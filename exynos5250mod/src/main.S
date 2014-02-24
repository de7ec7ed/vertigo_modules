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

#include <defines.h>

#include <hdrlib/mod.h>

ENTRY_POINT(default)

VARIABLE(callsign) .word CALLSIGN

// mod_header
VARIABLE(import_header_address) .word import_header
VARIABLE(export_header_address) .word export_header
VARIABLE(storage_header_address) .word storage_header

MOD_MODULE_INFORMATION exynos5250

// mod_import_header
import_header:
VARIABLE(import_functions_size) .word 4
VARIABLE(import_functions_address) .word import_functions

import_functions:

// dbglib 2
GEN_IMPORT_FUNCTION ser_print
GEN_IMPORT_FUNCTION mem_print

// kernel 2
GEN_IMPORT_FUNCTION mmu_map
GEN_IMPORT_FUNCTION mmu_unmap

// mod_export_header
export_header:
VARIABLE(export_functions_size) .word 30
VARIABLE(export_functions_address) .word export_functions

export_functions:

// socmod 30
GEN_EXPORT_FUNCTION soc_get_model_number
GEN_EXPORT_FUNCTION soc_get_family
GEN_EXPORT_FUNCTION soc_get_manufacture
GEN_EXPORT_FUNCTION uart_init
GEN_EXPORT_FUNCTION uart_fini
GEN_EXPORT_FUNCTION uart_get_rx_interrupt_status
GEN_EXPORT_FUNCTION uart_acknowledge_rx_interrupt
GEN_EXPORT_FUNCTION uart_get_tx_interrupt_status
GEN_EXPORT_FUNCTION uart_acknowledge_tx_interrupt
GEN_EXPORT_FUNCTION uart_set_clock
GEN_EXPORT_FUNCTION uart_write
GEN_EXPORT_FUNCTION uart_read
GEN_EXPORT_FUNCTION uart_putc
GEN_EXPORT_FUNCTION uart_getc
GEN_EXPORT_FUNCTION uart_get_physical_address
GEN_EXPORT_FUNCTION uart_get_size
GEN_EXPORT_FUNCTION wdt_init
GEN_EXPORT_FUNCTION wdt_fini
GEN_EXPORT_FUNCTION wdt_disable
GEN_EXPORT_FUNCTION wdt_enable
GEN_EXPORT_FUNCTION wdt_interrupt_disable
GEN_EXPORT_FUNCTION wdt_interrupt_enable
GEN_EXPORT_FUNCTION wdt_reset_disable
GEN_EXPORT_FUNCTION wdt_reset_enable
GEN_EXPORT_FUNCTION wdt_get_data
GEN_EXPORT_FUNCTION wdt_set_data
GEN_EXPORT_FUNCTION wdt_get_count
GEN_EXPORT_FUNCTION wdt_set_count
GEN_EXPORT_FUNCTION wdt_get_physical_address
GEN_EXPORT_FUNCTION wdt_get_size

// mod_storage_header
storage_header:

FUNCTION(init_asm)
	push {r1 - r12, lr}
	bl init_c
	pop {r1 - r12, pc}

FUNCTION(fini_asm)
	push {r1 - r12, lr}
	bl fini_c
	pop {r1 - r12, pc}
