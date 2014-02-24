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

#ifndef __S5L8930MOD_INT_H__
#define __S5L8930MOD_INT_H__

#define INT_CPU_0_0               0x0
#define INT_IOP                   0x3
#define INT_WDT                   0x4
#define INT_SWI                   0x7
#define INT_ISP0                  0x8
#define INT_ISP1                  0x9
#define INT_SCALER                0xB
#define INT_USB_DEVICE            0xD
#define INT_USB_EHCI              0xE
#define INT_USB_OHCI_0            0xF
#define INT_USB_OHCI_1            0x10
#define INT_PWM                   0x11
#define INT_PKE                   0x12
#define INT_I2C0                  0x13
#define INT_I2C2                  0x15
#define INT_UART_0                0x16
#define INT_UART_1                0x17
#define INT_UART_2                0x18
#define INT_UART_3                0x19
#define INT_UART_4                0x1A
#define INT_UART_5                0x1B
#define INT_UART_6                0x1C
#define INT_SPI_0                 0x1D
#define INT_SPI_1                 0x1E
#define INT_FLASH_CONTROLLER_0_0  0x22
#define INT_FLASH_CONTROLLER_0_1  0x23
#define INT_CEATA                 0x24
#define INT_SHA1                  0x25
#define INT_SDIO                  0x26
#define INT_TV_OUT                0x27
#define INT_MIPI_DSIM             0x28
#define INT_CLCD_0                0x29
#define INT_CLCD_1                0x2A
#define INT_RGBOUT_0              0x2B
#define INT_RGBOUT_1              0x2C
#define INT_DISPLAYPORT           0x2D
#define INT_VENC                  0x2E
#define INT_SGX                   0x2F
#define INT_VXD                   0x30
//#define INT_CDMA_X 0x31 - 0x55
//#define INT_AMC_X 0x56 - 0x6C
#define INT_DART_1                0x6D
#define INT_DART_2                0x6E
#define INT_CPU_0_1               0x6F
#define INT_JPEG                  0x73
#define INT_GPIO                  0x74
#define INT_ARM_IO                0x77

// PMU
#define INT_DOCK                  0x5
#define INT_I2C_0_MIKEY           0x17

// GPIO
#define INT_GPIO_BUTTONS_0        0x1
#define INT_GPIO_BUTTONS_1        0x2
#define INT_GPIO_BUTTONS_2        0x3
#define INT_BASEBAND_0            0x4
#define INT_BUTTONS_3             0x5
#define INT_BUTTONS_4             0x7
#define INT_BASEBAND_1            0xB
#define INT_SPI_2                 0xC
#define INT_PMU                   0xD
#define INT_SPI_1_MULTI_TOUCH     0x15
#define INT_I2C_0_COMPASS_2       0x18
#define INT_UART_4_GPS_0          0x20
#define INT_I2C_2_GYRO            0x21
#define INT_I2C_0_COMPASS_1       0x23
#define INT_I2C_2_ACCELEROMETER_0 0x24
#define INT_I2C0_ALS              0x25
#define INT_I2C_2_ACCELEROMETER_1 0x26
#define INT_UART_4_GPS_1          0xA0
#define INT_I2C_0_HIGHLAND_PARK   0xA2

#endif //__S5L8930MOD_INT_H__
