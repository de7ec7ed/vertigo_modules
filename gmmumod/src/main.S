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

// mod_header
VARIABLE(callsign) .word CALLSIGN
VARIABLE(version) .word MOD_VERSION

VARIABLE(import_header_address) .word import_header
VARIABLE(export_header_address) .word export_header
VARIABLE(storage_header_address) .word storage_header

MOD_MODULE_INFORMATION gmmumod gen_load init fini gen_unload

// mod_import_header
import_header:
VARIABLE(import_functions_size) .word 7
VARIABLE(import_functions_address) .word import_functions

import_functions:

/*
// intlib 15
GEN_IMPORT_FUNCTION pgtbl_cr3_to_pa
GEN_IMPORT_FUNCTION pgtbl_get_pml4e
GEN_IMPORT_FUNCTION pgtbl_pml4e_is_present
GEN_IMPORT_FUNCTION pgtbl_pml4e_to_pa
GEN_IMPORT_FUNCTION pgtbl_get_pdpte
GEN_IMPORT_FUNCTION pgtbl_pdpte_is_present
GEN_IMPORT_FUNCTION pgtbl_pdpte_to_pa
GEN_IMPORT_FUNCTION pgtbl_pdpte_is_region
GEN_IMPORT_FUNCTION pgtbl_get_pde
GEN_IMPORT_FUNCTION pgtbl_pde_is_present
GEN_IMPORT_FUNCTION pgtbl_pde_to_pa
GEN_IMPORT_FUNCTION pgtbl_pde_is_region
GEN_IMPORT_FUNCTION pgtbl_get_pte
GEN_IMPORT_FUNCTION pgtbl_pte_is_present
GEN_IMPORT_FUNCTION pgtbl_pte_to_pa
*/

//armv7lib 1
GEN_IMPORT_FUNCTION gen_va_to_pa

// kernel 8
GEN_IMPORT_FUNCTION log_printf
GEN_IMPORT_FUNCTION mas_alloc
GEN_IMPORT_FUNCTION mas_free
GEN_IMPORT_FUNCTION mmu_map
GEN_IMPORT_FUNCTION mmu_unmap
GEN_IMPORT_FUNCTION mmu_find_space

// mod_export_header
export_header:
VARIABLE(export_functions_size) .word 9
VARIABLE(export_functions_address) .word export_functions

export_functions:
GEN_EXPORT_FUNCTION gmmu_get_debug_level
GEN_EXPORT_FUNCTION gmmu_set_debug_level
GEN_EXPORT_FUNCTION gmmu_supports_1gb_pages
GEN_EXPORT_FUNCTION gmmu_supports_2mb_pages
GEN_EXPORT_FUNCTION gmmu_lookup_va
GEN_EXPORT_FUNCTION gmmu_lookup_pa
GEN_EXPORT_FUNCTION gmmu_map
GEN_EXPORT_FUNCTION gmmu_unmap
GEN_EXPORT_FUNCTION gmmu_map_guest_buffer

// mod_storage_header
storage_header:

