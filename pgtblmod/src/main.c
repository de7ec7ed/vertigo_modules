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
#include <defines.h>
#include <types.h>

#include <armv7lib/int.h>
#include <armv7lib/vmsa/tt.h>

#include <fxplib/gen.h>

#include <dbglib/gen.h>

#include <stdlib/check.h>

#include <kernel/mmu.h>

#include <main.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t pgtbl_print_pages(size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s) {

	tt_physical_address_t tmp_pa;
	tt_virtual_address_t va = {.all = 0};
	tt_virtual_address_t l1 = {.all = 0};
	tt_virtual_address_t l2 = {.all = 0};
	tt_translation_table_base_register_t ttbr;
	tt_first_level_descriptor_t fld;
	tt_second_level_descriptor_t sld;
	mmu_paging_system_t ps;
	size_t i, j;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_get_paging_system(MMU_SWITCH_EXTERNAL, &ps), "unable to get the external paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(tt_select_ttbr(va, ps.ttbr0, ps.ttbr1, ps.ttbcr, &ttbr), "unable to select the correct paging system", va.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(tt_ttbr_to_pa(ttbr, &tmp_pa), "unable to convert ttbr to pa", ttbr.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map(tmp_pa, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l1), "unable to map l1", tmp_pa.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	for(i = 0; i < TT_NUMBER_LEVEL_1_ENTRIES; i++) {
		va.page_table.fields.l1_index = i;
		CHECK_SUCCESS(tt_get_fld(va, l1, &fld), "unable to get fld", va.all, main_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END

		if(tt_fld_is_page_table(fld) == TRUE) {

			CHECK_SUCCESS(tt_fld_to_pa(fld, &tmp_pa), "unable to convert fld to pa", fld.all, main_dbg, DBG_LEVEL_2)
				return FAILURE;
			CHECK_END

			CHECK_SUCCESS(mmu_map(tmp_pa, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l2), "unable to map l2", tmp_pa.all, main_dbg, DBG_LEVEL_2)
				return FAILURE;
			CHECK_END

			for(j = 0; j < TT_NUMBER_LEVEL_2_ENTRIES; j++) {
				va.page_table.fields.l2_index = j;
				CHECK_SUCCESS(tt_get_sld(va, l2, &sld), "unable to get sld", va.all, main_dbg, DBG_LEVEL_2)
					return FAILURE;
				CHECK_END

				if(pgtbl_sld_is_match(sld, options, pa, b, c, xn, ap_0, ap_1, s) == TRUE) {
					CHECK_SUCCESS(pgtbl_print_sld(sld), "unable to print the sld", sld.all, main_dbg, DBG_LEVEL_2)
						return FAILURE;
					CHECK_END

					DBG_LOG_STATEMENT("va.all", va.all, main_dbg, DBG_LEVEL_2);
				}
			}

			CHECK_SUCCESS(mmu_unmap(l2, (TT_NUMBER_LEVEL_2_ENTRIES * sizeof(tt_second_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 12", l2.all, main_dbg, DBG_LEVEL_2)
				return FAILURE;
			CHECK_END
		}
		else {
			if(pgtbl_fld_is_match(fld, options, pa, b, c, xn, ap_0, ap_1, s) == TRUE) {
				CHECK_SUCCESS(pgtbl_print_fld(fld), "unable to print the fld", sld.all, main_dbg, DBG_LEVEL_2)
					return FAILURE;
				CHECK_END

				DBG_LOG_STATEMENT("va.all", va.all, main_dbg, DBG_LEVEL_2);
			}
		}
	}

	CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

bool_t pgtbl_fld_is_match(tt_first_level_descriptor_t fld, size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s) {

	tt_physical_address_t tmp_pa;

	//DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	if(fld.all == 0) { return FALSE; }

	if(tt_fld_is_supersection(fld) == TRUE) {
		pa.supersection.fields.offset = 0;
		if((options & PGTBL_CHECK_BUFFERABLE) && (fld.supersection.fields.b != b)) { return FALSE; }
		if((options & PGTBL_CHECK_CACHEABLE) && (fld.supersection.fields.c != c)) { return FALSE; }
		if((options & PGTBL_CHECK_EXECUTE_NEVER) && (fld.supersection.fields.xn != xn)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_0) && (fld.supersection.fields.ap_0 != ap_0)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_1) && (fld.supersection.fields.ap_1 != ap_1)) { return FALSE; }
		if((options & PGTBL_CHECK_SHAREABLE) && (fld.supersection.fields.s != s)) { return FALSE; }
	}
	else if(tt_fld_is_section(fld) == TRUE) {
		pa.section.fields.offset = 0;
		if((options & PGTBL_CHECK_BUFFERABLE) && (fld.section.fields.b != b)) { return FALSE; }
		if((options & PGTBL_CHECK_CACHEABLE) && (fld.section.fields.c != c)) { return FALSE; }
		if((options & PGTBL_CHECK_EXECUTE_NEVER) && (fld.section.fields.xn != xn)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_0) && (fld.section.fields.ap_0 != ap_0)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_1) && (fld.section.fields.ap_1 != ap_1)) { return FALSE; }
		if((options & PGTBL_CHECK_SHAREABLE) && (fld.supersection.fields.s != s)) { return FALSE; }
	}
	else {
		return FALSE;
	}

	CHECK_SUCCESS(tt_fld_to_pa(fld, &tmp_pa), "unable to convert fld to pa", fld.all, main_dbg, DBG_LEVEL_2)
		return FALSE;
	CHECK_END

	if((options & PGTBL_CHECK_PHYSICAL_ADDRESS) && (pa.all != tmp_pa.all)) { return FALSE; }

	return TRUE;
}

