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

#ifndef __QEMUMOD_UART_H__
#define __QEMUMOD_UART_H__

#include <config.h>
#include <defines.h>
#include <types.h>

#define UART_DEFAULT 2

#define UART_PUT_CHAR_OFFSET        0x0
#define UART_BYTES_READY_OFFSET     0x4
#define UART_CMD_OFFSET             0x8
#define UART_DATA_PTR_OFFSET        0x10
#define UART_DATA_LEN_OFFSET        0x14

#define UART_CMD_INT_DISABLE        0x0
#define UART_CMD_INT_ENABLE         0x1
#define UART_CMD_WRITE_BUFFER       0x2
#define UART_CMD_READ_BUFFER        0x3

#define UART_RX_TIMEOUT_PERIOD 0x10000

#ifdef __C__

typedef union uart_generic_register uart_put_char_register_t;
typedef union uart_generic_register uart_bytes_ready_register_t;
typedef union uart_generic_register uart_cmd_register_t;
typedef union uart_generic_register uart_data_ptr_t;
typedef union uart_generic_register uart_data_len_t;
typedef union uart_generic_register uart_reserved_register_t;

typedef volatile struct uart_block uart_block_t;

union uart_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

struct uart_block {
	uart_put_char_register_t put_char;
	uart_bytes_ready_register_t bytes_ready;
	uart_cmd_register_t cmd;
	uart_reserved_register_t reserved_0;
	uart_data_ptr_t data_ptr;
	uart_data_len_t data_len;
} PACKED;

result_t uart_init(uart_block_t *block, size_t options);
result_t uart_fini(uart_block_t *block);

result_t uart_write(uart_block_t *block, u8_t *buffer, size_t size);
result_t uart_putc(uart_block_t *block, u8_t c);

result_t uart_read(uart_block_t *block, u8_t *buffer, size_t size);
result_t uart_getc(uart_block_t *block, u8_t *c);

result_t uart_get_physical_address(size_t number, void **pa);
result_t uart_get_size(size_t number, size_t *size);

#endif //__C__


#endif //__QEMUMOD_UART_H__

