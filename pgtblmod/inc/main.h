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

#ifndef __PGTBLMOD_MAIN_H__
#define __PGTBLMOD_MAIN_H__

#define PGTBL_CHECK_PHYSICAL_ADDRESS     (1 << 0)
#define PGTBL_CHECK_BUFFERABLE           (1 << 1)
#define PGTBL_CHECK_CACHEABLE            (1 << 2)
#define PGTBL_CHECK_EXECUTE_NEVER        (1 << 3)
#define PGTBL_CHECK_ACCESS_PERMISSIONS_0 (1 << 4)
#define PGTBL_CHECK_ACCESS_PERMISSIONS_1 (1 << 5)
#define PGTBL_CHECK_SHAREABLE            (1 << 6)

#ifdef __C__

result_t init_c(void);
result_t fini_c(void);

result_t pgtbl_print_pages(size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s);
bool_t pgtbl_fld_is_match(tt_first_level_descriptor_t fld, size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s);
bool_t pgtbl_sld_is_match(tt_second_level_descriptor_t sld, size_t options, tt_physical_address_t pa, bool_t b, bool_t c, bool_t xn, u8_t ap_0, u8_t ap_1, bool_t s);
result_t pgtbl_print_fld(tt_first_level_descriptor_t fld);
result_t pgtbl_print_sld(tt_second_level_descriptor_t sld);

#endif //__C__

#ifdef __ASSEMBLY__

.extern init_asm
.extern fini_asm

.extern init_c
.extern fini_c

.extern run_c

#endif //__ASSEMBLY__

#endif //__PGTBLMOD_MAIN_H__
