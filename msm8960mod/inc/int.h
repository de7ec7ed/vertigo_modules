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

#ifndef __MSM8960MOD_INT_H__
#define __MSM8960MOD_INT_H__

// MSM ACPU Interrupt Numbers

// 0-15:  STI/SGI (software triggered/generated interrupts)
// 16-31: PPI (private peripheral interrupts)
// 32+:   SPI (shared peripheral interrupts)

#define INT_GIC_PPI_START 16
#define INT_GIC_SPI_START 32

#define INT_VGIC                                 (INT_GIC_PPI_START + 0)
#define INT_DEBUG_TIMER_EXP                      (INT_GIC_PPI_START + 1)
#define INT_GP_TIMER_EXP                         (INT_GIC_PPI_START + 2)
#define INT_GP_TIMER2_EXP                        (INT_GIC_PPI_START + 3)
#define INT_WDT0_ACCSCSSNBARK_INT                (INT_GIC_PPI_START + 4)
#define INT_WDT1_ACCSCSSNBARK_INT                (INT_GIC_PPI_START + 5)
#define INT_AVS_SVICINT                          (INT_GIC_PPI_START + 6)
#define INT_AVS_SVICINTSWDONE                    (INT_GIC_PPI_START + 7)
#define INT_CPU_DBGCPUXCOMMRXFULL                (INT_GIC_PPI_START + 8)
#define INT_CPU_DBGCPUXCOMMTXEMPTY               (INT_GIC_PPI_START + 9)
#define INT_ARMQC_PERFMON                        (INT_GIC_PPI_START + 10)
#define INT_SC_AVSCPUXDOWN                       (INT_GIC_PPI_START + 11)
#define INT_SC_AVSCPUXUP                         (INT_GIC_PPI_START + 12)
#define INT_SC_SICCPUXACGIRPTREQ                 (INT_GIC_PPI_START + 13)
#define INT_SC_SICCPUXEXTFAULTIRPTREQ            (INT_GIC_PPI_START + 14)
// PPI 15 is unused

