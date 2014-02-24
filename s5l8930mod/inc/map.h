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

#ifndef __S5L8930MOD_MAP_H__
#define __S5L8930MOD_MAP_H__

#define MAP_VIC_ADDRESS 0xBF200000
#define MAP_VIC_SIZE    0x40000

#define MAP_GPIO_ADDRESS 0xBFA00000
#define MAP_GPIO_SIZE    0x1000

#define MAP_PMGR_0_ADDRESS 0xBF100000
#define MAP_PMGR_0_SIZE    0x6000

#define MAP_PMGR_1_ADDRESS 0x85E00000
#define MAP_PMGR_1_SIZE    0x1000

#define MAP_PMGR_2_ADDRESS 0x88E00000
#define MAP_PMGR_2_SIZE    0x1000

#define MAP_PMGR_3_ADDRESS 0x88F00000
#define MAP_PMGR_3_SIZE    0x1000

#define MAP_PMGR_4_ADDRESS 0x89E00000
#define MAP_PMGR_4_SIZE    0x1000

#define MAP_PMGR_5_ADDRESS 0x89F00000
#define MAP_PMGR_5_SIZE    0x1000

#define MAP_WDT_ADDRESS 0xBF102020
#define MAP_WDT_SIZE    0x10

#define MAP_UART_0_ADDRESS 0x82500000
#define MAP_UART_0_SIZE    0x1000

#define MAP_UART_1_ADDRESS 0x82600000
#define MAP_UART_1_SIZE    0x1000

#define MAP_UART_2_ADDRESS 0x82700000
#define MAP_UART_2_SIZE    0x1000

#define MAP_UART_3_ADDRESS 0x82800000
#define MAP_UART_3_SIZE    0x1000

#define MAP_UART_4_ADDRESS 0x82900000
#define MAP_UART_4_SIZE    0x1000

#define MAP_UART_5_ADDRESS 0x82A00000
#define MAP_UART_5_SIZE    0x1000

#define MAP_UART_6_ADDRESS 0x82B00000
#define MAP_UART_6_SIZE    0x1000

#define MAP_DART_1_ADDRESS 0x88D00000
#define MAP_DART_1_SIZE    0x2000

#define MAP_DART_2_ADDRESS 0x89D00000
#define MAP_DART_2_SIZE    0x2000

#define MAP_SDIO_ADDRESS 0x80000000
#define MAP_SDIO_SIZE    0x1000

#define MAP_SHA1_ADDRESS 0x80100000
#define MAP_SHA1_SIZE    0x1000

#define MAP_CEATA_ADDRESS 0x81000000
#define MAP_CEATA_SIZE    0x1000

#define MAP_SPI_0_ADDRESS 0x82000000
#define MAP_SPI_0_SIZE    0x1000

#define MAP_SPI_1_ADDRESS 0x82100000
#define MAP_SPI_1_SIZE    0x1000

#define MAP_SPI_2_ADDRESS 0x82200000
#define MAP_SPI_2_SIZE    0x1000

#define MAP_PKE_ADDRESS 0x83100000
#define MAP_PKE_SIZE    0x1000

#define MAP_I2C_0_ADDRESS 0x83200000
#define MAP_12C_0_SIZE    0x1000

#define MAP_I2C_2_ADDRESS 0x83400000
#define MAP_I2C_2_SIZE    0x1000

#define MAP_I2S_0_ADDRESS 0x84500400
#define MAP_I2S_0_SIZE    0xC00

#define MAP_I2S_1_ADDRESS 0x84501400
#define MAP_I2S_1_SIZE    0xC00

#define MAP_I2S_2_ADDRESS 0x84502400
#define MAP_I2S_2_SIZE    0xC00

#define MAP_PWM_ADDRESS 0x83500000
#define MAP_PWM_SIZE    0x1000

#define MAP_OTGPHYCTRL_ADDRESS 0x86000000
#define MAP_OTGPHYCTRL_SIZE    0x1000

#define MAP_USB_COMPLEX_ADDRESS 0xBF108000
#define MAP_USB_COMPLEX_SIZE    0x1000

#define MAP_USB_DEVICE_ADDRESS 0x86100000
#define MAP_USB_DEVICE_SIZE    0x10000

#define MAP_USB_EHCI_ADDRESS 0x86400000
#define MAP_USB_EHCI_SIZE    0x10000

#define MAP_USB_OHCI_0_ADDRESS 0x86500000
#define MAP_USB_OHCI_0_SIZE 0x10000

#define MAP_USB_OHCI_1_ADDRESS 0x86600000
#define MAP_USB_OHCI_1_SIZE 0x10000

#define MAP_VXD_ADDRESS 0x85000000
#define MAP_VXD_SIZE    0x100000

#define MAP_SGX_ADDRESS 0x85100000
#define MAP_SGX_SIZE    0x1000

#define MAP_VENC_ADDRESS 0x88000000
#define MAP_VENC_SIZE    0x1000

#define MAP_JPEG_ADDRESS 0x88200000
#define MAP_JPEG_SIZE    0x1000

#define MAP_ISP_ADDRESS 0x88100000
#define MAP_ISP_SIZE    0x1000

#define MAP_SCALER_ADDRESS 0x89300000
#define MAP_SCALER_SIZE    0x1000

#define MAP_CLCD_ADDRESS 0x89200000
#define MAP_CLCD_SIZE    0x2000

#define MAP_MIPI_DSIM_ADDRESS 0x89500000
#define MAP_MIPI_DSIM_SIZE    0x1000

#define MAP_SWI_ADDRESS 0xBF600000
#define MAP_SWI_SIZE    0x1000

#define MAP_RGBOUT_ADDRESS 0x89600000
#define MAP_RGBOUT_SIZE    0x1000

#define MAP_TV_OUT_ADDRESS 0x89400000
#define MAP_TV_OUT_SIZE    0x1000

#define MAP_AMC_ADDRESS 0x84300000
#define MAP_AMC_SIZE    0x5000

#define MAP_DISPLAYPORT_ADDRESS 0x84900000
#define MAP_DISPLAYPORT_SIZE    0x2000

#endif //__S5L8930MOD_MAP_H__
