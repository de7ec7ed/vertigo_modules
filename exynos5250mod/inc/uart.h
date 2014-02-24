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

#ifndef __EXYNOS5250MOD_UART_H__
#define __EXYNOS5250MOD_UART_H__

#include <config.h>
#include <defines.h>
#include <types.h>

#define UART_DEFAULT 3

#define UART_ULCON_OFFSET    0x0 // Line Control Register
#define UART_UCON_OFFSET     0x4 // Control Register
#define UART_UFCON_OFFSET    0x8 // FIFO Control Register
#define UART_UMCON_OFFSET    0xC // Modem Control Register
#define UART_UTRSTAT_OFFSET  0x10 // TX/RX Status Register
#define UART_UESTAT_OFFSET   0x14 // Error Status Register
#define UART_UFSTAT_OFFSET   0x18 // FIFO Status Register
#define UART_UMSTAT_OFFSET   0x1C // Modem Status Register
#define UART_UTXH_OFFSET     0x20 // Transmit Buffer Register
#define UART_URXH_OFFSET     0x24 // Receive Buffer Register
#define UART_UBAUD_OFFSET    0x28 // Baud Rate Configure Register
#define UART_UDIVSLOT_OFFSET 0x2C // Divisor Slot Register
#define UART_UINTP_OFFSET    0x30 // Interrupt Pending Register
#define UART_UINTSP_OFFSET   0x34 // Interrupt Source Pending Register
#define UART_UINTM_OFFSET    0x38 // Interrupt Mask Register

#define UART_TX_TIMEOUT_PERIOD 0x10000
#define UART_RX_TIMEOUT_PERIOD 0x10000

#ifdef __C__

typedef union uart_line_control_register uart_line_control_register_t;
typedef union uart_control_register uart_control_register_t;
typedef union uart_fifo_control_register uart_fifo_control_register_t;
typedef union uart_modem_control_register uart_modem_control_register_t;
typedef union uart_tx_rx_status_register uart_tx_rx_status_register_t;
typedef union uart_error_status_register uart_error_status_register_t;
typedef union uart_fifo_status_register uart_fifo_status_register_t;
typedef union uart_modem_status_register uart_modem_status_register_t;
typedef union uart_generic_register uart_transmit_buffer_register_t;
typedef union uart_generic_register uart_receive_buffer_register_t;
typedef union uart_generic_register uart_baud_rate_divisor_register_t;
typedef union uart_generic_register uart_divisor_fractional_value_register_t;
typedef union uart_interrupt_register uart_interrupt_pending_register_t;
typedef union uart_interrupt_register uart_interrupt_source_pending_register_t;
typedef union uart_interrupt_register uart_interrupt_mask_register_t;

typedef volatile struct uart_block uart_block_t;

union uart_line_control_register {
	struct {
		u32_t wl    :2; // Word Length
		u32_t nsb   :1; // Number of Stop Bits
		u32_t pm    :3; // Parity Mode
		u32_t irm   :1; // Infra-Red Mode
		u32_t res_0 :1; // Reserved
	} fields;
	u32_t all;
};

union uart_control_register {
	struct {
		u32_t rm    :2; // Receive Mode
		u32_t tm    :2; // Transmit Mode
		u32_t sbs   :1; // Send Break Signal
		u32_t lbm   :1; // Loop-back Mode
		u32_t resie :1; // Rx Error Status Interrupt Enable
		u32_t rtoe  :1; // Rx Time Out Enable
		u32_t rit   :1; // Rx Interrupt Type
		u32_t tit   :1; // Tx Interrupt Type
		u32_t rtdse :1; // Rx DMA FSM to suspend when Rx Time-out occurs
		u32_t rterf :1; // Rx Time-out feature when Rx FIFO
		u32_t riii  :4; // Tx Timeout Interrupt Interval
		u32_t rdbs  :3; // Rx DMA Busrt Size
		u32_t res_0 :1;
		u32_t tdbs  :3; // Tx DMA Burst Size
		u32_t res_1 :9;
	} fields;
	u32_t all;
};

union uart_fifo_control_register {
	struct {
		u32_t fifoe   :1; // FIFO Enable
		u32_t rfifor  :1; // Rx FIFO Reset
		u32_t tfifor  :1; // Tx FIFO Reset
		u32_t res_0   :1; // Reserved
		u32_t rfifotl :3; // Rx FIFO Trigger Level
		u32_t res_1   :1;
		u32_t tfifotl :3; // Tx FIFO Trigger Level
		u32_t res_2   :21;
	} fields;
	u32_t all;
};

