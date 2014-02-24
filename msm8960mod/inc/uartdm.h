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

#ifndef __MSM8960MOD_UARTDM_H__
#define __MSM8960MOD_UARTDM_H__

#include <defines.h>
#include <types.h>

#define UARTDM_MR1_OFFSET         0x0 // Mode Register 1
#define UARTDM_MR2_OFFSET         0x4 // Mode Register 2
#define UARTDM_CSR_OFFSET         0x8 // Clock Selection Register
#define UARTDM_TF_OFFSET          0x70 // Transmit FIFO Register
#define UARTDM_TF_2_OFFSET        0x74 // Transmit FIFO Register 2
#define UARTDM_TF_3_OFFSET        0x78 // Transmit FIFO Register 3
#define UARTDM_TF_4_OFFSET        0x7C // Transmit FIFO Register 4
#define UARTDM_CR_OFFSET          0x10 // Command Register
#define UARTDM_IMR_OFFSET         0x14 // Interrupt Mask Register
#define UARTDM_IPR_OFFSET         0x18 // Interrupt Programming Register
#define UARTDM_TFWR_OFFSET        0x1C // Transmit FIFO Watermark Register
#define UARTDM_RFWR_OFFSET        0x20 // Receive FIFO Watermark Register
#define UARTDM_HCR_OFFSET         0x24 // Hunt Character Register
#define UARTDM_MREG_OFFSET        0x28 // M Value Register
#define UARTDM_NREG_OFFSET        0x2C // N Value Register
#define UARTDM_DREG_OFFSET        0x30 // D Value Register
#define UARTDM_MNDREG_OFFSET      0x34 // M, N, D Extra Value Register
#define UARTDM_IDRA_OFFSET        0x38 // IDRA Register
#define UARTDM_DMEN_OFFSET        0x3C // Data Mover Enable Register
#define UARTDM_DMTX_OFFSET        0x40 // Data Mover Number Words Received Register
#define UARTDM_BADR_OFFSET        0x44 // Data Mover Base Address Register
#define UARTDM_TESTSL_OFFSET      0x48
#define UARTDM_MISR_MODE_OFFSET   0x60
#define UARTDM_MISR_RESET_OFFSET  0x64
#define UARTDM_MISR_EXPORT_OFFSET 0x68
#define UARTDM_MISR_VAL_OFFSET    0x6C
#define UARTDM_SR_OFFSET          0x8  // Status Register
#define UARTDM_RF_OFFSET          0x70 // Receive FIFO Register
#define UARTDM_RF_2_OFFSET        0x74 // Receive FIFO Register 2
#define UARTDM_RF_3_OFFSET        0x78 // Receive FIFO Register 3
#define UARTDM_RF_4_OFFSET        0x7C // Receive FIFO Register 4
#define UARTDM_MISR_OFFSET        0x10 // Masked Interrupt Status Register
#define UARTDM_ISR_OFFSET         0x14 // Interrupt Status Register
#define UARTDM_DMRX_OFFSET        0x38
#define UARTDM_TXFS_OFFSET        0x4C // Transmit FIFO State Register
#define UARTDM_RXFS_OFFSET        0x50 // Receive FIFO State Register

#define UARTDM_TX_TIMEOUT_PERIOD 0x10000
#define UARTDM_RX_TIMEOUT_PERIOD 0x10000

#ifdef __C__

typedef union uartdm_generic_register uartdm_generic_register_t;
typedef union uartdm_generic_register uartdm_unused_register_t;
typedef union uartdm_mode_register_1 uartdm_mode_register_1_t;
typedef union uartdm_mode_register_2 uartdm_mode_register_2_t;
typedef union uartdm_clock_selection_register uartdm_clock_selection_register_t;
typedef union uartdm_generic_register uartdm_transmit_fifo_register_t;
typedef union uartdm_generic_register uartdm_receive_fifo_register_t;
typedef union uartdm_command_register uartdm_command_register_t;
typedef union uartdm_interrupt_mask_register uartdm_interrupt_mask_register_t;
typedef union uartdm_interrupt_programming_register uartdm_interrupt_programming_register_t;
typedef union uartdm_tx_fifo_watermark_register uartdm_tx_fifo_watermark_register_t;
typedef union uartdm_rx_fifo_watermark_register uartdm_rx_fifo_watermark_register_t;
typedef union uartdm_hunt_character_register uartdm_hunt_character_register_t;
typedef union uartdm_m_register uartdm_m_register_t;
typedef union uartdm_n_register uartdm_n_register_t;
typedef union uartdm_d_register uartdm_d_register_t;
typedef union uartdm_mnd_register uartdm_mnd_register_t;
typedef union uartdm_irda_register uartdm_irda_register_t;
typedef union uartdm_data_mover_enable_register uartdm_data_mover_enable_register_t;
typedef union uartdm_data_mover_tx_length_register uartdm_data_mover_tx_length_register_t;
typedef union uartdm_data_mover_base_address_register uartdm_data_mover_base_address_register_t;
typedef union uartdm_status_register uartdm_status_register_t;
typedef union uartdm_masked_interrupt_status_register uartdm_masked_interrupt_status_register_t;
typedef union uartdm_interrupt_status_register uartdm_interrupt_status_register_t;
typedef union uartdm_data_mover_rx_length_register uartdm_data_mover_rx_length_register_t;
typedef union uartdm_tx_fifo_state_register uartdm_tx_fifo_state_register_t;
typedef union uartdm_rx_fifo_state_register uartdm_rx_fifo_state_register_t;

