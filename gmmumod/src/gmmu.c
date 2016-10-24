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

#include <config.h>
#include <defines.h>
#include <types.h>

#include <dbglib/gen.h>
#include <fxplib/gen.h>

#include <armv7lib/gen.h>
#include <armv7lib/vmsa/gen.h>

#include <stdlib/check.h>

#include <kernel/log.h>
#include <kernel/mmu.h>
//#include <kernel/vmx.h>

#include <gmmumod/gmmu.h>

DBG_DEFINE_VARIABLE(gmmu_dbg, DBG_LEVEL_2);

EXPORT bool_t gmmu_supports_1gb_pages(void) {
	return 0;
}

EXPORT bool_t gmmu_supports_2mb_pages(void) {

	return 0;
}

EXPORT result_t gmmu_lookup_va(void *pa, void **va) {

	UNUSED_VARIABLE(pa);
	UNUSED_VARIABLE(va);

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	return FAILURE;
}

EXPORT result_t gmmu_lookup_pa(void *va, void **pa) {

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	if(gen_va_to_pa(*(tt_virtual_address_t*)&va, *(tt_physical_address_t **)&pa) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}

EXPORT result_t gmmu_map(void *pa, size_t size, natural_t options, void **va) {

	UNUSED_VARIABLE(pa);
	UNUSED_VARIABLE(size);
	UNUSED_VARIABLE(options);
	UNUSED_VARIABLE(va);

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	return FAILURE;
}

EXPORT result_t gmmu_unmap(void *va, size_t size, natural_t options) {

	UNUSED_VARIABLE(va);
	UNUSED_VARIABLE(size);
	UNUSED_VARIABLE(options);

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	return FAILURE;
}

EXPORT result_t gmmu_get_debug_level(natural_t *level) {

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	DBG_GET_VARIABLE(gmmu_dbg, *level);

	return SUCCESS;
}

EXPORT result_t gmmu_set_debug_level(natural_t level) {

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	DBG_SET_VARIABLE(gmmu_dbg, level);

	return SUCCESS;
}

EXPORT result_t gmmu_map_guest_buffer(void *guest_va, natural_t size, void **va) {

	void *guest_pa;
	void *tmp_va;
	natural_t i;

	DBG_LOG_FUNCTION(gmmu_dbg, DBG_LEVEL_3);

	size = size + (((natural_t)guest_va) & FOUR_KILOBYTE_MASK);

	DBG_LOG_STATEMENT("guest_va", guest_va, gmmu_dbg, DBG_LEVEL_3);

	// First, get a memory buffer of sufficient size for the whole virtually contiguous buffer
	CHECK_SUCCESS(mmu_find_space(size, (MMU_NO_OPTIONS), (void **)va), "gmmu_map_guest_buffer failed to allocate sufficient buffer size", size, gmmu_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	DBG_LOG_STATEMENT("found space *va", *va, gmmu_dbg, DBG_LEVEL_3);

	// Walk though the buffer in 4kb chuncks
	for (i=0; i<size; i+=FOUR_KILOBYTES) {
		tmp_va = (void *)((natural_t)(guest_va + i) & ~FOUR_KILOBYTE_MASK);

		CHECK_SUCCESS(gmmu_lookup_pa( tmp_va, &guest_pa), "unable to x-late guest va to get_pa", i, gmmu_dbg, DBG_LEVEL_3)
			// In some cases, some pages of the buffer might not be present. Leave them unmapped? Or set them all to phys addr 0?
			continue;
		CHECK_END

		DBG_LOG_STATEMENT("mapping guest_pa", guest_pa, gmmu_dbg, DBG_LEVEL_3);

		tmp_va = (void *)((natural_t)(*va + i) & ~FOUR_KILOBYTE_MASK);

		//CHECK_SUCCESS(mmu_map_page( (void *)guest_pa, tmp_va, MMU_FOUR_KILOBYTE_PAGE, (MMU_SPECIFIC_ADDRESS)), "failed to map the guest page!!", guest_pa, gmmu_dbg, DBG_LEVEL_2)
		CHECK_SUCCESS(mmu_map(*(tt_physical_address_t*)guest_pa, ONE_KILOBYTE*4, MMU_MAP_INTERNAL | MMU_SPECIFIC_ADDRESS, (tt_virtual_address_t *)tmp_va), "failed to map the guest page!!", guest_pa, gmmu_dbg, DBG_LEVEL_2)
			return FAILURE;
		CHECK_END

		DBG_LOG_STATEMENT("mapped to va", tmp_va, gmmu_dbg, DBG_LEVEL_3);
	}

	//Add the page offset
	*va = *va + ((natural_t)guest_va & FOUR_KILOBYTE_MASK);

	DBG_LOG_STATEMENT("returning *va", *va, gmmu_dbg, DBG_LEVEL_3);

	return SUCCESS;
}
