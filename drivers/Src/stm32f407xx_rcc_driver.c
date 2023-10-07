/**
 * @file stm32f407xx_rcc_driver.c
 * @author Mohamed Ali Haoufa
 * @brief This file contains the RCC (Reset and Clock Control) driver implementation for STM32F407xx microcontrollers.
 *
 * This driver provides functions for configuring and controlling the system clock and peripheral clocks.
 *
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../drivers/Inc/stm32f407xx_rcc_driver.h"

// AHB and APB1 prescaler values
uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint8_t APB1_PreScaler[4] = {2, 4, 8, 16};

/**
 * @brief Get the frequency of the PCLK1 (Peripheral Clock 1).
 *
 * This function calculates and returns the frequency of the PCLK1, which is the peripheral clock for APB1 peripherals.
 *
 * @return The PCLK1 frequency in Hertz.
 */
uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, systemClk;
    uint8_t clksrc, temp, ahbp, apb1p;

    clksrc = ((RCC->CFGR >> RCC_CFGR_SWS) & 0x3);

    if (clksrc == 0)
    {
        systemClk = HSI_VALUE;
    }
    else if (clksrc == 1)
    {
        systemClk = HSE_VALUE;
    }
    else if (clksrc == 2)
    {
        systemClk = RCC_GetPLLOutputClock();
    }

    temp = ((RCC->CFGR >> RCC_CFGR_HPRE) & 0xF);

    if (temp < 8)
    {
        ahbp = 1;
    }
    else
    {
        ahbp = AHB_PreScaler[temp - 8];
    }

    temp = ((RCC->CFGR >> RCC_CFGR_PPRE1) & 0x7);

    if (temp < 4)
    {
        apb1p = 1;
    }
    else
    {
        apb1p = APB1_PreScaler[temp - 4];
    }

    pclk1 = (systemClk / ahbp) / apb1p;

    return pclk1;
}

/**
 * @brief Get the frequency of the PCLK2 (Peripheral Clock 2).
 *
 * This function calculates and returns the frequency of the PCLK2, which is the peripheral clock for APB2 peripherals.
 *
 * @return The PCLK2 frequency in Hertz.
 */
uint32_t RCC_GetPCLK2Value(void)
{
    uint32_t systemClock = 0, tmp, pclk2;
    uint8_t clkSrc = (RCC->CFGR >> RCC_CFGR_SWS) & 0X3;
    uint8_t ahbp, apb2p;

    if (clkSrc == 0)
    {
        systemClock = HSI_VALUE;
    }
    else
    {
        systemClock = HSE_VALUE;
    }

    tmp = (RCC->CFGR >> RCC_CFGR_HPRE) & 0xF;

    if (tmp < 0x08)
    {
        ahbp = 1;
    }
    else
    {
        ahbp = AHB_PreScaler[tmp - 8];
    }

    tmp = (RCC->CFGR >> RCC_CFGR_PPRE2) & 0x7;

    if (tmp < 0x04)
    {
        apb2p = 1;
    }
    else
    {
        apb2p = APB1_PreScaler[tmp - 4];
    }

    pclk2 = (systemClock / ahbp) / apb2p;

    return pclk2;
}

/**
 * @brief Get the frequency of the PLL (Phase-Locked Loop) output clock.
 *
 * This function calculates and returns the frequency of the PLL output clock.
 *
 * @return The PLL output clock frequency in Hertz.
 */
uint32_t RCC_GetPLLOutputClock(void)
{
    uint32_t pllInputFreq = 0;
    uint32_t plln = 0;
    uint32_t pllm = 0;
    uint32_t pllp = 0;

    // Read the PLL configuration settings from RCC_PLLCFGR register.
    plln = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLN) & 0x1FFU;
    pllm = (RCC->PLLCFGR >> RCC_PLLCFGR_PLLM) & 0x3FU;
    pllp = ((RCC->PLLCFGR >> RCC_PLLCFGR_PLLP) & 0x3U) + 1;

    // Determine the PLL input frequency based on the oscillator source (HSE or HSI).
    if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC_HSE) != 0)
    {
        // HSE is used as the PLL input source.
        pllInputFreq = HSE_VALUE;
    }
    else
    {
        // HSI is used as the PLL input source.
        pllInputFreq = HSI_VALUE;
    }

    // Calculate the PLL output frequency using the formula.
    uint32_t pllOutputFreq = (pllInputFreq * (plln + 1)) / ((pllm + 1) * (pllp * 2));

    return pllOutputFreq;
}

