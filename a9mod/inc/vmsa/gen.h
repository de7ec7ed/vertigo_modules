/* This file is part of VERTIGO.
 *
 * (C) Copyright 2013, Siege Technologies <http://www.siegetechnologies.com>
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

#ifndef __A9MOD_VMSA_GEN_H__
#define __A9MOD_VMSA_GEN_H__

#ifdef __C__

typedef union gen_auxiliary_control_register gen_auxiliary_control_register_t;
typedef union gen_non_secure_access_control_register gen_non_secure_access_control_register_t;

union gen_auxiliary_control_register {
	struct {
		u32_t fw                            :1; // Cache and TLB maintenance broadcast
		u32_t l2_prefetch_enable            :1; // Prefetch hint enable
		u32_t l1_prefetch_enable            :1; // Dside prefetch
		u32_t write_full_line_of_zeros_mode :1; // Enable write full line of zeros mode
		u32_t sbz_0                         :2;
		u32_t smp                           :1; // Signals if the Cortex-A9 processor is taking part in coherency or not
		u32_t excl                          :1; // Exclusive cache bit
		u32_t alloc_in_one_way              :1; // Enable allocation in one cache way only
		u32_t parity_on                     :1; // Support for parity checking
		u32_t sbz_1                         :20;
	} fields;
	u32_t all;
};

union gen_non_secure_access_control_register {
	struct {
		u32_t sbz_0    :10;
		u32_t cp10     :1; // Determines permission to access coprocessor 10 in the Non-secure state
		u32_t cp11     :1; // Determines permission to access coprocessor 11 in the Non-secure state
		u32_t nsd32dis :1; // Disable the Non-secure use of D16-D31 of the VFP register file
		u32_t nsasedis :1; // Disable Non-secure Advanced SIMD Extension functionality
		u32_t ple      :1; // Controls NS accesses to the Preload Engine resources
		u32_t tl       :1; // Determines if lockable TLB entries can be allocated in Non-secure state
		u32_t ns_smp   :1; // Determines if the SMP bit of the Auxiliary Control Register is writable in Non-secure state
		u32_t sbz_1    :15;
	} fields;
	u32_t all;
};

/**
 * @name gen_get_actlr
 * @brief Gets the auxiliary control register
 *
 * @details Provides the ability to get the auxiliary control register.
 *
 * @retval gen_auxiliary_control_register_t
 *
 * Example Usage:
 * @code
 *    sctlr = gen_get_actlr();
 * @endcode
 */
gen_auxiliary_control_register_t gen_get_actlr(void);

/**
 * @name gen_set_actlr
 * @brief Sets the auxiliary control register
 *
 * @details Provides the ability to set the auxiliary control register.
 *
 * @param gen_auxiliary_control_register_t reg
 *
 * Example Usage:
 * @code
 *    gen_set_actlr(actlr);
 * @endcode
 */
void gen_set_actlr(gen_auxiliary_control_register_t reg);

/**
 * @name gen_get_nsacr
 * @brief Gets the non-secure access control register
 *
 * @details Provides the ability to get the non-secure access control register.
 *
 * @retval gen_non_secure_access_control_register_t
 *
 * Example Usage:
 * @code
 *    nsacr = gen_get_nsacr();
 * @endcode
 */
gen_non_secure_access_control_register_t gen_get_nsacr(void);

/**
 * @name gen_set_actlr
 * @brief Sets the non-secure access control register
 *
 * @details Provides the ability to set the non-secure access control register.
 *
 * @param gen_non_secure_access_control_register_t reg
 *
 * Example Usage:
 * @code
 *    gen_set_nsacr(nsacr);
 * @endcode
 */
void gen_set_nsacr(gen_non_secure_access_control_register_t reg);

#endif //__C__

#ifdef __ASSEMBLY__

.extern gen_get_actlr
.extern gen_set_actlr

.extern gen_get_nsacr
.extern gen_set_nsacr

#endif //__ASSEMBLY__

#endif //__A9MOD_VMSA_GEN_H__
