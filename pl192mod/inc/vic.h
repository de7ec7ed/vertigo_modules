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

#ifndef __PL192MOD_VIC_H__
#define __PL192MOD_VIC_H__

#include <types.h>

#define VIC_NUMBER_VECTOR_ADDRESS_REGISTERS           32
#define VIC_NUMBER_PRIORITY_REGISTERS                 32
#define VIC_NUMBER_PRIMECELL_IDENTIFICATION_REGISTERS 4

#ifdef __C__

/// VICIRQSTATUS: Shows the status of the interrupts after masking by the VICINTENABLE and VICINTSELECT Registers.
typedef union vic_generic_register vic_irq_status_register_t;

/// VICFIQSTATUS: Shows the status of the FIQ interrupts after masking by the VICINTENABLE and VICINTSELECT Registers.
typedef union vic_generic_register vic_fiq_status_register_t;

/// VICRAWINTR: Shows the status of the interrupts before masking by the Enable Registers.
typedef union vic_generic_register vic_raw_interrupt_status_register_t;

/// VICINTSELECT: Shows the status of the interrupts before masking by the Enable Registers.
typedef union vic_generic_register vic_interrupt_select_register_t;

/// VICINTENABLE: Enables the interrupt request lines, which allow the interrupts to reach the processor.
typedef union vic_generic_register vic_interrupt_enable_register_t;

/// VICINTENCLEAR: Clears corresponding bits in the VICINTENABLE Register.
typedef union vic_generic_register vic_interrupt_clear_register_t;

/// VICSOFTINT: Setting a bit HIGH generates a software interrupt for the selected source before interrupt masking.
typedef union vic_generic_register vic_software_interrupt_register_t;

/// VICSOFTINTCLEAR: Clears corresponding bits in the VICSOFTINT Register.
typedef union vic_generic_register vic_software_interrupt_clear_register_t;

/// VICPROTECTION: Enables or disables protected register access.
typedef union vic_protection_register vic_protection_register_t;

/// VICADDRESS: Contains the address of the currently active ISR, with reset value 0x00000000.
typedef void * vic_address_register_t;

/// VICSWPRIORITYMASK: Contains the mask value for the interrupt priority levels.
typedef union vic_software_priority_mask_register vic_software_priority_mask_register_t;

/// VICVECTADDR: Contains ISR vector addresses.
typedef void * vic_vector_address_register_t;

/// VICVECTPRIORITY: select the interrupt priority level for the 32 vectored interrupt sources, and the daisy chain input.
typedef union vic_vector_priority_register vic_vector_priority_register_t;

/// VICPERIPHID: The read-only registers provide the following options of the peripheral: part number, designer, revision number and configuration.
typedef union vic_peripheral_identification_register vic_peripheral_identification_register_t;

/// VICPCELLID: The register is used as a standard cross-peripheral identification system.
typedef u8_t vic_primecell_identification_register_t;

typedef volatile struct vic_block vic_block_t;

union vic_peripheral_identification_register {
	struct {
		u32_t pn :12; ///< Part number: This identifies the peripheral. The three digit product code 0x192 is used for the PrimeCell VIC.
		u32_t d  :8;  ///< Designer: This is the identification of the designer. ARM Limited is 0x41 (ASCII A).
		u32_t rn :4;  ///< Revision number: This is the revision number of the peripheral. The revision number starts from 0 and the value is revision-dependent.
		u32_t c  :8;  ///< Configuration: This is the configuration option of the peripheral. The configuration value is 0.
	} fields;
	u32_t all;
};

union vic_vector_priority_register {
	struct {
		u32_t vp :4;     ///< VectPriority: Selects vectored interrupt priority level.
		u32_t res_0 :28; ///< Reserved
	} fields;
	u32_t all;
};

union vic_software_priority_mask_register {
	struct {
		u16_t swpm;  ///< SWPriorityMask: Controls software masking of the 16 interrupt priority levels: 0 = interrupt priority level is masked 1 = interrupt priority level is not masked (reset).
		u16_t res_0; ///< Reserved
	} fields;
	u32_t all;
};

union vic_protection_register {
	struct {
		u32_t p :1; ///< Enables or disables protected register access: 0 = protection mode disabled (reset) 1 = protection mode enabled.
	} fields;
};

union vic_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

struct vic_block {
	vic_irq_status_register_t vicirqstatus;
	vic_fiq_status_register_t vicfiqstatus;
	vic_raw_interrupt_status_register_t vicrawintr;
	vic_interrupt_select_register_t vicintselect;
	vic_interrupt_enable_register_t vicintenable;
	vic_interrupt_clear_register_t vicintenclear;
	vic_software_interrupt_register_t vicsoftint;
	vic_software_interrupt_clear_register_t vicsoftintclear;
	vic_protection_register_t vicprotection;
	vic_software_priority_mask_register_t vicswproritymask;
	vic_vector_priority_register_t vicprioritydaisy;
	vic_vector_address_register_t vicvectaddr[VIC_NUMBER_VECTOR_ADDRESS_REGISTERS];
	vic_vector_priority_register_t vicvectpriority[VIC_NUMBER_PRIORITY_REGISTERS];
	vic_vector_address_register_t vicaddress;
	vic_peripheral_identification_register_t vicperiphid;
	vic_primecell_identification_register_t vicpcellid[VIC_NUMBER_PRIMECELL_IDENTIFICATION_REGISTERS];
} PACKED;

result_t vic_init(vic_block_t *block, size_t options);
result_t vic_fini(vic_block_t *block);

result_t vic_irq_is_set(vic_block_t *block, size_t number, bool_t *status);
result_t vic_irq_is_clear(vic_block_t *block, size_t number, bool_t *status);

result_t vic_fiq_is_set(vic_block_t *block, size_t number, bool_t *status);
result_t vic_fiq_is_clear(vic_block_t *block, size_t number, bool_t *status);

result_t vic_interrupt_enable(vic_block_t *block, size_t number);
result_t vic_interrupt_clear(vic_block_t *block, size_t number);

result_t vic_software_interrupt_enable(vic_block_t *block, size_t number);
result_t vic_software_interrupt_clear(vic_block_t *block, size_t number);

#endif //__C__

#endif //__PL192MOD_VIC_H__