union uart_modem_control_register {
	struct {
		u32_t rs    :1; // Request to Send
		u32_t res_0 :2; // Reserved
		u32_t mie   :1; // Modem Interrupt Enable
		u32_t afc   :1; // Auto Flow Control
		u32_t rtstl :3; // RTS Trigger Level
	} fields;
	u32_t all;
};

union uart_tx_rx_status_register {
	struct {
		u32_t rbdr   :1; // Receive Buffer Data Ready
		u32_t tbe    :1; // Transmit Buffer Empty
		u32_t te     :1; // Transmitter Empty
		u32_t rtsc   :1; // Rx Time-out status when read
		u32_t res_0  :4;
		u32_t rdfs   :4; // Current State of Rx DMA FSM
		u32_t tdfs   :4; // Current State of Tx DMA FSM
		u32_t rfcrts :8; // Rx FIFO counter capture value when Rx time-out occurs
		u32_t res_1  :8;
	} fields;
	u32_t all;
};

union uart_error_status_register {
	struct {
		u32_t oe    :1; // Overrun Error
		u32_t pe    :1; // Parity Error
		u32_t fe    :1; // Frame Error
		u32_t bd    :1; // Break Detect
		u32_t res_0 :28;
	} fields;
	u32_t all;
};

union uart_fifo_status_register {
	struct {
		u32_t rfifoc :8; // Rx FIFO Count
		u32_t rfifof :1; // Rx FIFO Full
		u32_t rfifoe :1;  // Rx FIFO Error
		u32_t res_0  :6;
		u32_t tfifoc :8; // Tx FIFO Count
		u32_t tfifof :1; // Tx FIFO Full
		u32_t res_1  :7; // Reserved
	} fields;
	u32_t all;
};

union uart_modem_status_register {
	struct {
		u32_t cs    :1; // Clear to Send
		u32_t res_0 :4; // Reserved
		u32_t dcts  :1; // Delta CTS
		u32_t res_1 :26; // Reserved
	} fields;
	u32_t all;
};

union uart_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

union uart_interrupt_register {
	struct {
		u32_t rxd   :1; // Receive Interrupt Generated
		u32_t error :1; // Error Interrupt Generated
		u32_t txd   :1; // Transmit Interrupt Generated
		u32_t modem :1; // Modem Interrupt Generated
		u32_t res_0 :28;
	} fields;
	u32_t all;
};

struct uart_block {
	uart_line_control_register_t ulcon;
	uart_control_register_t ucon;
	uart_fifo_control_register_t ufcon;
	uart_modem_control_register_t umcon;
	uart_tx_rx_status_register_t utrstat;
	uart_error_status_register_t uerstat;
	uart_fifo_status_register_t ufstat;
	uart_modem_status_register_t umstat;
	uart_transmit_buffer_register_t utxh;
	uart_receive_buffer_register_t urxh;
	uart_baud_rate_divisor_register_t ubrdiv;
	uart_divisor_fractional_value_register_t ufracval;
	uart_interrupt_pending_register_t uintp;
	uart_interrupt_source_pending_register_t uintsp;
	uart_interrupt_mask_register_t uintm;
} PACKED;

result_t uart_init(uart_block_t *block, size_t options);
result_t uart_fini(uart_block_t *block);

result_t uart_get_rx_interrupt_status(uart_block_t *block, bool_t *status);
result_t uart_acknowledge_rx_interrupt(uart_block_t *block);

result_t uart_get_tx_interrupt_status(uart_block_t *block, bool_t *status);
result_t uart_acknowledge_tx_interrupt(uart_block_t *block);

result_t uart_set_clock(uart_block_t *block);

result_t uart_write(uart_block_t *block, u8_t *buffer, size_t size);
result_t uart_read(uart_block_t *block, u8_t *buffer, size_t size);

result_t uart_putc(uart_block_t *block, u8_t c);
result_t uart_getc(uart_block_t *block, u8_t *c);

result_t uart_get_physical_address(size_t number, void **pa);
result_t uart_get_size(size_t number, size_t *size);

#endif //__C__


#endif //__EXYNOS5250MOD_UART_H__

