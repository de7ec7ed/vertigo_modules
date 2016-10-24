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

#ifndef __GMMUMOD_GMMU_H__
#define __GMMUMOD_GMMU_H__

#include <defines.h>
#include <types.h>

#define GMMU_MAP_NO_OPTIONS       0
#define GMMU_MAP_CACHEABLE        (1 << 0)
#define GMMU_MAP_BUFFERABLE       (1 << 1)
#define GMMU_MAP_SPECIFIC_ADDRESS (1 << 2)

#define GMMU_UNMAP_NO_OPTIONS     0

IMPORT bool_t gmmu_supports_1gb_pages(void);
IMPORT bool_t gmmu_supports_2mb_pages(void);

IMPORT result_t gmmu_lookup_va(void *pa, void **va);
IMPORT result_t gmmu_lookup_pa(void *va, void **pa);

IMPORT result_t gmmu_map(void *pa, size_t size, natural_t options, void **va);
IMPORT result_t gmmu_unmap(void *va, size_t size, natural_t options);

IMPORT result_t gmmu_get_debug_level(natural_t *level);
IMPORT result_t gmmu_set_debug_level(natural_t level);
IMPORT result_t gmmu_map_guest_buffer(void *guest_va, natural_t size, void **va);

#endif //__GMMUMOD_GMMU_H__
