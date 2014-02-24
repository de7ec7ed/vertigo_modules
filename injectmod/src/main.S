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

MOD_MODULE_INFORMATION testmod

// mod_import_header
import_header:
VARIABLE(import_functions_size) .word 24
VARIABLE(import_functions_address) .word import_functions

import_functions:

// armlib 4
GEN_IMPORT_FUNCTION gen_get_cpsr
GEN_IMPORT_FUNCTION gen_get_spsr
GEN_IMPORT_FUNCTION gen_va_to_pa
GEN_IMPORT_FUNCTION cac_flush_entire_data_cache

// dbglib 1
GEN_IMPORT_FUNCTION ser_print

// linmod 9
GEN_IMPORT_FUNCTION lin_get_schedule_address
GEN_IMPORT_FUNCTION lin_printk
GEN_IMPORT_FUNCTION lin_call_usermodehelper_setup
GEN_IMPORT_FUNCTION lin_call_usermodehelper_exec
GEN_IMPORT_FUNCTION lin_create_proc_entry
GEN_IMPORT_FUNCTION lin_remove_proc_entry
GEN_IMPORT_FUNCTION lin_remap_pfn_range
GEN_IMPORT_FUNCTION lin_kmalloc
GEN_IMPORT_FUNCTION lin_kfree

// bkptmod 4
GEN_IMPORT_FUNCTION bkpt_register_handler
GEN_IMPORT_FUNCTION bkpt_lookup_handler
GEN_IMPORT_FUNCTION bkpt_unregister_handler
GEN_IMPORT_FUNCTION bkpt_set_debug_level

// core 6
GEN_IMPORT_FUNCTION memcpy
GEN_IMPORt_FUNCTION memset
GEN_IMPORT_FUNCTION mas_alloc
GEN_IMPORT_FUNCTION mas_free
GEN_IMPORT_FUNCTION mas_set_debug_level
GEN_IMPORT_FUNCTION mmu_lookup_pa

// mod_export_header
export_header:
VARIABLE(export_functions_size) .word 0
VARIABLE(export_functions_address) .word export_functions

export_functions:

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

// this is were we should pass execution to
// after we are done doing what needs to be done
VARIABLE(schedule_return) .word 0

// this is the entry point to the schedule hook
// in supervisor mode
FUNCTION(schedule_asm)
	push {r0 - r12, lr}
	bl schedule_c
	pop {r0 - r12, pc}
	ldr pc, schedule_return



