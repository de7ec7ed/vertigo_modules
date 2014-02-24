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

#include <armv7lib/vmsa/tt.h>

#include <dbglib/gen.h>

#include <fxplib/gen.h>

#include <stdlib/check.h>
#include <stdlib/string.h>

#include <linmod/lin.h>

DBG_DEFINE_VARIABLE(lin_dbg, DBG_LEVEL_3);

result_t lin_find_function(void *start, size_t size, u8_t *signature, size_t signature_size, void **address) {

	u8_t *buffer = (u8_t *)start;
	size_t i;

	DBG_LOG_FUNCTION(lin_dbg, DBG_LEVEL_3);

	for(i = 0; i < size; i++) {
		if(memcmp(&(buffer[i]), signature, signature_size) == 0) {
			*address = &(buffer[i]);
			return SUCCESS;
		}
	}

	return FAILURE;
}

result_t lin_get_printk_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_printk);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_call_usermodehelper_setup_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_call_usermodehelper_setup);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_call_usermodehelper_exec_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_call_usermodehelper_exec);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_schedule_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_schedule);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_create_proc_entry_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_create_proc_entry);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_remove_proc_entry_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_remove_proc_entry);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_remap_pfn_range_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_remap_pfn_range);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_kmalloc_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_kmalloc);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_kfree_address(void **address) {

	*address = *(void **)gen_add_base(&lin_address_kfree);

	CHECK_NOT_NULL(*address, "*address is null", *address, lin_dbg, DBG_LEVEL_2)
		return FAILURE;
	CHECK_END

	return SUCCESS;
}

result_t lin_get_debug_level(size_t *level) {

	DBG_LOG_FUNCTION(lin_dbg, DBG_LEVEL_3);

	DBG_GET_VARIABLE(lin_dbg, *level);

	return SUCCESS;
}

result_t lin_set_debug_level(size_t level) {

	DBG_LOG_FUNCTION(lin_dbg, DBG_LEVEL_3);

	DBG_SET_VARIABLE(lin_dbg, level);

	return SUCCESS;
}
