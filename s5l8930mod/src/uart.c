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
#include <socmod/map.h>
#include <socmod/uart.h>

#include <stdlib/check.h>

result_t uart_init(uart_block_t *block, size_t options) {

	UNUSED_VARIABLE(block);

	UNUSED_VARIABLE(options);

	// TODO: Stuff to init the uart block
	// I think polling mode is all that is needed.
	// The PCLK, UBRDIV and UDIVSLOT are the things
	// that are stopping this right now. It is going
	// to require a lot more  reading before I can
	// do this from scratch.

	// FIXME: for now we will rely on the loader to
	// setup the serial port correctly for us

	return SUCCESS;
}

result_t uart_fini(uart_block_t *block) {

	UNUSED_VARIABLE(block);

	// TODO: I'm not sure if there will ever be anything
	// that needs to be done here. Maybe backup the old
	// uart_block during init and restore the state here.

	return SUCCESS;
}

result_t uart_get_rx_interrupt_status(uart_block_t *block, bool_t *status) {

	*status = block->uintp.fields.rxd;

	return SUCCESS;
}

result_t uart_acknowledge_rx_interrupt(uart_block_t *block) {

	block->uintp.fields.rxd = TRUE;

	return SUCCESS;
}

result_t uart_get_tx_interrupt_status(uart_block_t *block, bool_t *status) {

	*status = block->uintp.fields.txd;

	return SUCCESS;
}

result_t uart_acknowledge_tx_interrupt(uart_block_t *block) {

	block->uintp.fields.txd = TRUE;

	return SUCCESS;
}

result_t uart_set_clock(uart_block_t *block) {

	UNUSED_VARIABLE(block);

	// TODO: lots of freq and clock stuff.

	return FAILURE;
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

result_t uart_read(uart_block_t *block, u8_t *buffer, size_t size) {

	size_t i;

	for(i = 0; i < size; i++) {
		if(uart_getc(block, &(buffer[i])) != SUCCESS) {
			return FAILURE;
		}
	}

	return FAILURE;
}

result_t uart_putc(uart_block_t *block, u8_t c) {

	size_t i;

	for(i = 0; i < UART_TX_TIMEOUT_PERIOD; i++) {
		if(block->utrstat.fields.tbe == TRUE) {
			block->utxh.u8 = c;
			return SUCCESS;
		}
	}

	return FAILURE;
}

result_t uart_getc(uart_block_t *block, u8_t *c) {

	size_t i;

	for(i = 0; i < UART_RX_TIMEOUT_PERIOD; i++) {
		if(block->utrstat.fields.rbdr == TRUE) {
			*c = block->urxh.u8;
			return SUCCESS;
		}
	}

	return FAILURE;
}
