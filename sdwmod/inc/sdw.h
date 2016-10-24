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

#ifndef __SDWMOD_SDW_H__
#define __SDWMOD_SDW_H__

#include <defines.h>
#include <types.h>

#include <armv7lib/gen.h>
#include <armv7lib/vmsa/tt.h>

#include <kernel/vec.h>

#include <bkptmod/bkpt.h>

#define SDW_DATA_FAULT VEC_DATA_ABORT_VECTOR
#define SDW_INSTRUCTION_FAULT VEC_PREFETCH_ABORT_VECTOR

// ttbr write mask
#define SDW_MCR_P15_00_XX_C2_C0_00_MASK 0xFFFF0FFF

// ttbr 0 write instruction
#define SDW_MCR_P15_00_XX_C2_C0_00      0xEE020F10

// ttbr 1 write instruction
#define SDW_MCR_P15_00_XX_C2_C0_01      0xEE020F30

// mcr coprocessor mask
#define SDW_MCR_PXX_MASK 0x00000F00

typedef struct sdw_handler sdw_handler_t;

typedef result_t (* sdw_function_t)(sdw_handler_t *handler, size_t fault, gen_general_purpose_registers_t *registers);

struct sdw_handler {
	sdw_handler_t *prev;
	tt_first_level_descriptor_t fld;
	tt_second_level_descriptor_t sld;
	tt_physical_address_t pa;
	tt_virtual_address_t va;
	size_t size;
	sdw_function_t function;
	void *data;
	sdw_handler_t *next;
};

result_t sdw_init(void);

result_t sdw_add_handler(tt_physical_address_t pa, sdw_function_t function, void *data);

result_t sdw_lookup_handler_by_va(tt_virtual_address_t va, sdw_handler_t **handler);

result_t sdw_lookup_handler_by_pa(tt_physical_address_t pa, sdw_handler_t **handler);

result_t sdw_remove_handler(sdw_handler_t *handler);

result_t sdw_dispatch_handler(size_t fault, tt_virtual_address_t va, size_t *handled, gen_general_purpose_registers_t *registers);

result_t sdw_ttbr0_bkpt_handler(bkpt_handler_t *handler, gen_general_purpose_registers_t *registers);

result_t sdw_pabt_handler(vec_handler_t *handler, size_t *handled, gen_general_purpose_registers_t *registers);

result_t sdw_dabt_handler(vec_handler_t *handler, size_t *handled, gen_general_purpose_registers_t *registers);

result_t sdw_fini(void);

result_t sdw_get_debug_level(size_t *level);

result_t sdw_set_debug_level(size_t level);

#endif //__SDWMOD_SDW_H__