#define INT_APCC_QGICACGIRPTREQ                  (INT_GIC_SPI_START + 0)
#define INT_APCC_QGICL2PERFMONIRPTREQ            (INT_GIC_SPI_START + 1)
#define INT_SC_SICL2PERFMONIRPTREQ               (INT_GIC_SPI_START + 1)
#define INT_APCC_QGICL2IRPTREQ                   (INT_GIC_SPI_START + 2)
#define INT_APCC_QGICMPUIRPTREQ                  (INT_GIC_SPI_START + 3)
#define INT_TLMM_MSM_DIR_CONN_IRQ_0              (INT_GIC_SPI_START + 4)
#define INT_TLMM_MSM_DIR_CONN_IRQ_1              (INT_GIC_SPI_START + 5)
#define INT_TLMM_MSM_DIR_CONN_IRQ_2              (INT_GIC_SPI_START + 6)
#define INT_TLMM_MSM_DIR_CONN_IRQ_3              (INT_GIC_SPI_START + 7)
#define INT_TLMM_MSM_DIR_CONN_IRQ_4              (INT_GIC_SPI_START + 8)
#define INT_TLMM_MSM_DIR_CONN_IRQ_5              (INT_GIC_SPI_START + 9)
#define INT_TLMM_MSM_DIR_CONN_IRQ_6              (INT_GIC_SPI_START + 10)
#define INT_TLMM_MSM_DIR_CONN_IRQ_7              (INT_GIC_SPI_START + 11)
#define INT_TLMM_MSM_DIR_CONN_IRQ_8              (INT_GIC_SPI_START + 12)
#define INT_TLMM_MSM_DIR_CONN_IRQ_9              (INT_GIC_SPI_START + 13)
#define INT_PM8921_SEC_IRQ_103                   (INT_GIC_SPI_START + 14)
#define INT_PM8018_SEC_IRQ_106                   (INT_GIC_SPI_START + 15)
#define INT_TLMM_MSM_SUMMARY_IRQ                 (INT_GIC_SPI_START + 16)
#define INT_SPDM_RT_1_IRQ                        (INT_GIC_SPI_START + 17)
#define INT_SPDM_DIAG_IRQ                        (INT_GIC_SPI_START + 18)
#define INT_RPM_APCC_CPU0_GP_HIGH_IRQ            (INT_GIC_SPI_START + 19)
#define INT_RPM_APCC_CPU0_GP_MEDIUM_IRQ          (INT_GIC_SPI_START + 20)
#define INT_RPM_APCC_CPU0_GP_LOW_IRQ             (INT_GIC_SPI_START + 21)
#define INT_RPM_APCC_CPU0_WAKE_UP_IRQ            (INT_GIC_SPI_START + 22)
#define INT_RPM_APCC_CPU1_GP_HIGH_IRQ            (INT_GIC_SPI_START + 23)
#define INT_RPM_APCC_CPU1_GP_MEDIUM_IRQ          (INT_GIC_SPI_START + 24)
#define INT_RPM_APCC_CPU1_GP_LOW_IRQ             (INT_GIC_SPI_START + 25)
#define INT_RPM_APCC_CPU1_WAKE_UP_IRQ            (INT_GIC_SPI_START + 26)
#define INT_SSBI2_2_SC_CPU0_SECURE_IRQ           (INT_GIC_SPI_START + 27)
#define INT_SSBI2_2_SC_CPU0_NON_SECURE_IRQ       (INT_GIC_SPI_START + 28)
#define INT_SSBI2_1_SC_CPU0_SECURE_IRQ           (INT_GIC_SPI_START + 29)
#define INT_SSBI2_1_SC_CPU0_NON_SECURE_IRQ       (INT_GIC_SPI_START + 30)
#define INT_MSMC_SC_SEC_CE_IRQ                   (INT_GIC_SPI_START + 31)
#define INT_MSMC_SC_PRI_CE_IRQ                   (INT_GIC_SPI_START + 32)
#define INT_SLIMBUS0_CORE_EE1_IRQ                (INT_GIC_SPI_START + 33)
#define INT_SLIMBUS0_BAM_EE1_IRQ                 (INT_GIC_SPI_START + 34)
#define INT_Q6FW_WDOG_EXPIRED_IRQ                (INT_GIC_SPI_START + 35)
#define INT_Q6SW_WDOG_EXPIRED_IRQ                (INT_GIC_SPI_START + 36)
#define INT_MSS_TO_APPS_IRQ_0                    (INT_GIC_SPI_START + 37)
#define INT_MSS_TO_APPS_IRQ_1                    (INT_GIC_SPI_START + 38)
#define INT_MSS_TO_APPS_IRQ_2                    (INT_GIC_SPI_START + 39)
#define INT_MSS_TO_APPS_IRQ_3                    (INT_GIC_SPI_START + 40)
#define INT_MSS_TO_APPS_IRQ_4                    (INT_GIC_SPI_START + 41)
#define INT_MSS_TO_APPS_IRQ_5                    (INT_GIC_SPI_START + 42)
#define INT_MSS_TO_APPS_IRQ_6                    (INT_GIC_SPI_START + 43)
#define INT_MSS_TO_APPS_IRQ_7                    (INT_GIC_SPI_START + 44)
#define INT_MSS_TO_APPS_IRQ_8                    (INT_GIC_SPI_START + 45)
#define INT_MSS_TO_APPS_IRQ_9                    (INT_GIC_SPI_START + 46)
#define INT_VPE_IRQ                              (INT_GIC_SPI_START + 47)
#define INT_VFE_IRQ                              (INT_GIC_SPI_START + 48)
#define INT_VCODEC_IRQ                           (INT_GIC_SPI_START + 49)
#define INT_TV_ENC_IRQ                           (INT_GIC_SPI_START + 50)
#define INT_SMMU_VPE_CB_SC_SECURE_IRQ            (INT_GIC_SPI_START + 51)
#define INT_SMMU_VPE_CB_SC_NON_SECURE_IRQ        (INT_GIC_SPI_START + 52)
#define INT_SMMU_VFE_CB_SC_SECURE_IRQ            (INT_GIC_SPI_START + 53)
#define INT_SMMU_VFE_CB_SC_NON_SECURE_IRQ        (INT_GIC_SPI_START + 54)
#define INT_SMMU_VCODEC_B_CB_SC_SECURE_IRQ       (INT_GIC_SPI_START + 55)
#define INT_SMMU_VCODEC_B_CB_SC_NON_SECURE_IRQ   (INT_GIC_SPI_START + 56)
#define INT_SMMU_VCODEC_A_CB_SC_SECURE_IRQ       (INT_GIC_SPI_START + 57)
#define INT_SMMU_VCODEC_A_CB_SC_NON_SECURE_IRQ   (INT_GIC_SPI_START + 58)
#define INT_SMMU_ROT_CB_SC_SECURE_IRQ            (INT_GIC_SPI_START + 59)
#define INT_SMMU_ROT_CB_SC_NON_SECURE_IRQ        (INT_GIC_SPI_START + 60)
#define INT_SMMU_MDP1_CB_SC_SECURE_IRQ           (INT_GIC_SPI_START + 61)
#define INT_SMMU_MDP1_CB_SC_NON_SECURE_IRQ       (INT_GIC_SPI_START + 62)
#define INT_SMMU_MDP0_CB_SC_SECURE_IRQ           (INT_GIC_SPI_START + 63)
#define INT_SMMU_MDP0_CB_SC_NON_SECURE_IRQ       (INT_GIC_SPI_START + 64)
#define INT_SMMU_JPEGD_CB_SC_SECURE_IRQ          (INT_GIC_SPI_START + 65)
#define INT_SMMU_JPEGD_CB_SC_NON_SECURE_IRQ      (INT_GIC_SPI_START + 66)
#define INT_SMMU_IJPEG_CB_SC_SECURE_IRQ          (INT_GIC_SPI_START + 67)
#define INT_SMMU_IJPEG_CB_SC_NON_SECURE_IRQ      (INT_GIC_SPI_START + 68)
#define INT_SMMU_GFX3D_CB_SC_SECURE_IRQ          (INT_GIC_SPI_START + 69)
#define INT_SMMU_GFX3D_CB_SC_NON_SECURE_IRQ      (INT_GIC_SPI_START + 70)
#define INT_SMMU_GFX2D0_CB_SC_SECURE_IRQ         (INT_GIC_SPI_START + 71)
#define INT_SMMU_GFX2D0_CB_SC_NON_SECURE_IRQ     (INT_GIC_SPI_START + 72)
#define INT_ROT_IRQ                              (INT_GIC_SPI_START + 73)
#define INT_MMSS_FABRIC_IRQ                      (INT_GIC_SPI_START + 74)
#define INT_MDP_IRQ                              (INT_GIC_SPI_START + 75)
#define INT_JPEGD_IRQ                            (INT_GIC_SPI_START + 76)
#define INT_JPEG_IRQ                             (INT_GIC_SPI_START + 77)
#define INT_MMSS_IMEM_IRQ                        (INT_GIC_SPI_START + 78)
#define INT_HDMI_IRQ                             (INT_GIC_SPI_START + 79)
#define INT_GFX3D_IRQ                            (INT_GIC_SPI_START + 80)
#define INT_GFX2D0_IRQ                           (INT_GIC_SPI_START + 81)
#define INT_DSI1_IRQ                             (INT_GIC_SPI_START + 82)
#define INT_CSI_1_IRQ                            (INT_GIC_SPI_START + 83)
#define INT_CSI_0_IRQ                            (INT_GIC_SPI_START + 84)
#define INT_LPASS_SCSS_AUDIO_IF_OUT0_IRQ         (INT_GIC_SPI_START + 85)
#define INT_LPASS_SCSS_MIDI_IRQ                  (INT_GIC_SPI_START + 86)
#define INT_LPASS_Q6SS_WDOG_EXPIRED              (INT_GIC_SPI_START + 87)
#define INT_LPASS_SCSS_GP_LOW_IRQ                (INT_GIC_SPI_START + 88)
#define INT_LPASS_SCSS_GP_MEDIUM_IRQ             (INT_GIC_SPI_START + 89)
#define INT_LPASS_SCSS_GP_HIGH_IRQ               (INT_GIC_SPI_START + 90)
#define INT_TOP_IMEM_IRQ                         (INT_GIC_SPI_START + 91)
#define INT_FABRIC_SYS_IRQ                       (INT_GIC_SPI_START + 92)
#define INT_FABRIC_APPS_IRQ                      (INT_GIC_SPI_START + 93)
#define INT_USB1_HS_BAM_IRQ                      (INT_GIC_SPI_START + 94)
#define INT_SDC4_BAM_IRQ                         (INT_GIC_SPI_START + 95)
#define INT_SDC3_BAM_IRQ                         (INT_GIC_SPI_START + 96)
#define INT_SDC2_BAM_IRQ                         (INT_GIC_SPI_START + 97)
#define INT_SDC1_BAM_IRQ                         (INT_GIC_SPI_START + 98)
#define INT_FABRIC_SPS_IRQ                       (INT_GIC_SPI_START + 99)
#define INT_USB1_HS_IRQ                          (INT_GIC_SPI_START + 100)
#define INT_SDC4_IRQ_0                           (INT_GIC_SPI_START + 101)
#define INT_SDC3_IRQ_0                           (INT_GIC_SPI_START + 102)
#define INT_SDC2_IRQ_0                           (INT_GIC_SPI_START + 103)
#define INT_SDC1_IRQ_0                           (INT_GIC_SPI_START + 104)
#define INT_SPS_BAM_DMA_IRQ                      (INT_GIC_SPI_START + 105)
#define INT_SPS_SEC_VIOL_IRQ                     (INT_GIC_SPI_START + 106)
#define INT_SPS_MTI_0                            (INT_GIC_SPI_START + 107)
#define INT_SPS_MTI_1                            (INT_GIC_SPI_START + 108)
#define INT_SPS_MTI_2                            (INT_GIC_SPI_START + 109)
#define INT_SPS_MTI_3                            (INT_GIC_SPI_START + 110)
#define INT_SPS_MTI_4                            (INT_GIC_SPI_START + 111)
#define INT_SPS_MTI_5                            (INT_GIC_SPI_START + 112)
#define INT_SPS_MTI_6                            (INT_GIC_SPI_START + 113)
#define INT_SPS_MTI_7                            (INT_GIC_SPI_START + 114)
#define INT_SPS_MTI_8                            (INT_GIC_SPI_START + 115)
#define INT_SPS_MTI_9                            (INT_GIC_SPI_START + 116)
#define INT_SPS_MTI_10                           (INT_GIC_SPI_START + 117)
#define INT_SPS_MTI_11                           (INT_GIC_SPI_START + 118)
#define INT_SPS_MTI_12                           (INT_GIC_SPI_START + 119)
#define INT_SPS_MTI_13                           (INT_GIC_SPI_START + 120)
#define INT_SPS_MTI_14                           (INT_GIC_SPI_START + 121)
#define INT_SPS_MTI_15                           (INT_GIC_SPI_START + 122)
#define INT_SPS_MTI_16                           (INT_GIC_SPI_START + 123)
#define INT_SPS_MTI_17                           (INT_GIC_SPI_START + 124)
#define INT_SPS_MTI_18                           (INT_GIC_SPI_START + 125)
#define INT_SPS_MTI_19                           (INT_GIC_SPI_START + 126)
#define INT_SPS_MTI_20                           (INT_GIC_SPI_START + 127)
#define INT_SPS_MTI_21                           (INT_GIC_SPI_START + 128)
#define INT_SPS_MTI_22                           (INT_GIC_SPI_START + 129)
#define INT_SPS_MTI_23                           (INT_GIC_SPI_START + 130)
#define INT_SPS_MTI_24                           (INT_GIC_SPI_START + 131)
#define INT_SPS_MTI_25                           (INT_GIC_SPI_START + 132)
#define INT_SPS_MTI_26                           (INT_GIC_SPI_START + 133)
#define INT_SPS_MTI_27                           (INT_GIC_SPI_START + 134)
#define INT_SPS_MTI_28                           (INT_GIC_SPI_START + 135)
#define INT_SPS_MTI_29                           (INT_GIC_SPI_START + 136)
#define INT_SPS_MTI_30                           (INT_GIC_SPI_START + 137)
#define INT_SPS_MTI_31                           (INT_GIC_SPI_START + 138)
#define INT_CSIPHY_4LN_IRQ                       (INT_GIC_SPI_START + 139)
#define INT_CSIPHY_2LN_IRQ               (INT_GIC_SPI_START + 140)
#define INT_USB2_IRQ                             (INT_GIC_SPI_START + 141)
#define INT_USB1_IRQ                             (INT_GIC_SPI_START + 142)
#define INT_TSSC_SSBI_IRQ                        (INT_GIC_SPI_START + 143)
#define INT_TSSC_SAMPLE_IRQ                      (INT_GIC_SPI_START + 144)
#define INT_TSSC_PENUP_IRQ                       (INT_GIC_SPI_START + 145)
#define INT_GSBI1_UARTDM_IRQ             (INT_GIC_SPI_START + 146)
#define INT_GSBI1_QUP_IRQ                (INT_GIC_SPI_START + 147)
#define INT_GSBI2_UARTDM_IRQ             (INT_GIC_SPI_START + 148)
#define INT_GSBI2_QUP_IRQ                (INT_GIC_SPI_START + 149)
#define INT_GSBI3_UARTDM_IRQ                     (INT_GIC_SPI_START + 150)
#define INT_GSBI3_QUP_IRQ                        (INT_GIC_SPI_START + 151)
#define INT_GSBI4_UARTDM_IRQ                     (INT_GIC_SPI_START + 152)
#define INT_GSBI4_QUP_IRQ                        (INT_GIC_SPI_START + 153)
#define INT_GSBI5_UARTDM_IRQ                     (INT_GIC_SPI_START + 154)
#define INT_GSBI5_QUP_IRQ                        (INT_GIC_SPI_START + 155)
#define INT_GSBI6_UARTDM_IRQ                     (INT_GIC_SPI_START + 156)
#define INT_GSBI6_QUP_IRQ                        (INT_GIC_SPI_START + 157)
#define INT_GSBI7_UARTDM_IRQ                     (INT_GIC_SPI_START + 158)
#define INT_GSBI7_QUP_IRQ                        (INT_GIC_SPI_START + 159)
#define INT_GSBI8_UARTDM_IRQ                     (INT_GIC_SPI_START + 160)
#define INT_GSBI8_QUP_IRQ                        (INT_GIC_SPI_START + 161)
#define INT_TSIF_TSPP_IRQ                        (INT_GIC_SPI_START + 162)
#define INT_TSIF_BAM_IRQ                         (INT_GIC_SPI_START + 163)
#define INT_TSIF2_IRQ                            (INT_GIC_SPI_START + 164)
#define INT_TSIF1_IRQ                            (INT_GIC_SPI_START + 165)
#define INT_DSI2_IRQ                             (INT_GIC_SPI_START + 166)
#define INT_ISPIF_IRQ                            (INT_GIC_SPI_START + 167)
#define INT_MSMC_SC_SEC_TMR_IRQ                  (INT_GIC_SPI_START + 168)
#define INT_MSMC_SC_SEC_WDOG_BARK_IRQ            (INT_GIC_SPI_START + 169)
#define INT_ADM_0_SCSS_0_IRQ                     (INT_GIC_SPI_START + 170)
#define INT_ADM_0_SCSS_1_IRQ                     (INT_GIC_SPI_START + 171)
#define INT_ADM_0_SCSS_2_IRQ                     (INT_GIC_SPI_START + 172)
#define INT_ADM_0_SCSS_3_IRQ                     (INT_GIC_SPI_START + 173)
#define INT_CC_SCSS_WDT1CPU1BITEEXPIRED          (INT_GIC_SPI_START + 174)
#define INT_CC_SCSS_WDT1CPU0BITEEXPIRED          (INT_GIC_SPI_START + 175)
#define INT_CC_SCSS_WDT0CPU1BITEEXPIRED          (INT_GIC_SPI_START + 176)
#define INT_CC_SCSS_WDT0CPU0BITEEXPIRED          (INT_GIC_SPI_START + 177)
#define INT_TSENS_UPPER_LOWER_INT                (INT_GIC_SPI_START + 178)
#define INT_SSBI2_2_SC_CPU1_SECURE_INT           (INT_GIC_SPI_START + 179)
#define INT_SSBI2_2_SC_CPU1_NON_SECURE_INT       (INT_GIC_SPI_START + 180)
#define INT_SSBI2_1_SC_CPU1_SECURE_INT           (INT_GIC_SPI_START + 181)
#define INT_SSBI2_1_SC_CPU1_NON_SECURE_INT       (INT_GIC_SPI_START + 182)
#define INT_XPU_SUMMARY_IRQ                      (INT_GIC_SPI_START + 183)
#define INT_BUS_EXCEPTION_SUMMARY_IRQ            (INT_GIC_SPI_START + 184)
#define INT_HSDDRX_EBI1CH0_IRQ                   (INT_GIC_SPI_START + 185)
#define INT_HSDDRX_EBI1CH1_IRQ                   (INT_GIC_SPI_START + 186)
#define INT_SDC5_BAM_IRQ                         (INT_GIC_SPI_START + 187)
#define INT_SDC5_IRQ_0                           (INT_GIC_SPI_START + 188)
#define INT_GSBI9_UARTDM_IRQ                     (INT_GIC_SPI_START + 189)
#define INT_GSBI9_QUP_IRQ                        (INT_GIC_SPI_START + 190)
#define INT_GSBI10_UARTDM_IRQ                    (INT_GIC_SPI_START + 191)
#define INT_GSBI10_QUP_IRQ                       (INT_GIC_SPI_START + 192)
#define INT_GSBI11_UARTDM_IRQ                    (INT_GIC_SPI_START + 193)
#define INT_GSBI11_QUP_IRQ                       (INT_GIC_SPI_START + 194)
#define INT_GSBI12_UARTDM_IRQ                    (INT_GIC_SPI_START + 195)
#define INT_GSBI12_QUP_IRQ                       (INT_GIC_SPI_START + 196)
#define INT_RIVA_APSS_LTECOEX_IRQ                (INT_GIC_SPI_START + 197)
#define INT_RIVA_APSS_SPARE_IRQ                  (INT_GIC_SPI_START + 198)
#define INT_RIVA_APSS_WDOG_BITE_RESET_RDY_IRQ    (INT_GIC_SPI_START + 199)
#define INT_RIVA_APSS_RESET_DONE_IRQ             (INT_GIC_SPI_START + 200)
#define INT_RIVA_APSS_ASIC_IRQ                   (INT_GIC_SPI_START + 201)
#define INT_RIVA_APPS_WLAN_RX_DATA_AVAIL_IRQ     (INT_GIC_SPI_START + 202)
#define INT_RIVA_APPS_WLAN_DATA_XFER_DONE_IRQ    (INT_GIC_SPI_START + 203)
#define INT_RIVA_APPS_WLAN_SMSM_IRQ              (INT_GIC_SPI_START + 204)
#define INT_RIVA_APPS_LOG_CTRL_IRQ               (INT_GIC_SPI_START + 205)
#define INT_RIVA_APPS_FM_CTRL_IRQ                (INT_GIC_SPI_START + 206)
#define INT_RIVA_APPS_HCI_IRQ                    (INT_GIC_SPI_START + 207)
#define INT_RIVA_APPS_WLAN_CTRL_IRQ              (INT_GIC_SPI_START + 208)
#define INT_A2_BAM_IRQ                           (INT_GIC_SPI_START + 209)
#define INT_SMMU_GFX2D1_CB_SC_SECURE_IRQ         (INT_GIC_SPI_START + 210)
#define INT_SMMU_GFX2D1_CB_SC_NON_SECURE_IRQ     (INT_GIC_SPI_START + 211)
#define INT_GFX2D1_IRQ                           (INT_GIC_SPI_START + 212)
#define INT_PPSS_WDOG_TIMER_IRQ                  (INT_GIC_SPI_START + 213)
#define INT_SPS_SLIMBUS_CORE_EE0_IRQ             (INT_GIC_SPI_START + 214)
#define INT_SPS_SLIMBUS_BAM_EE0_IRQ              (INT_GIC_SPI_START + 215)
#define INT_QDSS_ETB_IRQ                         (INT_GIC_SPI_START + 216)
#define INT_QDSS_CTI2KPSS_CPU1_IRQ               (INT_GIC_SPI_START + 217)
#define INT_QDSS_CTI2KPSS_CPU0_IRQ               (INT_GIC_SPI_START + 218)
#define INT_TLMM_MSM_DIR_CONN_IRQ_16             (INT_GIC_SPI_START + 219)
#define INT_TLMM_MSM_DIR_CONN_IRQ_17             (INT_GIC_SPI_START + 220)
#define INT_TLMM_MSM_DIR_CONN_IRQ_18             (INT_GIC_SPI_START + 221)
#define INT_TLMM_MSM_DIR_CONN_IRQ_19             (INT_GIC_SPI_START + 222)
#define INT_TLMM_MSM_DIR_CONN_IRQ_20             (INT_GIC_SPI_START + 223)
#define INT_TLMM_MSM_DIR_CONN_IRQ_21             (INT_GIC_SPI_START + 224)
#define INT_PM8921_SEC_IRQ_104                   (INT_GIC_SPI_START + 225)
#define INT_PM8018_SEC_IRQ_107                   (INT_GIC_SPI_START + 226)
#define INT_USB_HSIC_IRQ                         (INT_GIC_SPI_START + 229)

// smd/smsm interrupts
#define INT_A9_M2A_0                             MSS_TO_APPS_IRQ_0
#define INT_A9_M2A_5                             MSS_TO_APPS_IRQ_1
#define INT_ADSP_A11                             LPASS_SCSS_GP_HIGH_IRQ
#define INT_ADSP_A11_SMSM                        LPASS_SCSS_GP_MEDIUM_IRQ
#define INT_DSPS_A11                             SPS_MTI_31
#define INT_DSPS_A11_SMSM                        SPS_MTI_30
#define INT_WCNSS_A11                            RIVA_APSS_SPARE_IRQ
#define INT_WCNSS_A11_SMSM                       RIVA_APPS_WLAN_SMSM_IRQ

#endif //__MSM8960MOD_INT_H__