typedef volatile struct uartdm_block uartdm_block_t;

union uartdm_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

union uartdm_mode_register_1 {
	struct {
		u32_t auto_rfr_level0 :5;
		u32_t cts_ctl         :1;
		u32_t rx_rdy_ctl      :1;
		u32_t auto_rfr_level1 :2;
		u32_t res_0           :2;
	} fields;
	u32_t all;
};

union uartdm_mode_register_2 {
	struct {
		u32_t parity_mode   :2;
		u32_t stop_bit_len  :2;
		u32_t bits_per_char :2;
		u32_t error_mode    :1;
		u32_t num_char      :1;
	} fields;
	u32_t all;
};

union uartdm_clock_selection_register {
	struct {
		u32_t rx_clk_sel :4;
		u32_t tx_clk_sel :4;
	} fields;
	u32_t all;
};

union uartdm_command_register {
	struct {
		u32_t rx_en           :1;
		u32_t rx_disable      :1;
		u32_t tx_en           :1;
		u32_t tx_disable      :1;
		u32_t command_channel :4;
		u32_t cr_prot_en      :1;
	} fields;
	u32_t all;
};

union uartdm_interrupt_mask_register {
	struct {
		u32_t txlev :1;
		u32_t rxhunt :1;
		u32_t rxbreak :1;
		u32_t rxstale :1;
		u32_t rxlev :1;
		u32_t delta_cts :1;
		u32_t current_cts :1;
	} fields;
	u32_t all;
};

union uartdm_interrupt_programming_register {
	struct {
		u32_t stale_timeout_lsb :5;
		u32_t res_0 :1;
		u32_t sample_data :1;
		u32_t stale_timeout_msb :4;
	} fields;
	u32_t all;
};

union uartdm_tx_fifo_watermark_register {
	struct {
		u32_t tfw :7;
	} fields;
	u32_t all;
};

union uartdm_rx_fifo_watermark_register {
	struct {
		u32_t rfw :7;
	} fields;
	u32_t all;
};

union uartdm_hunt_character_register {
	struct {
		u32_t data :8;
	} fields;
	u32_t all;
};

union uartdm_m_register {
	struct {
		u32_t data :12;
	} fields;
	u32_t all;
};

union uartdm_n_register {
	struct {
		u32_t nreg :12;
	} fields;
};

union uartdm_d_register {
	struct {
		u32_t data :12;
	} fields;
	u32_t all;
};

union uartdm_mnd_register {
	struct {
		u32_t dreg_lsb :2;
		u32_t nreg_lsb :3;
		u32_t mreg_lsb :1;
	} fields;
	u32_t all;
};

union uartdm_irda_register {
	struct {
		u32_t irda_en :1;
		u32_t invert_irda_rx :1;
		u32_t invert_irda_tx :1;
		u32_t irda_loopback :1;
		u32_t medium_rate_en :1;
	} fields;
	u32_t all;
};

union uartdm_data_mover_enable_register {
	struct {
		u32_t tx_dm_en :1;
		u32_t rx_dm_en :1;
	} fields;
	u32_t all;
};

union uartdm_data_mover_tx_length_register {
	struct {
		u32_t tx_dm_last_char_length :2;
		u32_t tx_dm_word_length :14;
	} fields;
	u32_t all;
};

union uartdm_data_mover_base_address_register {
	struct {
		u32_t unused_0 :2;
		u32_t rx_base_addr :5;
	} fields;
	u32_t all;
};

union uartdm_status_register {
	struct {
		u32_t rxrdy :1;
		u32_t rxfull :1;
		u32_t txrdy :1;
		u32_t txemt :1;
		u32_t overrun :1;
		u32_t par_frame_err :1;
		u32_t rx_break :1;
		u32_t hunt_char :1;
	} fields;
	u32_t all;
};

union uartdm_masked_interrupt_status_register {
	struct {
		u32_t misr :7;
	} fields;
	u32_t all;
};

union uartdm_interrupt_status_register {
	struct {
		u32_t txlev :1;
		u32_t rxhunt :1;
		u32_t rxbreak :1;
		u32_t rxstale :1;
		u32_t rxlev :1;
		u32_t delta_cts :1;
		u32_t current_cts :1;
	} fields;
	u32_t all;
};

union uartdm_data_mover_rx_length_register {
	struct {
		u32_t rx_dm_length :16;
	} fields;
	u32_t all;
};

union uartdm_tx_fifo_state_register {
	struct {
		u32_t tx_fifo_state :7;
	} fields;
	u32_t all;
};

union uartdm_rx_fifo_state_register {
	struct {
		u32_t rx_fifo_state :7;
	} fields;
	u32_t all;
};

