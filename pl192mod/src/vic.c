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
#include <vicmod/vic.h>

result_t vic_init(vic_block_t *block, size_t options) {

	UNUSED_VARIABLE(block);
	UNUSED_VARIABLE(options);

	// TODO: something nice to set the developers mind
	// at ease.

	return SUCCESS;
}
result_t vic_fini(vic_block_t *block) {

	UNUSED_VARIABLE(block);
	// TODO: something that makes the developer think
	// that everything will be back to the way it was before
	// the library was used.

	return SUCCESS;
}

result_t vic_irq_is_set(vic_block_t *block, size_t number, bool_t *status) {

	if(block == NULL) { return FAILURE; }

	if(block->vicirqstatus.all & (1 << number)) {
		*status = TRUE;
	}
	else {
		*status = FALSE;
	}

	return SUCCESS;
}
result_t vic_irq_is_clear(vic_block_t *block, size_t number, bool_t *status) {
	if(block == NULL) { return FAILURE; }

	if(block->vicirqstatus.all & (1 << number)) {
		*status = FALSE;
	}
	else {
		*status = TRUE;
	}

	return SUCCESS;
}

result_t vic_fiq_is_set(vic_block_t *block, size_t number, bool_t *status) {

	if(block == NULL) { return FAILURE; }

	if(block->vicfiqstatus.all & (1 << number)) {
		*status = TRUE;
	}
	else {
		*status = FALSE;
	}

	return SUCCESS;
}
result_t vic_fiq_is_clear(vic_block_t *block, size_t number, bool_t *status) {

	if(block == NULL) { return FAILURE; }

	if(block->vicfiqstatus.all & (1 << number)) {
		*status = TRUE;
	}
	else {
		*status = FALSE;
	}

	return SUCCESS;
}

result_t vic_interrupt_enable(vic_block_t *block, size_t number) {

	if(block == NULL) { return FAILURE; }

	block->vicintenable.all |= (1 << number);

	return SUCCESS;
}
result_t vic_interrupt_clear(vic_block_t *block, size_t number) {

	if(block == NULL) { return FAILURE; }

	block->vicintenclear.all &= ~(1 << number);

	return SUCCESS;
}

result_t vic_software_interrupt_enable(vic_block_t *block, size_t number) {

	if(block == NULL) { return FAILURE; }

	block->vicsoftint.all |= (1 << number);

	return SUCCESS;
}
result_t vic_software_interrupt_clear(vic_block_t *block, size_t number) {

	if(block == NULL) { return FAILURE; }

	block->vicsoftintclear.all &= ~(1 << number);

	return SUCCESS;
}