bool_t pgtbl_sld_is_match(tt_second_level_descriptor_t sld, size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s) {

	tt_physical_address_t tmp_pa;

	//DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	if(sld.all == 0) { return FALSE; }

	if(tt_sld_is_large_page(sld) == TRUE) {
		pa.large_page.fields.offset = 0;
		if((options & PGTBL_CHECK_BUFFERABLE) && (sld.large_page.fields.b != b)) { return FALSE; }
		if((options & PGTBL_CHECK_CACHEABLE) && (sld.large_page.fields.c != c)) { return FALSE; }
		if((options & PGTBL_CHECK_EXECUTE_NEVER) && (sld.large_page.fields.xn != xn)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_0) && (sld.large_page.fields.ap_0 != ap_0)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_1) && (sld.large_page.fields.ap_1 != ap_1)) { return FALSE; }
		if((options & PGTBL_CHECK_SHAREABLE) && (sld.large_page.fields.s != s)) { return FALSE; }
	}
	else if(tt_sld_is_small_page(sld) == TRUE) {
		pa.small_page.fields.offset = 0;
		if((options & PGTBL_CHECK_BUFFERABLE) && (sld.small_page.fields.b != b)) { return FALSE; }
		if((options & PGTBL_CHECK_CACHEABLE) && (sld.small_page.fields.c != c)) { return FALSE; }
		if((options & PGTBL_CHECK_EXECUTE_NEVER) && (sld.small_page.fields.xn != xn)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_0) && (sld.small_page.fields.ap_0 != ap_0)) { return FALSE; }
		if((options & PGTBL_CHECK_ACCESS_PERMISSIONS_1) && (sld.small_page.fields.ap_1 != ap_1)) { return FALSE; }
		if((options & PGTBL_CHECK_SHAREABLE) && (sld.small_page.fields.s != s)) { return FALSE; }
	}
	else {
		return FALSE;
	}

	CHECK_SUCCESS(tt_sld_to_pa(sld, &tmp_pa), "unable to convert sld to pa", sld.all, main_dbg, DBG_LEVEL_2)
		return FALSE;
	CHECK_END

	if((options & PGTBL_CHECK_PHYSICAL_ADDRESS) && (pa.all != tmp_pa.all)) { return FALSE; }

	return TRUE;
}