struct uartdm_block {
	uartdm_mode_register_1_t mr1;                           // UARTDM_MR1_OFFSET = 0x0
	uartdm_mode_register_2_t mr2;                           // UARTDM_MR2_OFFSET = 0x4
	union {
		uartdm_clock_selection_register_t csr;              // UARTDM_CSR_OFFSET = 0x8
		uartdm_status_register_t sr;                        // UARTDM_SR_OFFSET = 0x8
	};
	uartdm_unused_register_t unused_0;
	union {
		uartdm_command_register_t cr;                       // UARTDM_CR_OFFSET = 0x10
		uartdm_masked_interrupt_status_register_t misr;     // UARTDM_MISR_OFFSET = 0x10
	};
	union {
		uartdm_interrupt_mask_register_t imr;               // UARTDM_IMR_OFFSET = 0x14
		uartdm_interrupt_status_register_t isr;             // UARTDM_ISR_OFFSET = 0x14
	};
	uartdm_interrupt_programming_register_t ipr;            // UARTDM_IPR_OFFSET = 0x18
	uartdm_tx_fifo_watermark_register_t txwr;               // UARTDM_TFWR_OFFSET = 0x1C
	uartdm_rx_fifo_watermark_register_t rxwr;               // UARTDM_RFWR_OFFSET = 0x20
	uartdm_hunt_character_register_t hcr;                   // UARTDM_HCR_OFFSET = 0x24
	uartdm_m_register_t m;                                  // UARTDM_MREG_OFFSET = 0x28
	uartdm_n_register_t n;                                  // UARTDM_NREG_OFFSET = 0x2C
	uartdm_d_register_t d;                                  // UARTDM_DREG_OFFSET = 0x30
	uartdm_mnd_register_t mnd;                              // UARTDM_MNDREG_OFFSET = 0x34
	union {
		uartdm_irda_register_t irda;                        // UARTDM_IDRA_OFFSET = 0x38
		uartdm_data_mover_rx_length_register_t dmrx;        // UARTDM_DMRX_OFFSET = 0x38
	};
	uartdm_data_mover_enable_register_t dmen;               // UARTDM_DMEN_OFFSET = 0x3C
	uartdm_data_mover_tx_length_register_t dmtx;            // UARTDM_DMTX_OFFSET = 0x40
	uartdm_data_mover_base_address_register_t badr;         // UARTDM_BADR_OFFSET = 0x44
	uartdm_generic_register_t testsl;                       // UARTDM_TESTSL_OFFSET = 0x48
	uartdm_tx_fifo_state_register_t txfs;                   // UARTDM_TXFS_OFFSET = 0x4C
	uartdm_rx_fifo_state_register_t rxfs;                   // UARTDM_RXFS_OFFSET = 0x50
	uartdm_unused_register_t unused_1[(UARTDM_MISR_MODE_OFFSET - (UARTDM_RXFS_OFFSET + 1)) / BYTES_PER_LONG];
	uartdm_generic_register_t misr_mode;                    // UARTDM_MISR_MODE_OFFSET = 0x60
	uartdm_generic_register_t misr_reset;                   // UARTDM_MISR_RESET_OFFSET = 0x64
	uartdm_generic_register_t misr_export;                  // UARTDM_MISR_EXPORT_OFFSET = 0x68
	uartdm_generic_register_t misr_val;                     // UARTDM_MISR_VAL_OFFSET = 0x6C
	uartdm_unused_register_t unused_2[(UARTDM_TF_OFFSET - (UARTDM_MISR_VAL_OFFSET + 1)) / BYTES_PER_LONG];
	union {
		uartdm_transmit_fifo_register_t tf;                 // UARTDM_TF_OFFSET = 0x70
		uartdm_receive_fifo_register_t rf;                  // UARTDM_RF_OFFSET = 0x70
	};
	union {
		uartdm_transmit_fifo_register_t tf_2;               // UARTDM_TF_2_OFFSET = 0x74
		uartdm_receive_fifo_register_t rf_2;                // UARTDM_RF_2_OFFSET = 0x74
	};
	union {
		uartdm_transmit_fifo_register_t tf_3;              // UARTDM_TF_3_OFFSET = 0x78
		uartdm_receive_fifo_register_t rf_3;               // UARTDM_RF_3_OFFSET = 0x78
	};
	union {
		uartdm_transmit_fifo_register_t tf_4;              // UARTDM_TF_4_OFFSET = 0x7C
		uartdm_receive_fifo_register_t rf_4;               // UARTDM_RF_4_OFFSET = 0x7C
	};
} PACKED;

result_t uartdm_init(uartdm_block_t *block, size_t options);
result_t uartdm_fini(uartdm_block_t *block);

result_t uartdm_set_clock(uartdm_block_t *block);

result_t uartdm_write(uartdm_block_t *block, u8_t *buffer, size_t size);
result_t uartdm_read(uartdm_block_t *block, u8_t *buffer, size_t size);

result_t uartdm_putc(uartdm_block_t *block, u8_t c);
result_t uartdm_getc(uartdm_block_t *block, u8_t *c);

#endif //__C__

#endif //__MSM8960MOD_UART_H__
