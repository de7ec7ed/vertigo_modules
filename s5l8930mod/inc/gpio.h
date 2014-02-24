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

#ifndef __S5L8930MOD_GPIO_H__
#define __S5L8930MOD_GPIO_H__

#define GPIO_BUTTONS_BUTTON_MENU     0x0
#define GPIO_BASEBAND_PMU_EXTON      0x1
#define GPIO_BASEBAND_BB_ON          0x2
#define GPIO_BASEBAND_BB_USB_MUX     0x3
#define GPIO_BUTTONS_BUTTON_RINGERAB 0x4
#define GPIO_GAS_GAUGE_BATTERY_SWI   0x5
#define GPIO_SDIO_DEVICE_RESET       0x6
#define GPIO_BLUETOOTH_BT_WAKE       0x7
#define GPIO_BLUETOOTH_BT_RESET      0x100
#define GPIO_BASEBAND_RADIO_ON       0x101
#define GPIO_BASEBAND_BB_RST         0x102
#define GPIO_BASEBAND_RESET_DET      0x103
#define GPIO_SPI2_SRDY               0x104
#define GPIO_AUDIO0_RESET            0x106
#define GPIO_HIGHLAND_PARK_RESET     0x200
#define GPIO_PMU_KEEPACT             0x203
#define GPIO_MULTI_TOUCH_RESET       0x204
#define GPIO_LCD_RESET               0x206
#define GPIO_COMPASS_RESET           0x300
#define GPIO_GPS_GPS_RESET           0x300
#define GPIO_GPS_GPS_STANDBY         0x306
#define GPIO_ISP_SENSOR_SHUTDOWN2    0x402
#define GPIO_ALS_INT_STATUS          0x405
#define GPIO_SPI0_SPI_CS0            0x505
#define GPIO_MULTI_TOUCH_ENABLE_CS   0x601
#define GPIO_SPI2_SCLK               0x602
#define GPIO_SPI2_MOSI               0x604
#define GPIO_SPI_MRDY                0x605
#define GPIO_BASEBAND_UART1_TX       0x606
#define GPIO_UART1_RTS               0x700
#define GPIO_BASEBAND_UART2_TX       0x702
#define GPIO_UART3_TX                0x706
#define GPIO_UART3_RTS               0x800
#define GPIO_UART4_TX                0x802
#define GPIO_UART4_RTS               0x804
#define GPIO_UART5_TX                0x806
#define GPIO_UART6_TX                0x807
#define GPIO_I2C0_IIC_SDA            0x903
#define GPIO_I2C0_IIC_SCL            0x904
#define GPIO_I2C2_IIC_SDA            0x907
#define GPIO_I2C2_IIC_SCL            0xA00
#define GPIO_ISP_STROBE_ENABLE       0xF00
#define GPIO_ISP_SENSOR_SHUTDOWN     0xF02
#define GPIO_IPS_SENSOR_EXTCLK       0xF03
#define GPIO_TV_OUT_AMP_ENABLE       0x1104
#define GPIO_UART0_TX                0x1107
#define GPIO_AUDIO0_SPKR_MUTE        0x1401
#define GPIO_ARM_IO_DDR_ITS0         0x1501
#define GPIO_ARM_IO_DDR_ITS1         0x1502

#endif //__S5L8930MOD_GPIO_H__
