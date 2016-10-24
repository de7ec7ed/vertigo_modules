/* This file is part of VERTIGO.
 *
 * (C) Copyright 2013, Siege Technologies <http://www.siegetechnologies.com>
 * (C) Copyright 2013, Kirk Swidowski <http://www.swidowski.com>
 *
 * VERTIGO is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VERTIGO is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VERTIGO. If not, see <http://www.gnu.org/licenses/>.
 *
 * Written by Kirk Swidowski <kirk@swidowski.com>
 */

#include <config.h>

#include <armv7lib/cmsa/cac.h>
#include <armv7lib/vmsa/gen.h>
#include <armv7lib/vmsa/flt.h>
#include <armv7lib/vmsa/tlb.h>

#include <dbglib/gen.h>

#include <fxplib/gen.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <kernel/mas.h>
#include <kernel/vec.h>

#include <sdwmod/sdw.h>

DBG_DEFINE_VARIABLE(sdw_dbg, DBG_LEVEL_2);

sdw_handler_t *sdw_handlers = NULL;

result_t sdw_init(void) {

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(vec_register_handler(VEC_PREFETCH_ABORT_VECTOR, (vec_function_t)sdw_pabt_handler, NULL), "unable to add vector handler", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(vec_register_handler(VEC_DATA_ABORT_VECTOR, (vec_function_t)sdw_dabt_handler, NULL), "unable to add vector handler", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t sdw_add_handler(tt_physical_address_t pa, sdw_function_t function, void *data) {

	tt_virtual_address_t va;
	tt_virtual_address_t l1 = {.all = 0};
	tt_virtual_address_t l2 = {.all = 0};
	tt_virtual_address_t start;
	tt_virtual_address_t end;
	tt_translation_table_base_register_t ttbr;
	tt_first_level_descriptor_t fld;
	tt_second_level_descriptor_t sld;
	mmu_paging_system_t ps;
	sdw_handler_t *handler;
	sdw_handler_t **head;
	size_t i;

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	head = &sdw_handlers;

	handler = (sdw_handler_t *)malloc(sizeof(sdw_handler_t));

	CHECK_NOT_NULL(handler, "handler is null", handler, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	memset(handler, 0, sizeof(sdw_handler_t));

	start.all = (size_t)ONE_GIGABYTE * 3;
	end.all = ((size_t)ONE_GIGABYTE * 4) - 1;

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch the internal paging system", FAILURE, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("pa", pa.all, sdw_dbg, DBG_LEVEL_3);

	// I just don't see a good way around this we need to search all the page tables for the pa
	CHECK_SUCCESS(gen_pa_to_va(pa, start, end, &va), "failed to translate pa to va", pa.all, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("va", va.all, sdw_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging system", FAILURE, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_get_paging_system(MMU_SWITCH_EXTERNAL, &ps), "unable to get the external paging system", FAILURE, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("ttbr0", ps.ttbr0.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("ttbr1", ps.ttbr1.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("ttbcr", ps.ttbcr.all, sdw_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(tt_select_ttbr(va, ps.ttbr0, ps.ttbr1, ps.ttbcr, &ttbr), "unable to select the correct paging system", va.all, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	// well the tt_select_ttbr should pick the correct ttbr to use for the lookup
	// all known OSs use ttbr1 to store the kernel page tables no matter if it is
	// used by the mmu or not so if the ttbr1 pa is not 0 then use it instead
	// of ttbr0
	// instead of doing this the unmapping should be done on both ttb registers
	// as the current approach could take a little while to syncronize across
	// the different address spaces
	// this also implies that shadow paging should only be performed on kernel
	// pages unless you know process of interest and its ttb registers are in ps

	CHECK_SUCCESS(tt_ttbr_to_pa(ps.ttbr1, &pa), "unable to convert ttbr to pa", ttbr.all, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	if(pa.all != 0) {
		ttbr = ps.ttbr1;
	}
	else {
		CHECK_SUCCESS(tt_ttbr_to_pa(ps.ttbr0, &pa), "unable to convert ttbr to pa", ttbr.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			return FAILURE;
		CHECK_END
	}

	CHECK_SUCCESS(mmu_map(pa, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l1), "unable to map pa", pa.all, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(tt_get_fld(va, l1, &fld), "unable to get fld", va.all, sdw_dbg, DBG_LEVEL_2)
		free(handler);
		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
		return FAILURE;
	CHECK_END

	if(tt_fld_is_supersection(fld) == TRUE) {
		handler->fld = fld;
		handler->size = TT_SUPERSECTION_SIZE;
		va.supersection.fields.offset = 0;
		handler->va = va;
		CHECK_SUCCESS(tt_fld_to_pa(fld, &(handler->pa)), "unable to translate fld to pa", fld.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		for(i = 0; i < TT_NUMBER_SUPERSECTION_ENTRIES; i++) {
			CHECK_SUCCESS(tt_get_fld(va, l1, &fld), "unable to get fld", va.all, sdw_dbg, DBG_LEVEL_2)
				free(handler);
				CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				return FAILURE;
			CHECK_END

			fld.all = 0;
			CHECK_SUCCESS(tt_set_fld(va, l1, fld), "unable to set fld", va.all, sdw_dbg, DBG_LEVEL_2)
				free(handler);
				CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				return FAILURE;
			CHECK_END

			cac_flush_cache_region(&(((tt_first_level_descriptor_t *)l1.all)[va.page_table.fields.l1_index]), sizeof(tt_first_level_descriptor_t));

			va.page_table.fields.l1_index++;
		}

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			return FAILURE;
		CHECK_END
	}
	else if(tt_fld_is_section(fld) == TRUE) {
		handler->fld = fld;
		handler->size = TT_SECTION_SIZE;
		va.section.fields.offset = 0;
		handler->va = va;
		CHECK_SUCCESS(tt_fld_to_pa(fld, &(handler->pa)), "unable to translate fld to pa", fld.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		fld.all = 0;
		CHECK_SUCCESS(tt_set_fld(va, l1, fld), "unable to set fld", va.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		cac_flush_cache_region(&(((tt_first_level_descriptor_t *)l1.all)[va.page_table.fields.l1_index]), sizeof(tt_first_level_descriptor_t));

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			return FAILURE;
		CHECK_END
	}
	else if(tt_fld_is_page_table(fld) == TRUE) {

		CHECK_SUCCESS(tt_fld_to_pa(fld, &pa), "unable to convert fld to pa", fld.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(mmu_map(pa, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l2), "unable to map pa", pa.all, sdw_dbg, DBG_LEVEL_2)
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			free(handler);
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(tt_get_sld(va, l2, &sld), "unable to get sld", va.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		handler->sld = sld;
		CHECK_SUCCESS(tt_sld_to_pa(sld, &(handler->pa)), "unable to translate sld to pa", sld.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		if(tt_sld_is_small_page(sld) == TRUE) {

			handler->size = TT_SMALL_PAGE_SIZE;
			va.small_page.fields.offset = 0;
			handler->va = va;

			sld.all = 0;
			CHECK_SUCCESS(tt_set_sld(va, l2, sld), "unable to set sld", va.all, sdw_dbg, DBG_LEVEL_2)
				free(handler);
				CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				return FAILURE;
			CHECK_END

			cac_flush_cache_region(&(((tt_second_level_descriptor_t *)l2.all)[va.page_table.fields.l2_index]), sizeof(tt_second_level_descriptor_t));
		}
		else if(tt_sld_is_large_page(sld) == TRUE) {
			handler->size = TT_LARGE_PAGE_SIZE;
			va.large_page.fields.offset = 0;
			handler->va = va;

			for(i = 0; i < TT_NUMBER_LARGE_PAGE_ENTRIES; i++) {
				CHECK_SUCCESS(tt_get_sld(va, l2, &sld), "unable to get sld", va.all, sdw_dbg, DBG_LEVEL_2)
					free(handler);
					CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					return FAILURE;
				CHECK_END

				sld.all = 0;
				CHECK_SUCCESS(tt_set_sld(va, l2, sld), "unable to set sld", va.all, sdw_dbg, DBG_LEVEL_2)
					free(handler);
					CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					return FAILURE;
				CHECK_END

				cac_flush_cache_region(&(((tt_second_level_descriptor_t *)l2.all)[va.page_table.fields.l2_index]), sizeof(tt_second_level_descriptor_t));

				va.page_table.fields.l2_index++;
			}
		}
		else {
			DBG_LOG_STATEMENT("second level descriptor type is unsupported", sld.all, sdw_dbg, DBG_LEVEL_2);
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l2", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		}

		handler->fld.all = fld.all;

		CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, sdw_dbg, DBG_LEVEL_2)
			free(handler);
			return FAILURE;
		CHECK_END
	}
	else {
		DBG_LOG_STATEMENT("first level descriptor type is unsupported", fld.all, sdw_dbg, DBG_LEVEL_2);
		free(handler);
		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap l1", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
		return FAILURE;
	}

	handler->prev = NULL;
	handler->function = function;
	handler->data = data;
	handler->next = *head;

	if(*head != NULL) {
		(*head)->prev = handler;
	}

	*head = handler;

	DBG_LOG_STATEMENT("handler->fld.all", handler->fld.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->sld.all", handler->sld.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->pa.all", handler->pa.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->va.all", handler->va.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->size", handler->size, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->function", handler->function, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->data", handler->data, sdw_dbg, DBG_LEVEL_3);

	tlb_invalidate_tlb_region((void *)(handler->va.all), handler->size);

	return SUCCESS;
}

result_t sdw_lookup_handler_by_va(tt_virtual_address_t va, sdw_handler_t **handler) {

	sdw_handler_t **head;

	//DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(handler, "handler is null", handler, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	head = &sdw_handlers;

	*handler = *head;

	while(*handler != NULL) {
		if((va.all >= (*handler)->va.all) && (va.all < ((*handler)->va.all + (*handler)->size))) {
			return SUCCESS;
		}
		*handler = (*handler)->next;
	}

	return FAILURE;
}

result_t sdw_lookup_handler_by_pa(tt_physical_address_t pa, sdw_handler_t **handler) {

	sdw_handler_t **head;

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	CHECK_NOT_NULL(handler, "handler is null", handler, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	head = &sdw_handlers;

	*handler = *head;

	while(*handler != NULL) {
		if((pa.all >= (*handler)->pa.all) && (pa.all < ((*handler)->pa.all + (*handler)->size))) {
			return SUCCESS;
		}
		*handler = (*handler)->next;
	}

	return FAILURE;
}

result_t sdw_remove_handler(sdw_handler_t *handler) {

	sdw_handler_t **head;
	tt_virtual_address_t va;
	tt_virtual_address_t l1 = {.all = 0};
	tt_virtual_address_t l2 = {.all = 0};
	tt_physical_address_t pa;
	tt_translation_table_base_register_t ttbr;
	tt_first_level_descriptor_t fld;
	tt_second_level_descriptor_t sld;
	mmu_paging_system_t ps;
	size_t i;

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	head = &sdw_handlers;

	CHECK_NOT_NULL(handler, "handler is null", handler, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("handler->fld.all", handler->fld.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->sld.all", handler->sld.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->pa.all", handler->pa.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->va.all", handler->va.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->size", handler->size, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->function", handler->function, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("handler->data", handler->data, sdw_dbg, DBG_LEVEL_3);

	pa = handler->pa;
	va = handler->va;

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging system", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_get_paging_system(MMU_SWITCH_EXTERNAL, &ps), "unable to get the stored paging system", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("ttbr0", ps.ttbr0.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("ttbr1", ps.ttbr1.all, sdw_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("ttbcr", ps.ttbcr.all, sdw_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(tt_select_ttbr(va, ps.ttbr0, ps.ttbr1, ps.ttbcr, &ttbr), "unable to select the correct paging system", va.all, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// well the tt_select_ttbr should pick the correct ttbr to use for the lookup
	// all known OSs use ttbr1 to store the kernel page tables no matter if it is
	// used by the mmu or not so if the ttbr1 pa is not 0 then use it instead
	// of ttbr0
	// instead of doing this the unmapping should be done on both ttb registers
	// as the current approach could take a little while to syncronize across
	// the different address spaces
	// this also implies that shadow paging should only be performed on kernel
	// pages unless you know process of interest and its ttb registers are in ps

	CHECK_SUCCESS(tt_ttbr_to_pa(ps.ttbr1, &pa), "unable to convert ttbr to pa", ttbr.all, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	if(pa.all != 0) {
		ttbr = ps.ttbr1;
	}
	else {
		CHECK_SUCCESS(tt_ttbr_to_pa(ps.ttbr0, &pa), "unable to convert ttbr to pa", ttbr.all, sdw_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
	}

	CHECK_SUCCESS(tt_ttbr_to_pa(ttbr, &pa), "unable to convert ttbr to pa", ttbr.all, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map(pa, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l1), "unable to map pa", pa.all, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	if(tt_fld_is_supersection(handler->fld) == TRUE) {

		DBG_LOG_STATEMENT("fld is a supersection", handler->fld.all, sdw_dbg, DBG_LEVEL_3);

		for(i = 0; i < TT_NUMBER_SUPERSECTION_ENTRIES; i++) {
			CHECK_SUCCESS(tt_set_fld(va, l1, handler->fld), "unable to set fld", va.all, sdw_dbg, DBG_LEVEL_2)
				CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				return FAILURE;
			CHECK_END

			cac_flush_cache_region(&(((tt_first_level_descriptor_t *)l1.all)[va.page_table.fields.l1_index]), sizeof(tt_first_level_descriptor_t));

			va.page_table.fields.l1_index++;
		}

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, sdw_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
	}
	else if(tt_fld_is_section(handler->fld) == TRUE) {

		DBG_LOG_STATEMENT("fld is a section", handler->fld.all, sdw_dbg, DBG_LEVEL_3);

		CHECK_SUCCESS(tt_set_fld(va, l1, handler->fld), "unable to set fld", va.all, sdw_dbg, DBG_LEVEL_2)
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		cac_flush_cache_region(&(((tt_first_level_descriptor_t *)l1.all)[va.page_table.fields.l1_index]), sizeof(tt_first_level_descriptor_t));

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
	}
	else if(tt_fld_is_page_table(handler->fld) == TRUE) {

		DBG_LOG_STATEMENT("fld is a page table", handler->fld.all, sdw_dbg, DBG_LEVEL_3);

		CHECK_SUCCESS(tt_fld_to_pa(handler->fld, &pa), "unable to convert fld to pa", fld.all, sdw_dbg, DBG_LEVEL_2)
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(mmu_map(pa, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l2), "unable to map pa", pa.all, sdw_dbg, DBG_LEVEL_2)
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		if(tt_sld_is_small_page(handler->sld) == TRUE) {

			DBG_LOG_STATEMENT("sld is a small page", handler->sld.all, sdw_dbg, DBG_LEVEL_3);

			CHECK_SUCCESS(tt_set_sld(va, l2, handler->sld), "unable to set sld", va.all, sdw_dbg, DBG_LEVEL_2)
				CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
				return FAILURE;
			CHECK_END

			cac_flush_cache_region(&(((tt_second_level_descriptor_t *)l2.all)[va.page_table.fields.l2_index]), sizeof(tt_second_level_descriptor_t));

		}
		else if(tt_sld_is_large_page(handler->sld) == TRUE) {

			DBG_LOG_STATEMENT("sld is a large page", handler->sld.all, sdw_dbg, DBG_LEVEL_2);

			for(i = 0; i < TT_NUMBER_LARGE_PAGE_ENTRIES; i++) {
				CHECK_SUCCESS(tt_set_sld(va, l2, handler->sld), "unable to set sld", va.all, sdw_dbg, DBG_LEVEL_2)
					CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
					return FAILURE;
				CHECK_END

				cac_flush_cache_region(&(((tt_second_level_descriptor_t *)l2.all)[va.page_table.fields.l2_index]), sizeof(tt_second_level_descriptor_t));

				va.page_table.fields.l2_index++;
			}
		}
		else {
			DBG_LOG_STATEMENT("second level descriptor type is unsupported", sld.all, sdw_dbg, DBG_LEVEL_2);
			CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		}

		CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, sdw_dbg, DBG_LEVEL_2)
			CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
	}
	else {
		DBG_LOG_STATEMENT("first level descriptor type is unsupported", fld.all, sdw_dbg, DBG_LEVEL_2);
		CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l1.all, sdw_dbg, DBG_LEVEL_2) CHECK_END
		return FAILURE;
	}

	tlb_invalidate_tlb_region((void *)(handler->va.all), handler->size);

	if(handler == *head) {
		*head = handler->next;
	}
	else {
		if(handler->prev != NULL) {
			handler->prev->next = handler->next;
		}

		if(handler->next != NULL) {
			handler->next->prev = handler->prev;
		}
	}
	free(handler);

	return SUCCESS;
}

result_t sdw_dispatch_handler(size_t fault, tt_virtual_address_t va, size_t *handled, gen_general_purpose_registers_t *registers) {

	sdw_handler_t *handler;

	//DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	if(sdw_lookup_handler_by_va(va, &handler) == SUCCESS) {
		CHECK_SUCCESS(handler->function(handler, fault, registers), "handler returned failure", FAILURE, sdw_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END
		*handled = TRUE;
	}

	return SUCCESS;
}

result_t sdw_pabt_handler(vec_handler_t *handler, size_t *handled, gen_general_purpose_registers_t *registers) {

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	UNUSED_VARIABLE(handler);

	CHECK_SUCCESS(sdw_dispatch_handler(SDW_INSTRUCTION_FAULT, flt_get_ifar(), handled, registers), "sdw dispatch handler returned failure", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t sdw_dabt_handler(vec_handler_t *handler, size_t *handled, gen_general_purpose_registers_t *registers) {

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	UNUSED_VARIABLE(handler);

	CHECK_SUCCESS(sdw_dispatch_handler(SDW_DATA_FAULT, flt_get_dfar(), handled, registers), "sdw dispatch handler returned failure", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t sdw_fini(void) {

	sdw_handler_t **head;
	sdw_handler_t *tmp;

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	head = &sdw_handlers;

	CHECK_SUCCESS(vec_unregister_handler(VEC_PREFETCH_ABORT_VECTOR, (vec_function_t)sdw_pabt_handler), "unable to remove vector handler", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(vec_unregister_handler(VEC_PREFETCH_ABORT_VECTOR, (vec_function_t)sdw_pabt_handler), "unable to remove vector handler", FAILURE, sdw_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// free the linked list of handlers
	while(*head != NULL) {
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}

	return SUCCESS;
}

result_t sdw_get_debug_level(size_t *level) {

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	DBG_GET_VARIABLE(sdw_dbg, *level);

	return SUCCESS;
}

result_t sdw_set_debug_level(size_t level) {

	DBG_LOG_FUNCTION(sdw_dbg, DBG_LEVEL_3);

	DBG_SET_VARIABLE(sdw_dbg, level);

	return SUCCESS;
}
