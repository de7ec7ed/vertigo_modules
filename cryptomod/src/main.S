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

MOD_MODULE_INFORMATION cryptomod

// mod_import_header
import_header:
VARIABLE(import_functions_size) .word 6
VARIABLE(import_functions_address) .word import_functions

import_functions:

// dbglib 1
GEN_IMPORT_FUNCTION ser_print

// stdlib 3
GEN_IMPORT_FUNCTION memcmp
GEN_IMPORT_FUNCTION memset
GEN_IMPORT_FUNCTION memcpy

// kernel 2
GEN_IMPORT_FUNCTION mas_alloc
GEN_IMPORT_FUNCTION mas_free

// mod_export_header
export_header:
VARIABLE(export_functions_size) .word 9
VARIABLE(export_functions_address) .word export_functions

export_functions:
GEN_EXPORT_FUNCTION aes_setup
GEN_EXPORT_FUNCTION aes_encrypt
GEN_EXPORT_FUNCTION aes_decrypt
GEN_EXPORT_FUNCTION aes_number_of_rounds

GEN_EXPORT_FUNCTION sha1_init
GEN_EXPORT_FUNCTION sha1_pad
GEN_EXPORT_FUNCTION sha1_loop
GEN_EXPORT_FUNCTION sha1_result
GEN_EXPORT_FUNCTION sha1_buffer

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
