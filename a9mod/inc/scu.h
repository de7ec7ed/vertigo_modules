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

#ifndef __A9MOD_SCU_H__
#define __A9MOD_SCU_H__

#include <defines.h>

#define SCU_CONTROL_REGISTER_OFFSET                         0x0 // SCU Control Register
#define SCU_CONFIGURATION_REGISTER_OFFSET                   0x4 // SCU Configuration Register
#define SCU_CPU_POWER_STATUS_REGISTER_OFFSET                0x8 // SCU CPU Power Status Register
#define SCU_INVALIDATE_ALL_REGISTERS_IN_SECURE_STATE_OFFSET 0xC // SCU Invalidate All Registers in Secure State
#define SCU_FILTERING_START_ADDRESS_REGISTER_OFFSET         0x40 // Filtering Start Address Register
#define SCU_FILTERING_END_ADDRESS_REGISTER_OFFSET           0x44 // Filtering End Address Register
#define SCU_ACCESS_CONTROL_REGISTER_OFFSET                  0x50 // SCU Access Control (SAC) Register
#define SCU_NON_SECURE_ACCESS_CONTROL_REGISTER              0x54 // Non-secure Access Control (SNSAC) Register

#ifdef __C__

typedef union scu_generic_register scu_generic_register_t;
typedef union scu_generic_register scu_unused_register_t;
typedef union scu_control_register scu_control_register_t;
typedef union scu_configuration_register scu_configuration_register_t;
typedef union scu_cpu_power_status_register scu_cpu_power_status_register_t;
typedef union scu_invalidate_all_registers_in_secure_state scu_invalidate_all_registers_in_secure_state_t;
typedef union scu_filtering_start_address_register scu_filtering_start_address_register_t;
typedef union scu_filtering_end_address_register scu_filtering_end_address_register_t;
typedef union scu_access_control_register scu_access_control_register_t;
typedef union scu_non_secure_access_control_register scu_non_secure_access_control_register_t;

typedef volatile struct scu_block scu_block_t;

union scu_generic_register {
	u8_t  u8;
	u16_t u16;
	u32_t all;
};

union scu_control_register {
	struct {
		u32_t scu_enable                       :1;
		u32_t address_filtering_enable         :1;
		u32_t scu_rams_parity_enable           :1;
		u32_t scu_speculative_linefills_enable :1;
		u32_t force_all_device_to_port0_enable :1;
		u32_t scu_standby_enable               :1;
		u32_t ic_standby_enable                :1;
		u32_t res_0                            :25;
	} fields;
	u32_t all;
};

union scu_configuration_register {
	struct {
		u32_t cpu_number    :2;
		u32_t sbz_0         :2;
		u32_t cpus_smp      :4;
		u32_t tag_ram_sizes :8;
		u32_t sbz_1         :16;
	} fields;
	u32_t all;
};

union scu_cpu_power_status_register {
	struct {
		u32_t cpu_0_status :2;
		u32_t sbz_0        :6;
		u32_t cpu_1_status :2;
		u32_t sbz_1        :6;
		u32_t cpu_2_status :2;
		u32_t sbz_2        :6;
		u32_t cpu_3_status :2;
		u32_t sbz_3        :6;

	} fields;
	u32_t all;
};

union scu_invalidate_all_registers_in_secure_state {
	struct {
		u32_t cpu_0_ways :4;
		u32_t cpu_1_ways :4;
		u32_t cpu_2_ways :4;
		u32_t cpu_3_ways :4;
		u32_t res_0      :16;
	} fields;
	u32_t all;
};

union scu_filtering_start_address_register {
	struct {
		u32_t res_0                   :20;
		u32_t filtering_start_address :12;
	} fields;
	u32_t all;
};

union scu_filtering_end_address_register {
	struct {
		u32_t res_0                 :20;
		u32_t filtering_end_address :12;
	} fields;
	u32_t all;
};

union scu_access_control_register {
	struct {
		u32_t cpu_0 :1;
		u32_t cpu_1 :1;
		u32_t cpu_2 :1;
		u32_t cpu_3 :1;
		u32_t sbz_0 :28;
	} fields;
	u32_t all;
};

union scu_non_secure_access_control_register {
	struct {
		u32_t cpu_0_component_access :1;
		u32_t cpu_1_component_access :1;
		u32_t cpu_2_component_access :1;
		u32_t cpu_3_component_access :1;
		u32_t cpu_0_private_timer    :1;
		u32_t cpu_1_private_timer    :1;
		u32_t cpu_2_private_timer    :1;
		u32_t cpu_3_private_timer    :1;
		u32_t cpu_0_global_timer     :1;
		u32_t cpu_1_global_timer     :1;
		u32_t cpu_2_global_timer     :1;
		u32_t cpu_3_global_timer     :1;
		u32_t sbz_0                  :20;
	};
	u32_t all;
};

struct scu_block {
	scu_control_register_t ctrl;                           // SCU_CONTROL_REGISTER_OFFSET = 0x0
	scu_configuration_register_t conf;                     // SCU_CONFIGURATION_REGISTER_OFFSET = 0x4
	scu_cpu_power_status_register_t cpupsr;                // SCU_CPU_POWER_STATUS_REGISTER_OFFSET = 0x8
	scu_invalidate_all_registers_in_secure_state_t iariss; // SCU_INVALIDATE_ALL_REGISTERS_IN_SECURE_STATE_OFFSET = 0xC
	scu_unused_register_t unused_0[(SCU_FILTERING_START_ADDRESS_REGISTER_OFFSET - (SCU_INVALIDATE_ALL_REGISTERS_IN_SECURE_STATE_OFFSET + 1)) / BYTES_PER_LONG];
	scu_filtering_start_address_register_t fsa;            // SCU_FILTERING_START_ADDRESS_REGISTER_OFFSET = 0x40
	scu_filtering_end_address_register_t fea;              // SCU_FILTERING_END_ADDRESS_REGISTER_OFFSET = 0x44
	scu_unused_register_t unused_1[(SCU_ACCESS_CONTROL_REGISTER_OFFSET - (SCU_FILTERING_END_ADDRESS_REGISTER_OFFSET + 1)) / BYTES_PER_LONG];
	scu_access_control_register_t ac;                      // SCU_ACCESS_CONTROL_REGISTER_OFFSET = 0x50
	scu_non_secure_access_control_register_t nsac;         // SCU_NON_SECURE_ACCESS_CONTROL_REGISTER = 0x54
} PACKED;

result_t scu_init(scu_block_t *block, size_t options);
result_t scu_fini(scu_block_t *block);
result_t scu_print(scu_block_t *block);

#endif //__C__

#endif //__A9MOD_SCU_H__
