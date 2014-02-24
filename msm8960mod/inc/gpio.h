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

#ifndef __MSM8960MOD_GPIO_H__
#define __MSM8960MOD_GPIO_H__

#define GPIO_MDP_VSYNC                      0
#define GPIO_MHL_RST                        1
#define GPIO_MSM_FLASH_CNTL_EN              2
#define GPIO_CAM_MCLK2                      2 /* > Rev10 */
#define GPIO_MSM_FLASH_NOW                  3
#define GPIO_VFE_CAMIF_TIMER3_INT           4
#define GPIO_CAM_MCLK0                      5
#define GPIO_CAM_CORE_EN                    6
#define GPIO_CAM_MIPI_EN                    7
#define GPIO_CODEC_I2C_SDA                  8
#define GPIO_CODEC_I2C_SCL                  9
#define GPIO_LCD_22V_EN                    10
#define GPIO_MXT_TS_IRQ                    11
#define GPIO_FPGA_CS                       14
#define GPIO_MHL_WAKE_UP                   15
#define GPIO_MAIN_MIC_BIAS                 18
#define GPIO_MHL_EN                        19
#define GPIO_FUELGAUGE_I2C_SDA             24
#define GPIO_FUELGAUGE_I2C_SCL             25
#define GPIO_BT_UART_TXD                   26
#define GPIO_BT_UART_RXD                   27
#define GPIO_BT_UART_CTS                   28
#define GPIO_BT_UART_RTS                   29
#define GPIO_NFC_SDA                       32
#define GPIO_NFC_SCL                       33
#define GPIO_ALS_INT                       -1/* 42 */
#define GPIO_SENSOR_SNS_SDA                44
#define GPIO_SENSOR_SNS_SCL                45
#define GPIO_CAM_A_EN                      46
#define GPIO_HAPTIC_PWR_EN                 47 /* < BOARD_REV08 */
#define GPIO_HOME_KEY                      49 /* >= BOARD_REV08 */
#define GPIO_MXT_TS_LDO_EN                 50
#define GPIO_CAM_SENSOR_EN                 51
#define GPIO_INOK_INT                      52
#define GPIO_SENSOR_ALS_SDA                63
#define GPIO_SENSOR_ALS_SCL                64
#define GPIO_FUEL_INT                      67
#define GPIO_MSENSE_RST                    68
#define GPIO_MPU3050_INT                   69
#define GPIO_VIB_PWM                       70
#define GPIO_USB_I2C_SDA                   73
#define GPIO_USB_I2C_SCL                   74
#define GPIO_CAM2_RST_N                    76
#define GPIO_VIB_ON                        77 /* < BOARD_REV04 */
#define GPIO_KS8851_RST                    89
#define GPIO_KS8851_IRQ                    90
#define GPIO_NFC_FIRMWARE                  92
#define GPIO_MHL_SCL                       96
#define GPIO_MHL_SDA                       95
#define GPIO_MHL_INT                       99
#define GPIO_NFC_IRQ                       106
#define GPIO_ISP_RESET                     107

/* ES305B GPIO */
#define GPIO_MSM_AUD_A2220_WAKEUP          79
#define GPIO_MSM_AUD_A2220_RESET           75

/* PMIC8921 MPP */
#define GPIO_PMIC_MPP_FLASH_LED_UNLOCK     4

/* PMIC8921 GPIO */
#define GPIO_PMIC_VIB_ON                   4
#define GPIO_PMIC_MSM_FLASH_CNTL_EN        5
#define GPIO_PMIC_RGB_INT                  6
#define GPIO_PMIC_ECOMPASS_RST             9
#define GPIO_PMIC_SPK_EN                   18
#define GPIO_PMIC_VPS_EN                   19
#define GPIO_PMIC_NFC_EN                   21
#define GPIO_PMIC_OTG_EN                   -1
#define GPIO_PMIC_HAPTIC_PWR_EN            22
#define GPIO_PMIC_CODEC_RST                38
#define GPIO_PMIC_OTG_POWER                42
#define GPIO_PMIC_LCD_RST                  43
#define GPIO_PMIC_CMC_ESD_DET              15
#define GPIO_PMIC_VGH_ESD_DET              44
#define GPIO_PMIC_BATT_INT                 37

#endif //__MSM8960MOD_GPIO_H__
