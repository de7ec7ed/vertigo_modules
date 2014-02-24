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

#ifndef __BKPT_H__
#define __BKPT_H__

#include <armv7lib/gen.h>
#include <armv7lib/vmsa/tt.h>

#include <kernel/vec.h>

#define BKPT_BEFORE_INSTRUCTION 0
#define BKPT_AFTER_INSTRUCTION  1

#define BKPT_THUMB_BREAKPOINT_INSTRUCTION 0xFFFF
#define BKPT_ARM_BREAKPOINT_INSTRUCTION   0xFFFFFFFF

typedef struct bkpt_handler bkpt_handler_t;

typedef result_t (* bkpt_function_t)(bkpt_handler_t *handler, gen_general_purpose_registers_t *registers);

struct bkpt_handler {
	bkpt_handler_t *prev;
	tt_virtual_address_t va;
	gen_program_status_register_t psr;
	bkpt_function_t function;
	size_t value;
	void *data;
	bkpt_handler_t *next;
};

result_t bkpt_init(void);

result_t bkpt_patch(tt_virtual_address_t va, size_t *value);

result_t bkpt_register_handler(tt_virtual_address_t va, gen_program_status_register_t psr, bkpt_function_t function, void *data);

result_t bkpt_lookup_handler(tt_virtual_address_t va, bkpt_handler_t **handler);

result_t bkpt_unregister_handler(bkpt_handler_t *handler);

result_t bkpt_dispatch_handler(tt_virtual_address_t va, bool_t *handled, gen_general_purpose_registers_t *registers);

result_t bkpt_und_handler(vec_handler_t *handler, bool_t *handled, gen_general_purpose_registers_t *registers);

result_t bkpt_fini(void);

result_t bkpt_get_debug_level(size_t *level);

result_t bkpt_set_debug_level(size_t level);

#endif //__BKPT_H__
