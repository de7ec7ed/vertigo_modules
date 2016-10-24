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

#ifndef __QEMUMOD_WDT_H__
#define __QEMUMOD_WDT_H__

#include <defines.h>
#include <types.h>

typedef union wdt_generic_register wdt_null_register_t;

typedef volatile struct wdt_block wdt_block_t;

union wdt_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

struct wdt_block {
	wdt_null_register_t null;
} PACKED;

result_t wdt_init(wdt_block_t *block, size_t options);
result_t wdt_fini(wdt_block_t *block);

result_t wdt_disable(wdt_block_t *block);
result_t wdt_enable(wdt_block_t *block);

result_t wdt_interrupt_disable(wdt_block_t *block);
result_t wdt_interrupt_enable(wdt_block_t *block);

result_t wdt_reset_disable(wdt_block_t *block);
result_t wdt_reset_enable(wdt_block_t *block);

result_t wdt_get_data(wdt_block_t *block, size_t *count);
result_t wdt_set_data(wdt_block_t *block, size_t count);

result_t wdt_get_count(wdt_block_t *block, size_t *count);
result_t wdt_set_count(wdt_block_t *block, size_t count);

result_t wdt_get_physical_address(void **pa);
result_t wdt_get_size(size_t *size);

#endif //__QEMUMOD_WDT_H__
