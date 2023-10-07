/**
 * @file stm32f407xx_rcc_driver.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and functions prototypes for the STM32F407xx SPI driver.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef INC_STM32F407XX_RCC_DRIVER_H_
#define INC_STM32F407XX_RCC_DRIVER_H_

#include "stm32f407xx.h"

#define RCC_PLLCFGR_PLLSRC_HSE  ((uint32_t)0x00400000)
#define HSI_VALUE 16000000U  // 16 MHz internal oscillator
#define HSE_VALUE 8000000U   // 8 MHz external oscillator

/**
 * @brief Get the frequency of the PCLK1 (Peripheral Clock 1).
 *
 * This function calculates and returns the frequency of the PCLK1, which is the peripheral clock for APB1 peripherals.
 *
 * @return The PCLK1 frequency in Hertz.
 */
uint32_t RCC_GetPCLK1Value(void);

/**
 * @brief Get the frequency of the PCLK2 (Peripheral Clock 2).
 *
 * This function calculates and returns the frequency of the PCLK2, which is the peripheral clock for APB2 peripherals.
 *
 * @return The PCLK2 frequency in Hertz.
 */
uint32_t RCC_GetPCLK2Value(void);


/**
 * @brief Get the frequency of the PLL (Phase-Locked Loop) output clock.
 *
 * This function calculates and returns the frequency of the PLL output clock.
 *
 * @return The PLL output clock frequency in Hertz.
 */
uint32_t  RCC_GetPLLOutputClock(void);


#endif /* INC_STM32F407XX_RCC_DRIVER_H_ */
