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

#include <dbglib/gen.h>
#include <fxplib/gen.h>
#include <stdlib/check.h>

#include <kernel/mmu.h>

#include <socmod/uart.h>
#include <socmod/wdt.h>
#include <socmod/main.h>

DBG_DEFINE_VARIABLE(main_dbg, DBG_LEVEL_3);

result_t init_c(void) {

	tt_physical_address_t pa;
	tt_virtual_address_t va;
	size_t size;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging system", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_get_physical_address(UART_DEFAULT, (void **)&(pa.all)), "unable to get the uart physical address", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_get_size(UART_DEFAULT, &size), "unable to get the uart size", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	va.all = 0;
	CHECK_SUCCESS(mmu_map(pa, size, MMU_MAP_INTERNAL | MMU_MAP_DEVICE_MEMORY, &va), "unable to map the uart", pa.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_init((uart_block_t *)(va.all), 0), "unable to initialize the uart", FAILURE, main_dbg, DBG_LEVEL_3)
		CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the uart", va.all, main_dbg, DBG_LEVEL_3) CHECK_END
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the uart", va.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch paging system", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t fini_c(void) {

	tt_physical_address_t pa;
	tt_virtual_address_t va;
	size_t size;

	DBG_LOG_FUNCTION(main_dbg, DBG_LEVEL_3);

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_INTERNAL), "unable to switch paging system", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_get_physical_address(UART_DEFAULT, (void **)&(pa.all)), "unable to get the uart physical address", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_get_size(UART_DEFAULT, &size), "unable to get the uart size", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	va.all = 0;
	CHECK_SUCCESS(mmu_map(pa, size, MMU_MAP_INTERNAL | MMU_MAP_DEVICE_MEMORY, &va), "unable to map the uart", pa.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(uart_fini((uart_block_t *)(va.all)), "unable to finalize the uart", FAILURE, main_dbg, DBG_LEVEL_3)
		CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the uart", va.all, main_dbg, DBG_LEVEL_3) CHECK_END
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_unmap(va, size, MMU_MAP_INTERNAL), "unable to unmap the uart", va.all, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END

	CHECK_SUCCESS(mmu_switch_paging_system(MMU_SWITCH_EXTERNAL), "unable to switch paging system", FAILURE, main_dbg, DBG_LEVEL_3)
		return FAILURE;
	CHECK_END


	return SUCCESS;
}
