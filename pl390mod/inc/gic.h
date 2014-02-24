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

#ifndef __PL390MOD_GIC_H__
#define __PL390MOD_GIC_H__

#include <defines.h>
#include <types.h>

#define GIC_ICDDCR_OFFSET  0x0 // Distributor Control Register
#define GIC_ICDICTR_OFFSET 0x4 // Interrupt Controller Type Register
#define GIC_ICDIIDR_OFFSET 0x8 // Distributor Implementer Identification Register
#define GIC_RESERVED_0_OFFSET 0xC // Reserved 0
#define GIC_ICDISR_OFFSET  0x80 // Interrupt Security Registers
#define GIC_ICDISER_OFFSET 0x100 // Enable Set Registers
#define GIC_ICDICER_OFFSET 0x180 // Enable Clear Registers
#define GIC_ICDISPR_OFFSET 0x200 // Pending Set Registers
#define GIC_ICDICPR_OFFSET 0x280 // Pending Clear Registers
#define GIC_ICDABR_OFFSET 0x300 // Active Status Registers
#define GIC_RESERVED_1_OFFSET 0x380 // Reserved 1
#define GIC_ICDIPR_OFFSET 0x400 // Priority Level Registers

#define GIC_NUMBER_PRIMECELL_IDENTIFICATION_REGISTERS 4

#ifdef __C__


typedef union gic_distributor_control_register gic_distributor_control_register_t;
typedef union gic_interrupt_control_type_register gic_interrupt_control_type_register_t;
typedef union gic_distributor_implementer_identification_register gic_distributor_implementer_identification_register_t;
typedef union gic_generic_register gic_interrupt_security_register_t;
typedef union gic_generic_register gic_enable_set_register_t;
typedef union gic_generic_register gic_enable_clear_register_t;
typedef union gic_generic_register gic_pending_set_register_t;
typedef union gic_generic_register gic_pending_clear_register_t;
typedef union gic_generic_register gic_active_status_register_t;
typedef union gic_generic_register gic_priority_level_register_t;

typedef union gic_generic_register gic_reserved_register_t;
typedef union gic_generic_register gic_generic_register_t;

union gic_distributor_implementer_identification_register {
	struct {
		u32_t implementer :12; // Contains the JEP106 code of the company that implemented the GIC Distributor
		u32_t revision    :4;  // An implementation defined revision number
		u32_t variant     :4;  // An implementation defined variant number
		u32_t res_0       :4;
		u32_t productid   :8;  // An implementation defined product identifier
	} fields;
	u32_t all;
};

union gic_interrupt_control_type_register {
	struct {
		u32_t itlinesnumber :5; // Indicates the maximum number of interrupts that the GIC supports
		u32_t cpunumber     :3; // Indicates the number of implemented CPU interfaces
		u32_t res_0         :2;
		u32_t securityextn  :1; // Indicates whether the GIC implements the Security Extensions
		u32_t lspi          :5; // If the GIC implements the Security Extensions, the value of this field is the maximum number of implemented lockable SPIs
		u32_t res_1         :17;
	} fields;
	u32_t all;
};

union gic_distributor_control_register {
	struct {
		u32_t enable :1;
		u32_t res_0 :31;
	} fields;
	u32_t all;
};

union vic_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

struct gic_distributor_block {
	gic_distributor_control_register_t icddcr;
	gic_interrupt_control_type_register_t icdictr;
	gic_distributor_implementer_identification_register_t icdiicr;
	gic_reserved_register_t reserved_0[(GIC_ICDISR_OFFSET - GIC_RESERVED_0_OFFSET) / BYTES_PER_LONG];
	gic_interrupt_security_register_t icdisr[(GIC_ICDISER_OFFSET - GIC_ICDISR_OFFSET) / BYTES_PER_LONG];
	gic_enable_set_register_t icdiser[(GIC_ICDICER_OFFSET - GIC_ICDISER_OFFSET) / BYTES_PER_LONG];
	gic_enable_clear_register_t icdicer[(GIC_ICDISPR_OFFSET - GIC_ICDICER_OFFSET) / BYTES_PER_LONG];
	gic_pending_set_register_t icdispr[(GIC_ICDICPR_OFFSET - GIC_ICDISPR_OFFSET) / BYTES_PER_LONG];
	gic_pending_clear_register_t icdiscr[(GIC_ICDABR_OFFSET - GIC_ICDICPR_OFFSET) / BYTES_PER_LONG];
	gic_active_status_register_t icdabr[(GIC_RESERVED_1_OFFSET - GIC_ICDABR_OFFSET) / BYTES_PER_LONG];
	gic_reserved_register_t reserved_1[(GIC_asdf - GIC_RESERVED_1_OFFSET) / BYTES_PER_LONG]
} PACKED;

struct gic_cpu_interface_block {
	//gic_primecell_identification_register_t gicpcellid[GIC_NUMBER_PRIMECELL_IDENTIFICATION_REGISTERS];
} PACKED;

result_t gic_init(gic_distributor_block_t *distributor, gic_cpu_interface_block_t cpu_interface, size_t options);
result_t gic_fini(gic_distributor_t *distributor, gic_cpu_interface_block_t cpu_interface);

#endif //__C__

#endif //__PL390MOD_GIC_H__
