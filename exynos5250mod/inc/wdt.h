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

#ifndef __EXYNOS5250MOD_WDT_H__
#define __EXYNOS5250MOD_WDT_H__

#include <defines.h>
#include <types.h>

#define WDT_WTCON_OFFSET          0x0 // Watchdog timer control register
#define WDT_WTDAT_OFFSET          0x4 // Watchdog timer data register
#define WDT_WTCNT_OFFSET          0x8 // Watchdog timer count register
#define WDT_WTCRLINT_OFFSET       0xC // Watchdog timer interrupt clear register

typedef union wdt_control_register wdt_control_register_t;
typedef union wdt_generic_register wdt_data_register_t;
typedef union wdt_generic_register wdt_count_register_t;
typedef union wdt_generic_register wdt_clear_interrupt_register_t;


typedef volatile struct wdt_block wdt_block_t;

union wdt_control_register {
	struct {
		u32_t re     :1; // Reset Enable/Disable
		u32_t res_0  :1;
		u32_t ie     :1; // Interrupt enable
		u32_t cs     :2; // Clock Select
		u32_t tmr    :1; // Enables/Disables the Watchdog Timer
		u32_t res_1  :2;
		u32_t psr    :8; // Prescaler value
		u32_t res_2  :16;
	} fields;
	u32_t all;
};

union wdt_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

struct wdt_block {
	wdt_control_register_t wtcon;
	wdt_data_register_t wtdat;
	wdt_count_register_t wtcnt;
	wdt_clear_interrupt_register_t wtclrint;

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

#endif //__EXYNOS5250MOD_WDT_H__
