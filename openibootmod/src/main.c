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
#include <armv7lib/cmsa/cac.h>
#include <armv7lib/vmsa/gen.h>
#include <armv7lib/vmsa/tt.h>

#include <fxplib/gen.h>

#include <dbglib/gen.h>

#include <socmod/map.h>
#include <socmod/wdt.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <kernel/mas.h>
#include <kernel/mmu.h>

#include <openibootmod/main.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	typedef void (* function_t)(void);
	//function_t function = NULL;
	tt_virtual_address_t va;
	tt_physical_address_t pa;
	mmu_paging_system_t ps;
	tt_translation_table_base_register_t ttbr;
	tt_first_level_descriptor_t fld;
	tt_virtual_address_t l1 = {.all = 0};

	// switch to the internal paging system
	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch to the internal paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// disable fiqs and irqs
	int_disable_fiq();
	int_disable_irq();

	CHECK_SUCCESS(mmu_get_paging_system(MMU_SWITCH_EXTERNAL, &ps), "unable to get the external paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	//CHECK_SUCCESS(tt_select_ttbr(va, ttbr0, ttbr1, ttbcr, &ttbr), "unable to select the correct paging system", va.all, sdw_dbg, DBG_LEVEL_2)
	//	return FAILURE;
	//CHECK_END
	ttbr.all = ps.ttbr1.all;

	CHECK_SUCCESS(tt_ttbr_to_pa(ttbr, &pa), "unable to convert ttbr to pa", ttbr.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map(pa, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL | MMU_MAP_NORMAL_MEMORY, &l1), "unable to map pa", pa.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	va.all = 0x50000000;
	pa.all = va.all;

	CHECK_SUCCESS(tt_get_fld(va, l1, &fld), "unable to get fld", va.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	fld.all = TT_NOT_PRESENT_TYPE;

	CHECK_SUCCESS(tt_set_fld(va, l1, fld), "unable to set fld", va.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_unmap(l1, (TT_NUMBER_LEVEL_1_ENTRIES * sizeof(tt_first_level_descriptor_t)), MMU_MAP_INTERNAL), "unable to unmap 11", l1.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map(pa, ONE_MEGABYTE, MMU_MAP_EXTERNAL | MMU_MAP_NORMAL_MEMORY, &va), "unable to map pa", pa.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// switch to the external paging system
	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch to the external paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	// copy some code to the 1MB of memory
	memcpy((void *)(va.all), gen_add_base(&openiboot_block), (&openiboot_block_end - &openiboot_block));

	//function = (function_t)va.all;

	cac_flush_entire_instruction_cache();
	cac_flush_entire_data_cache();

	DBG_LOG_STATEMENT("SUCCESS", SUCCESS, main_dbg, DBG_LEVEL_3);

	// jump to the 1MB of memory
	//function();

	return SUCCESS;
}

result_t fini_c(void) {

	return SUCCESS;
}
