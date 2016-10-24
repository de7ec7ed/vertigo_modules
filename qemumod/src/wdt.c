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
#include <types.h>

#include <socmod/map.h>
#include <socmod/wdt.h>

result_t wdt_init(wdt_block_t *block, size_t options) {

	UNUSED_VARIABLE(block);

	UNUSED_VARIABLE(options);

	return SUCCESS;
}

result_t wdt_fini(wdt_block_t *block) {

	UNUSED_VARIABLE(block);

	return SUCCESS;
}

result_t wdt_enable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_disable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_acknowledge_interrupt(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_interrupt_disable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_interrupt_enable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_reset_disable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_reset_enable(wdt_block_t *block) {

	return SUCCESS;
}

result_t wdt_get_data(wdt_block_t *block, size_t *data) {

	return SUCCESS;
}

result_t wdt_set_data(wdt_block_t *block, size_t data) {

	return SUCCESS;
}
result_t wdt_get_count(wdt_block_t *block, size_t *count) {

	return SUCCESS;
}

result_t wdt_set_count(wdt_block_t *block, size_t count) {

	return SUCCESS;
}

result_t wdt_get_physical_address(void **pa) {

	*pa = (void *)MAP_WDT_ADDRESS;

	return SUCCESS;
}

result_t wdt_get_size(size_t *size) {

	*size = MAP_WDT_SIZE;

	return SUCCESS;
}
