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

#include <armv7lib/vmsa/tt.h>

#include <fxplib/gen.h>

#include <dbglib/gen.h>

#include <socmod/int.h>
#include <socmod/map.h>
#include <socmod/wdt.h>

#include <stdlib/check.h>

#include <kernel/mas.h>
#include <kernel/mmu.h>
#include <kernel/vec.h>

#include <wdtmod/main.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_2);

result_t main_irq_handler(vec_handler_t *handler, size_t *handled, gen_general_purpose_registers_t *registers) {

	tt_virtual_address_t va = {.all = 0};
	wdt_block_t *block;

	//DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	UNUSED_VARIABLE(handled);
	UNUSED_VARIABLE(registers);

	(*(size_t *)(handler->data))++;

	//DBG_LOG_STATEMENT("(*(size_t *)(handler->data))", (*(size_t *)(handler->data)), main_dbg, DBG_LEVEL_3);

	if(((*(size_t *)(handler->data)) % MAIN_INTERRUPT_VECTOR_CHECK_INTERVAL) == 0) {

		CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch to the internal paging system", FAILURE, main_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END

		CHECK_SUCCESS(mmu_map((tt_physical_address_t)MAP_WDT_ADDRESS, MAP_WDT_SIZE, MMU_MAP_INTERNAL, &va), "unable to map the watchdog timer", MAP_WDT_ADDRESS, main_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END

		block = (wdt_block_t *)va.all;

		DBG_LOG_STATEMENT("wtcon", block->wtcon.all, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("wtrstdat", block->wtrstdat.all, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("wtintdat", block->wtintdat.all, main_dbg, DBG_LEVEL_3);
		DBG_LOG_STATEMENT("wtcnt", block->wtcnt.all, main_dbg, DBG_LEVEL_3);

		wdt_reset_disable(block);
		wdt_interrupt_disable(block);

		CHECK_SUCCESS(mmu_unmap(va, MAP_WDT_SIZE, MMU_MAP_INTERNAL), "unable to unmap the watchdog timer", va.all, main_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END

		*(size_t *)(handler->data) = 0;
	}

	return SUCCESS;
}

result_t init_c(void) {

	tt_virtual_address_t va = {.all = 0};
	wdt_block_t *block;
	size_t *data;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch to the internal paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map((tt_physical_address_t)MAP_WDT_ADDRESS, MAP_WDT_SIZE, MMU_MAP_INTERNAL, &va), "unable to map the watchdog timer", MAP_WDT_ADDRESS, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	block = (wdt_block_t *)va.all;

	CHECK_SUCCESS(wdt_init(block, 0), "unable to init the watchdog timer", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("values before", 0, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtintdat", block->wtintdat.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtcon", block->wtcon.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtrstdat", block->wtrstdat.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtcnt", block->wtcnt.all, main_dbg, DBG_LEVEL_3);

	DBG_LOG_STATEMENT("[%] watchdog timer disabled", 0, main_dbg, DBG_LEVEL_2);

	wdt_reset_disable(block);
	wdt_interrupt_disable(block);

	DBG_LOG_STATEMENT("values after", 0, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtintdat", block->wtintdat.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtcon", block->wtcon.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtrstdat", block->wtrstdat.all, main_dbg, DBG_LEVEL_3);
	DBG_LOG_STATEMENT("wtcnt", block->wtcnt.all, main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_unmap(va, MAP_WDT_SIZE, MMU_MAP_INTERNAL), "unable to unmap the watchdog timer", va.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	data = malloc(sizeof(size_t));

	*data = 0;

	CHECK_SUCCESS(vec_register_handler(VEC_INTERRUPT_VECTOR, gen_add_base(main_irq_handler), data), "unable to add handler", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t fini_c(void) {

	tt_virtual_address_t va = {.all = 0};

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch to the internal paging system", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_map((tt_physical_address_t)MAP_WDT_ADDRESS, MAP_WDT_SIZE, MMU_MAP_INTERNAL, &va), "unable to map the watchdog timer", MAP_WDT_ADDRESS, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(wdt_fini((wdt_block_t *)va.all), "unable to fini the watchdog timer", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_unmap(va, MAP_WDT_SIZE, MMU_MAP_INTERNAL), "unable to unmap the watchdog timer", va.all, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(vec_unregister_handler(VEC_INTERRUPT_VECTOR, gen_add_base(main_irq_handler)), "unable to remove vector handler", FAILURE, main_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}
