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

#ifndef __MSM8960MOD_MAP_H__
#define __MSM8960MOD_MAP_H__

#include <defines.h>

#define MAP_TMR_ADDRESS 0x0200A000
#define MAP_TMR_SIZE    0x1000

#define MSM8960_TMR0_ADDRESS 0x0208A000
#define MSM8960_TMR0_SIZE    0x1000

#define MSM8960_RPM_ADDRESS 0x00108000
#define MSM8960_RPM_SIZE    0x1000

#define MSM8960_RPM_MPM_ADDRESS 0x00200000
#define MSM8960_RPM_MPM_SIZE    0x1000

#define MSM8960_TCSR_ADDRESS 0x1A400000
#define MSM8960_TCSR_SIZE    0x1000

#define MSM8960_APCS_GCC_ADDRESS 0x02011000
#define MSM8960_APCS_GCC_SIZE    0x1000

#define MSM8960_SAW_L2_ADDRESS 0x02012000
#define MSM8960_SAW_L2_SIZE    0x1000

#define MSM8960_SAW0_ADDRESS 0x02089000
#define MSM8960_SAW0_SIZE    0x1000

#define MSM8960_SAW1_ADDRESS 0x02099000
#define MSM8960_SAW1_SIZE    0x1000

#define MSM8960_IMEM_ADDRESS 0x2A03F000
#define MSM8960_IMEM_SIZE    0x1000

#define MSM8960_ACC0_ADDRESS 0x02088000
#define MSM8960_ACC0_SIZE    0x1000

#define MSM8960_ACC1_ADDRESS 0x02098000
#define MSM8960_ACC1_SIZE    0x1000

#define MSM8960_QGIC_DIST_ADDRESS 0x02000000
#define MSM8960_QGIC_DIST_SIZE    0x1000

#define MSM8960_QGIC_CPU_ADDRESS 0x02002000
#define MSM8960_QGIC_CPU_SIZE    0x1000

#define MSM8960_CLK_CTL_ADDRESS 0x00900000
#define MSM8960_CLK_CTL_SIZE    0x4000

#define MSM8960_MMSS_CLK_CTL_ADDRESS 0x04000000
#define MSM8960_MMSS_CLK_CTL_SIZE    0x1000

#define MSM8960_LPASS_CLK_CTL_ADDRESS 0x28000000
#define MSM8960_LPASS_CLK_CTL_SIZE    0x1000

#define MSM8960_HFPLL_ADDRESS 0x00903000
#define MSM8960_HFPLL_SIZE    0x1000

#define MSM8960_TLMM_ADDRESS 0x00800000
#define MSM8960_TLMM_SIZE    0x4000

#define MSM8960_SIC_NON_SECURE_ADDRESS 0x12100000
#define MSM8960_SIC_NON_SECURE_SIZE    0x10000

#define MSM8960_HDMI_ADDRESS 0x04A00000
#define MSM8960_HDMI_SIZE    0x1000

#define MSM8960_QFPROM_ADDRESS 0x00700000
#define MSM8960_QFPROM_SIZE    0x1000

#define MAP_UARTDM_0_ADDRESS 0x16440000
#define MAP_UARTDM_0_SIZE    0x1000

#define MAP_UARTDM_1_ADDRESS 0x16540000
#define MAP_UARTDM_1_SIZE    0x1000


#endif //__MSM8960MOD_MAP_H__
