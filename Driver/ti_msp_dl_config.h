/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the LP_MSPM0G3507
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_LP_MSPM0G3507
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG7
#define PWM_0_INST_IRQHandler                                   TIMG7_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG7_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              8000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_15
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM32)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM32_PF_TIMG7_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX

/* Defines for PWM_1 */
#define PWM_1_INST                                                         TIMG6
#define PWM_1_INST_IRQHandler                                   TIMG6_IRQHandler
#define PWM_1_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define PWM_1_INST_CLK_FREQ                                              8000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_1_C0_PORT                                                 GPIOB
#define GPIO_PWM_1_C0_PIN                                          DL_GPIO_PIN_6
#define GPIO_PWM_1_C0_IOMUX                                      (IOMUX_PINCM23)
#define GPIO_PWM_1_C0_IOMUX_FUNC                     IOMUX_PINCM23_PF_TIMG6_CCP0
#define GPIO_PWM_1_C0_IDX                                    DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (63999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           32000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_0_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC1
#define ADC12_0_INST_IRQHandler                                  ADC1_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC1_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define GPIO_ADC12_0_C4_PORT                                               GPIOB
#define GPIO_ADC12_0_C4_PIN                                       DL_GPIO_PIN_17
#define GPIO_ADC12_0_IOMUX_C4                                    (IOMUX_PINCM43)
#define GPIO_ADC12_0_IOMUX_C4_FUNC                (IOMUX_PINCM43_PF_UNCONNECTED)



/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for RED: GPIOB.14 with pinCMx 31 on package pin 2 */
#define LED_RED_PIN                                             (DL_GPIO_PIN_14)
#define LED_RED_IOMUX                                            (IOMUX_PINCM31)
/* Defines for SCL_D0: GPIOA.8 with pinCMx 19 on package pin 54 */
#define OLED_SCL_D0_PORT                                                 (GPIOA)
#define OLED_SCL_D0_PIN                                          (DL_GPIO_PIN_8)
#define OLED_SCL_D0_IOMUX                                        (IOMUX_PINCM19)
/* Defines for SDA_D1: GPIOB.24 with pinCMx 52 on package pin 23 */
#define OLED_SDA_D1_PORT                                                 (GPIOB)
#define OLED_SDA_D1_PIN                                         (DL_GPIO_PIN_24)
#define OLED_SDA_D1_IOMUX                                        (IOMUX_PINCM52)
/* Defines for RES: GPIOB.9 with pinCMx 26 on package pin 61 */
#define OLED_RES_PORT                                                    (GPIOB)
#define OLED_RES_PIN                                             (DL_GPIO_PIN_9)
#define OLED_RES_IOMUX                                           (IOMUX_PINCM26)
/* Defines for DC: GPIOA.27 with pinCMx 60 on package pin 31 */
#define OLED_DC_PORT                                                     (GPIOA)
#define OLED_DC_PIN                                             (DL_GPIO_PIN_27)
#define OLED_DC_IOMUX                                            (IOMUX_PINCM60)
/* Defines for PIN_1: GPIOB.8 with pinCMx 25 on package pin 60 */
#define Gray_Address_PIN_1_PORT                                          (GPIOB)
#define Gray_Address_PIN_1_PIN                                   (DL_GPIO_PIN_8)
#define Gray_Address_PIN_1_IOMUX                                 (IOMUX_PINCM25)
/* Defines for PIN_2: GPIOA.31 with pinCMx 6 on package pin 39 */
#define Gray_Address_PIN_2_PORT                                          (GPIOA)
#define Gray_Address_PIN_2_PIN                                  (DL_GPIO_PIN_31)
#define Gray_Address_PIN_2_IOMUX                                  (IOMUX_PINCM6)
/* Defines for PIN_3: GPIOA.28 with pinCMx 3 on package pin 35 */
#define Gray_Address_PIN_3_PORT                                          (GPIOA)
#define Gray_Address_PIN_3_PIN                                  (DL_GPIO_PIN_28)
#define Gray_Address_PIN_3_IOMUX                                  (IOMUX_PINCM3)
/* Defines for AIN_1: GPIOB.5 with pinCMx 18 on package pin 53 */
#define TB6612_AIN_1_PORT                                                (GPIOB)
#define TB6612_AIN_1_PIN                                         (DL_GPIO_PIN_5)
#define TB6612_AIN_1_IOMUX                                       (IOMUX_PINCM18)
/* Defines for AIN_2: GPIOB.11 with pinCMx 28 on package pin 63 */
#define TB6612_AIN_2_PORT                                                (GPIOB)
#define TB6612_AIN_2_PIN                                        (DL_GPIO_PIN_11)
#define TB6612_AIN_2_IOMUX                                       (IOMUX_PINCM28)
/* Defines for BIN_1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define TB6612_BIN_1_PORT                                                (GPIOA)
#define TB6612_BIN_1_PIN                                        (DL_GPIO_PIN_12)
#define TB6612_BIN_1_IOMUX                                       (IOMUX_PINCM34)
/* Defines for BIN_2: GPIOA.13 with pinCMx 35 on package pin 6 */
#define TB6612_BIN_2_PORT                                                (GPIOA)
#define TB6612_BIN_2_PIN                                        (DL_GPIO_PIN_13)
#define TB6612_BIN_2_IOMUX                                       (IOMUX_PINCM35)
/* Defines for PIN1: GPIOB.13 with pinCMx 30 on package pin 1 */
#define EnconderA_PIN1_PORT                                              (GPIOB)
// groups represented: ["EnconderB","EnconderA"]
// pins affected: ["PIN3","PIN1"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define EnconderA_PIN1_IIDX                                 (DL_GPIO_IIDX_DIO13)
#define EnconderA_PIN1_PIN                                      (DL_GPIO_PIN_13)
#define EnconderA_PIN1_IOMUX                                     (IOMUX_PINCM30)
/* Defines for PIN2: GPIOA.14 with pinCMx 36 on package pin 7 */
#define EnconderA_PIN2_PORT                                              (GPIOA)
#define EnconderA_PIN2_PIN                                      (DL_GPIO_PIN_14)
#define EnconderA_PIN2_IOMUX                                     (IOMUX_PINCM36)
/* Defines for PIN3: GPIOB.16 with pinCMx 33 on package pin 4 */
#define EnconderB_PIN3_PORT                                              (GPIOB)
#define EnconderB_PIN3_IIDX                                 (DL_GPIO_IIDX_DIO16)
#define EnconderB_PIN3_PIN                                      (DL_GPIO_PIN_16)
#define EnconderB_PIN3_IOMUX                                     (IOMUX_PINCM33)
/* Defines for PIN4: GPIOA.15 with pinCMx 37 on package pin 8 */
#define EnconderB_PIN4_PORT                                              (GPIOA)
#define EnconderB_PIN4_PIN                                      (DL_GPIO_PIN_15)
#define EnconderB_PIN4_IOMUX                                     (IOMUX_PINCM37)




/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_PWM_1_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_ADC12_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