result_t pgtbl_print_fld(tt_first_level_descriptor_t fld) {

	tt_physical_address_t pa;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	if(tt_fld_is_supersection(fld) == TRUE) {
		DBG_LOG_STATEMENT("fld.supersection.all", fld.supersection.all, main_dbg, DBG_LEVEL_2);
		DBG_LOG_STATEMENT("fld.supersection.fields.type_0", fld.supersection.fields.type_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.b", fld.supersection.fields.b, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.c", fld.supersection.fields.c, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.xn", fld.supersection.fields.xn, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.ap_0", fld.supersection.fields.ap_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.tex", fld.supersection.fields.tex, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.ap_1", fld.supersection.fields.ap_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.s", fld.supersection.fields.s, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.ng", fld.supersection.fields.ng, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.type_1", fld.supersection.fields.type_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.supersection.fields.ns", fld.supersection.fields.ns, main_dbg, DBG_LEVEL_3);
	}
	else if(tt_fld_is_section(fld) == TRUE) {
		DBG_LOG_STATEMENT("fld.section.all", fld.section.all, main_dbg, DBG_LEVEL_2);
		DBG_LOG_STATEMENT("fld.section.fields.type_0", fld.section.fields.type_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.b", fld.section.fields.b, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.c", fld.section.fields.c, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.xn", fld.section.fields.xn, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.ap_0", fld.section.fields.ap_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.tex", fld.section.fields.tex, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.ap_1", fld.section.fields.ap_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.s", fld.section.fields.s, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.ng", fld.section.fields.ng, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.type_1", fld.section.fields.type_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("fld.section.fields.ns", fld.section.fields.ns, main_dbg, DBG_LEVEL_3);
	}
	else {
		return FAILURE;
	}

	CHECK_SUCCESS(tt_fld_to_pa(fld, &pa), "unable to translate fld to pa", fld.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("pa.all", pa.all, main_dbg, DBG_LEVEL_2);

	return SUCCESS;
}

result_t pgtbl_print_sld(tt_second_level_descriptor_t sld) {

	tt_physical_address_t pa;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	if(tt_sld_is_large_page(sld) == TRUE) {
		DBG_LOG_STATEMENT("sld.large_page.all", sld.large_page.all, main_dbg, DBG_LEVEL_2);
		DBG_LOG_STATEMENT("sld.large_page.fields.type", sld.large_page.fields.type, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.b", sld.large_page.fields.b, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.c", sld.large_page.fields.c, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.ap_0", sld.large_page.fields.ap_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.ap_1", sld.large_page.fields.ap_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.s", sld.large_page.fields.s, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.ng", sld.large_page.fields.ng, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.tex", sld.large_page.fields.tex, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.large_page.fields.xn", sld.large_page.fields.xn, main_dbg, DBG_LEVEL_3);
	}
	else if(tt_sld_is_small_page(sld) == TRUE) {
		DBG_LOG_STATEMENT("sld.small_page.all", sld.small_page.all, main_dbg, DBG_LEVEL_2);
		DBG_LOG_STATEMENT("sld.small_page.fields.type", sld.small_page.fields.type, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.b", sld.small_page.fields.b, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.c", sld.small_page.fields.c, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.ap_0", sld.small_page.fields.ap_0, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.tex", sld.small_page.fields.tex, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.ap_1", sld.small_page.fields.ap_1, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.s", sld.small_page.fields.s, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.ng", sld.small_page.fields.ng, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("sld.small_page.fields.xn", sld.small_page.fields.xn, main_dbg, DBG_LEVEL_3);
	}
	else {
		return FAILURE;
	}

	CHECK_SUCCESS(tt_sld_to_pa(sld, &pa), "unable to translate sld to pa", sld.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("pa.all", pa.all, main_dbg, DBG_LEVEL_2);

	return SUCCESS;
}

result_t init_c(void) {

	tt_physical_address_t pa;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	pa.all = 0x12440000;

	CHECK_SUCCESS(pgtbl_print_pages(PGTBL_CHECK_PHYSICAL_ADDRESS, pa, 0, 0, 0, 0, 0, 0), "unable to print pages", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	mmu_set_debug_level(DBG_LEVEL_2);

	return SUCCESS;
}

result_t fini_c(void) {

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);


	return SUCCESS;
}
