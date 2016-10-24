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

#include <kernel/mmu.h>

#include <socmod/map.h>
#include <socmod/uart.h>

result_t uart_init(uart_block_t *block, size_t options) {

	UNUSED_VARIABLE(block);

	UNUSED_VARIABLE(options);

	return SUCCESS;
}

result_t uart_fini(uart_block_t *block) {

	UNUSED_VARIABLE(block);

	return SUCCESS;
}

result_t uart_write(uart_block_t *block, u8_t *buffer, size_t size) {

	size_t i;

	for(i = 0; i < size; i++) {
		if(uart_putc(block, buffer[i]) != SUCCESS) {
			return FAILURE;
		}
	}

	return SUCCESS;
}

result_t uart_putc(uart_block_t *block, u8_t c) {

	// access the union directly forces a read followed by a write
	// these registers are write-only
	*(volatile u8_t *)&(block->put_char) = c;

	return SUCCESS;
}

result_t uart_read(uart_block_t *block, u8_t *buffer, size_t size) {

	size_t i;

	for(i = 0; i < size; i++) {
		if(uart_getc(block, &(buffer[i])) != SUCCESS) {
			return FAILURE;
		}
	}

	return FAILURE;
}

result_t uart_getc(uart_block_t *block, u8_t *c) {

	size_t i;

	for(i = 0; i < UART_RX_TIMEOUT_PERIOD; i++) {
		if(block->bytes_ready.all > 0) {

			// access the union directly forces a read followed by a write
			// these registers are write-only
			*(volatile void **)&(block->data_ptr) = c;
			*(volatile u32_t *)&(block->data_len) = sizeof(*c);

			*(volatile u32_t *)&(block->cmd) = UART_CMD_READ_BUFFER;

			return SUCCESS;
		}
	}

	return FAILURE;
}

result_t uart_get_physical_address(size_t number, void **pa) {

	if(number == 2) {
		*pa = (void *)MAP_UART_2_ADDRESS;
	}
	else {
		return FAILURE;
	}

	return SUCCESS;
}

result_t uart_get_size(size_t number, size_t *size) {

	if(number == 2) {
		*size = MAP_UART_2_SIZE;
	}
	else {
		return FAILURE;
	}

	return SUCCESS;
}


