/**
 * @file stm32f407xx.h
 * @author Mohamed Ali Haoufa
 * @brief Header file containing all the necessary information about the STM32F407xx MCU.
 * @version 0.1
 * @date 2023-10-07
 *
 * This file contains the definitions and macros for the STM32F407xx microcontroller
 * peripherals and memory maps.
 *
 * @copyright Copyright (c) 2023
 *
 */

/** @defgroup STM32F407XX_HEADER STM32F407xx MCU Header File
 * @{
 * @brief Header file containing all the necessary information about the STM32F407xx MCU.
 */
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/**
 * @defgroup STM32F407XX_DEFINITIONS Definitions and Macros
 * @{
 * @brief Various definitions and macros for the STM32F407xx MCU.
 */

/** @brief volatile_32bit_register Define for accessing a volatile 32-bit register */
#define __vo    volatile

/** @brief Define for the weak attribute */
#define __weak  __attribute__((weak))

/** @} STM32F407XX_DEFINITIONS */


/********************************** START : Processor Specific Details **********************************************/

/**
 * @defgroup NVIC_ISERx NVIC ISERx Registers
 * @{
 * @brief Base addresses for NVIC ISERx registers.
 */
#define NVIC_ISER0          ((__vo uint32_t*)0xE000E100)  
#define NVIC_ISER1          ((__vo uint32_t*)0xE000E104)  
#define NVIC_ISER2          ((__vo uint32_t*)0xE000E108)  
#define NVIC_ISER3          ((__vo uint32_t*)0xE000E10C)
#define NVIC_ISER4      	((__vo uint32_t*)0xE000E110)
#define NVIC_ISER5        	((__vo uint32_t*)0xE000E114)
#define NVIC_ISER6      	((__vo uint32_t*)0xE000E118)
#define NVIC_ISER7      	((__vo uint32_t*)0xE000E11C)
/** @} NVIC_ISERx */

/**
 * @defgroup NVIC_ICERx NVIC ICERx Registers
 * @{
 * @brief Base addresses for NVIC ICERx registers.
 */
#define NVIC_ICER0          ((__vo uint32_t*)0xE000E180)  
#define NVIC_ICER1          ((__vo uint32_t*)0xE000E184)  
#define NVIC_ICER2          ((__vo uint32_t*)0xE000E188)  
#define NVIC_ICER3          ((__vo uint32_t*)0xE000E18C)  
#define NVIC_ICER4		    ((__vo uint32_t*)0xE000E190)
#define NVIC_ICER5		    ((__vo uint32_t*)0xE000E194)
#define NVIC_ICER6  		((__vo uint32_t*)0xE000E198)
#define NVIC_ICER7		    ((__vo uint32_t*)0xE000E19C)
/** @} NVIC_ICERx */

/********************************** END : Processor Specific Details ************************************************/

/********************************** START : Memory Base Addresses ***************************************************/

/**
 * @defgroup NVIC_PR_BASE NVIC Priority Registers Base Address
 * @{
 * @brief Base address for NVIC Priority registers calculation.
 */

#define NVIC_PR_BASE_ADDR   ((__vo uint32_t*)0xE000E400)

/** @} NVIC_PR_BASE */

/**
 * @defgroup PR_BITS_IMPLEMENTED Priority Bits Implemented
 * @{
 * @brief Number of Priority bits implemented in the priority register.
 */

#define NO_PR_BITS_IMPLEMENTED      4

/** @} PR_BITS_IMPLEMENTED */

/**
 * @defgroup MEMORY_BASE_ADDRESSES Memory Base Addresses
 * @{
 * @brief Base addresses of memory regions.
 */
#define FLASH_BASEADDR               0x08000000U   /**< Base address of FLASH memory */
#define SRAM1_BASEADDR     (uint32_t)0x20000000    /**< Base address of SRAM1 memory */
#define SRAM                         SRAM1_BASE_ADDR

#define ROM_BASEADDR                 0x1FFF0000U   /**< Base address of ROM memory */
#define SRAM2_BASEADDR               0x2001C000U   /**< Base address of SRAM2 memory */

/** @} MEMORY_BASE_ADDRESSES */
/********************************** END : Memory Base Addresses *******************************************************/

/**
 * @defgroup STM32F407XX_PERIPHERALS Peripheral Base Addresses
 * @{
 * @brief Base addresses of various peripherals for the STM32F407xx MCU.
 */

/********************************** START : Peripheral Base Addresses *************************************************/

/**
 * @defgroup Peripheral_Base_Addresses Peripheral Base Addresses
 * @{
 * @brief Base addresses of AHBx and APBx bus peripherals.
 */
#define PERIPH_BASEADDR            0x40000000U	   /**< Base address of peripheral memory */
#define APB1PERIPH_BASEADDR        PERIPH_BASEADDR /**< Base address of APB1 peripheral memory */
#define APB2PERIPH_BASEADDR        0x40010000U	   /**< Base address of APB2 peripheral memory */
#define AHB1PERIPH_BASEADDR        0x40020000U	   /**< Base address of AHB1 peripheral memory */
#define AHB2PERIPH_BASEADDR        0x50000000U	   /**< Base address of AHB2 peripheral memory */

/** @} Peripheral_Base_Addresses */
/********************************** END : Peripheral Base Addresses ***************************************************/

/********************************** START : Peripheral Base Addresses on APB1 Bus *************************************/

/**
 * @defgroup Peripheral_Base_Addresses_APB1 Peripheral Base Addresses on APB1 Bus
 * @{
 * @brief Base addresses of peripherals connected to the APB1 bus.
 */
#define GPIOA_BASEADDR        (AHB1PERIPH_BASEADDR + 0x0000)    /**< Base address of GPIOA peripheral */
#define GPIOB_BASEADDR        (AHB1PERIPH_BASEADDR + 0x0400)    /**< Base address of GPIOB peripheral */
#define GPIOC_BASEADDR        (AHB1PERIPH_BASEADDR + 0x0800)    /**< Base address of GPIOC peripheral */
#define GPIOD_BASEADDR        (AHB1PERIPH_BASEADDR + 0x0C00)    /**< Base address of GPIOD peripheral */
#define GPIOE_BASEADDR        (AHB1PERIPH_BASEADDR + 0x1000)    /**< Base address of GPIOE peripheral */
#define GPIOF_BASEADDR        (AHB1PERIPH_BASEADDR + 0x1400)    /**< Base address of GPIOF peripheral */
#define GPIOG_BASEADDR        (AHB1PERIPH_BASEADDR + 0x1800)    /**< Base address of GPIOG peripheral */
#define GPIOH_BASEADDR        (AHB1PERIPH_BASEADDR + 0x1C00)    /**< Base address of GPIOH peripheral */
#define GPIOI_BASEADDR        (AHB1PERIPH_BASEADDR + 0x2000)    /**< Base address of GPIOI peripheral */
#define RCC_BASEADDR          (AHB1PERIPH_BASEADDR + 0x3800)    /**< Base address of RCC peripheral */
#define DMA1_BASEADDR         (AHB1PERIPH_BASEADDR + 0x6000)    /**< Base address of DMA1 peripheral */
#define DMA2_BASEADDR         (AHB1PERIPH_BASEADDR + 0x6400)    /**< Base address of DMA2 peripheral */
#define CRC_BASEADDR          (AHB1PERIPH_BASEADDR + 0x3000)    /**< Base address of CRC peripheral */
#define FIR_BASEADDR          (AHB1PERIPH_BASEADDR + 0x3C00)    /**< Base address of Flash Interface peripheral */

#define I2C1_BASEADDR         (APB1PERIPH_BASEADDR+0x5400)  /**< Base address of I2C1 peripheral */
#define I2C2_BASEADDR         (APB1PERIPH_BASEADDR+0x5800)  /**< Base address of I2C2 peripheral */
#define I2C3_BASEADDR         (APB1PERIPH_BASEADDR+0x5C00)  /**< Base address of I2C3 peripheral */

#define SPI2_BASEADDR         (APB1PERIPH_BASEADDR+0x3800)  /**< Base address of SPI2 peripheral */
#define SPI3_BASEADDR         (APB1PERIPH_BASEADDR+0x3C00)  /**< Base address of SPI3 peripheral */

#define USART2_BASEADDR       (APB1PERIPH_BASEADDR+0x4400)  /**< Base address of USART2 peripheral */
#define USART3_BASEADDR       (APB1PERIPH_BASEADDR+0x4800)  /**< Base address of USART3 peripheral */
#define UART4_BASEADDR        (APB1PERIPH_BASEADDR+0x4C00)  /**< Base address of UART4 peripheral */
#define UART5_BASEADDR        (APB1PERIPH_BASEADDR+0x5000)  /**< Base address of UART5 peripheral */

/** @} Peripheral_Base_Addresses_APB1 */
/********************************** END : Peripheral Base Addresses on APB1 Bus ***************************************************/

/********************************** START : Peripheral Base Addresses on APB2 Bus *************************************************/
/**
 * @defgroup Peripheral_Base_Addresses_APB2 Peripheral Base Addresses on APB2 Bus
 * @{
 * @brief Base addresses of peripherals connected to the APB2 bus.
 */
#define SPI1_BASEADDR         (APB2PERIPH_BASEADDR+0x3000)  /**< Base address of SPI1 peripheral */
#define SPI4_BASEADDR         (APB2PERIPH_BASEADDR+0x3400)  /**< Base address of SPI4 peripheral */
#define USART1_BASEADDR       (APB2PERIPH_BASEADDR+0x1000)  /**< Base address of USART1 peripheral */
#define USART6_BASEADDR       (APB2PERIPH_BASEADDR+0x1400)  /**< Base address of USART6 peripheral */
#define SYSCFG_BASEADDR       (APB2PERIPH_BASEADDR+0x3800)  /**< Base address of SYSCFG peripheral */
#define EXTI_BASEADDR         (APB2PERIPH_BASEADDR+0x3C00)  /**< Base address of EXTI peripheral */
/** @} Peripheral_Base_Addresses_APB2 */

/** @} STM32F407XX_PERIPHERALS */
/********************************** END : Peripheral Base Addresses on APB2 Bus ***************************************************/

/********************************** START : Peripheral register definition structure **********************************************/
/**
 * @defgroup Peripheral_Registers Peripheral Register Definitions
 * @{
 * @brief Structures defining the register layouts for various peripherals.
 */

/**
 * @struct GPIO_RegDef_t
 * @brief GPIO peripheral register definition structure
 */
typedef struct {
    __vo uint32_t MODER;      /**< GPIO port mode register */
    __vo uint32_t OTYPER;     /**< GPIO port output type register */
    __vo uint32_t OSPEEDR;    /**< GPIO port output speed register */
    __vo uint32_t PUPDR;      /**< GPIO port pull-up/pull-down register */
    __vo uint32_t IDR;        /**< GPIO port input data register */
    __vo uint32_t ODR;        /**< GPIO port output data register */
    __vo uint32_t BSRR;       /**< GPIO port bit set/reset register */
    __vo uint32_t LCKR;       /**< GPIO port configuration lock register */
    __vo uint32_t AFR[2];     /**< GPIO alternate function registers (AFR[0] = low, AFR[1] = high) */
} GPIO_RegDef_t;

/**
 * @struct RCC_RegDef_t
 * @brief RCC peripheral register definition structure
 */
typedef struct {
    __vo uint32_t CR;         /**< RCC control register */
    __vo uint32_t PLLCFGR;    /**< RCC PLL configuration register */
    __vo uint32_t CFGR;       /**< RCC configuration register */
    __vo uint32_t CIR;        /**< RCC clock configuration register */
    __vo uint32_t AHB1RSTR;   /**< RCC AHB1 peripheral reset register */
    __vo uint32_t AHB2RSTR;   /**< RCC AHB2 peripheral reset register */
    __vo uint32_t AHB3RSTR;   /**< RCC AHB3 peripheral reset register */
    uint32_t      RESERVED0;
    __vo uint32_t APB1RSTR;   /**< RCC APB1 peripheral reset register */
    __vo uint32_t APB2RSTR;   /**< RCC APB2 peripheral reset register */
    uint32_t      RESERVED1[2];
    __vo uint32_t AHB1ENR;    /**< RCC AHB1 peripheral clock enable register */
    __vo uint32_t AHB2ENR;    /**< RCC AHB2 peripheral clock enable register */
    __vo uint32_t AHB3ENR;    /**< RCC AHB3 peripheral clock enable register */
    uint32_t      RESERVED2;
    __vo uint32_t APB1ENR;    /**< RCC APB1 peripheral clock enable register */
    __vo uint32_t APB2ENR;    /**< RCC APB2 peripheral clock enable register */
    uint32_t      RESERVED3[2];
    __vo uint32_t AHB1LPENR;  /**< RCC AHB1 peripheral clock enable in low power mode register */
    __vo uint32_t AHB2LPENR;  /**< RCC AHB2 peripheral clock enable in low power mode register */
    __vo uint32_t AHB3LPENR;  /**< RCC AHB3 peripheral clock enable in low power mode register */
    uint32_t      RESERVED4;
    __vo uint32_t APB1LPENR;  /**< RCC APB1 peripheral clock enable in low power mode register */
    __vo uint32_t APB2LPENR;  /**< RCC APB2 peripheral clock enable in low power mode register */
    uint32_t      RESERVED5[2];
    __vo uint32_t BDCR;       /**< RCC backup domain control register */
    __vo uint32_t CSR;        /**< RCC control/status register */
    uint32_t      RESERVED6[2];
    __vo uint32_t SSCGR;      /**< RCC spread spectrum clock generation register */
    __vo uint32_t PLLI2SCFGR; /**< RCC PLLI2S configuration register */
    __vo uint32_t PLLSAICFGR; /**< RCC PLLSAI configuration register */
    __vo uint32_t DCKCFGR;    /**< RCC dedicated clock configuration register */
    __vo uint32_t CKGATENR;   /**< RCC clocks gated enable register */
    __vo uint32_t DCKCFGR2;   /**< RCC dedicated clocks configuration register 2 */
} RCC_RegDef_t;

/**
 * @struct EXTI_RegDef_t
 * @brief EXTI peripheral register definition structure
 */
typedef struct {
    __vo uint32_t IMR;      /**< EXTI interrupt mask register */
    __vo uint32_t EMR;      /**< EXTI event mask register */
    __vo uint32_t RTSR;     /**< EXTI rising trigger selection register */
    __vo uint32_t FTSR;     /**< EXTI falling trigger selection register */
    __vo uint32_t SWIER;    /**< EXTI software interrupt event register */
    __vo uint32_t PR;       /**< EXTI pending register */
} EXTI_RegDef_t;

/**
 * @struct SYSCFG_RegDef_t
 * @brief SYSCFG peripheral register definition structure
 */
typedef struct {
    __vo uint32_t MEMRMP;    /**< SYSCFG memory remap register (Offset: 0x00) */
    __vo uint32_t PMC;       /**< SYSCFG peripheral mode configuration register (Offset: 0x04) */
    __vo uint32_t EXTICR[4]; /**< SYSCFG external interrupt configuration registers (Offset: 0x08 - 0x14) */
    uint32_t      RESERVED1[2]; /**< Reserved bits (Offset: 0x18 - 0x1F) */
    __vo uint32_t CMPCR;     /**< SYSCFG Compensation cell control register (Offset: 0x20) */
    uint32_t      RESERVED2[2]; /**< Reserved bits (Offset: 0x24 - 0x2B) */
    __vo uint32_t CFGR;      /**< SYSCFG configuration register (Offset: 0x2C) */
} SYSCFG_RegDef_t;

/**
 * @struct SPI_RegDef_t
 * @brief SPI peripheral register definition structure
 */
typedef struct {
    __vo uint32_t CR1;    /* SPI Control Register 1 (0x00) */
    __vo uint32_t CR2;    /* SPI Control Register 2 (0x04) */
    __vo uint32_t SR;     /* SPI Status Register (0x08) */
    __vo uint32_t DR;     /* SPI Data Register (0x0C) */
    __vo uint32_t CRCPR;  /* SPI CRC Polynomial Register (0x10) */
    __vo uint32_t RXCRCR; /* SPI RX CRC Register (0x14) */
    __vo uint32_t TXCRCR; /* SPI TX CRC Register (0x18) */
    __vo uint32_t I2SCFGR;/* SPI_I2S configuration register (0x1C) */
    __vo uint32_t I2SPR;  /* SPI_I2S prescaler register (0x20) */
} SPI_RegDef_t;

/**
 * @struct I2C_RegDef_t
 * @brief I2C peripheral register definition structure
 */
typedef struct {
    __vo uint32_t CR1;       /**< I2C control register 1 */
    __vo uint32_t CR2;       /**< I2C control register 2 */
    __vo uint32_t OAR1;      /**< I2C own address register 1 */
    __vo uint32_t OAR2;      /**< I2C own address register 2 */
    __vo uint32_t DR;        /**< I2C data register */
    __vo uint32_t SR1;       /**< I2C status register 1 */
    __vo uint32_t SR2;       /**< I2C status register 2 */
    __vo uint32_t CCR;       /**< I2C clock control register */
    __vo uint32_t TRISE;     /**< I2C rise time register */
    __vo uint32_t FLTR;      /**< I2C digital filter register */
} I2C_RegDef_t;

/**
 * @struct USART_RegDef_t
 * @brief USART peripheral register definition structure
 */
typedef struct
{
    __vo uint32_t SR;    /* USART Status Register (0x00) */
    __vo uint32_t DR;    /* USART Data Register (0x04) */
    __vo uint32_t BRR;   /* USART Baud Rate Register (0x08) */
    __vo uint32_t CR1;   /* USART Control Register 1 (0x0C) */
    __vo uint32_t CR2;   /* USART Control Register 2 (0x10) */
    __vo uint32_t CR3;   /* USART Control Register 3 (0x14) */
    __vo uint32_t GTPR;  /* USART Guard time and prescaler Register (0x18) */

} USART_RegDef_t;

/** @} Peripheral_Registers */
/********************************** END : Peripheral register definition structure ***********************************/

/********************************** START : Peripheral Definitions ***************************************************/

/**
 * @defgroup Peripheral_Definitions Peripheral Definitions
 * @{
 * @brief Definitions for various peripheral instances based on their base addresses.
 */
#define  GPIOA       ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define  GPIOB       ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define  GPIOC       ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define  GPIOD       ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define  GPIOE       ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define  GPIOF       ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define  GPIOG       ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define  GPIOH       ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define  GPIOI       ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC          ((RCC_RegDef_t*)RCC_BASEADDR)  

#define EXTI         ((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG       ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

#define SPI1         ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2         ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3         ((SPI_RegDef_t*)SPI3_BASEADDR)
#define SPI4         ((SPI_RegDef_t*)SPI4_BASEADDR)

#define I2C1         ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2         ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3         ((I2C_RegDef_t*)I2C3_BASEADDR)

#define USART1         ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2         ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3         ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4          ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5          ((USART_RegDef_t*)UART5_BASEADDR)
#define USART6         ((USART_RegDef_t*)USART6_BASEADDR)

/** @} Peripheral Definitions */
/********************************** END : Peripheral Definitions ***************************************************/

/********************************** START : Clock Enable Macros ***************************************************/
/**
 * @defgroup Clock_Enable_Macros Clock Enable Macros
 * @{
 */

/**
 * @defgroup Clock_Enable_GPIO_Clocks Clock Enable GPIO Clocks
 * @{
 * @brief Macros for enabling clocks to GPIO peripherals.
 */
#define GPIOA_PCLK_EN()      ( RCC->AHB1ENR |= (1<<0) )
#define GPIOB_PCLK_EN()      ( RCC->AHB1ENR |= (1<<1) )
#define GPIOC_PCLK_EN()      ( RCC->AHB1ENR |= (1<<2) )
#define GPIOD_PCLK_EN()      ( RCC->AHB1ENR |= (1<<3) )
#define GPIOE_PCLK_EN()      ( RCC->AHB1ENR |= (1<<4) )
#define GPIOF_PCLK_EN()      ( RCC->AHB1ENR |= (1<<5) )
#define GPIOG_PCLK_EN()      ( RCC->AHB1ENR |= (1<<6) )
#define GPIOH_PCLK_EN()      ( RCC->AHB1ENR |= (1<<7) )
#define GPIOI_PCLK_EN()      ( RCC->AHB1ENR |= (1<<8) )
/** @} Clock_Enable_GPIO_Clocks */

/**
 * @defgroup Clock_Enable_I2C_Clocks Clock Enable I2C Clocks
 * @{
 * @brief Macros for enabling clocks to I2C peripherals.
 */ 
#define I2C1_PCLK_EN()      ( RCC->APB1ENR |= (1<<21) )
#define I2C2_PCLK_EN()      ( RCC->APB1ENR |= (1<<22) )
#define I2C3_PCLK_EN()      ( RCC->APB1ENR |= (1<<23) )
/** @} Clock_Enable_I2C_Clocks */

/**
 * @defgroup Clock_Enable_SPI_Clocks Clock Enable SPI Clocks
 * @{
 * @brief Macros for enabling clocks to SPI peripherals.
 */
#define SPI1_PCLK_EN()      ( RCC->APB2ENR |= (1<<12) )
#define SPI2_PCLK_EN()      ( RCC->APB1ENR |= (1<<14) )
#define SPI3_PCLK_EN()      ( RCC->APB1ENR |= (1<<15) )
#define SPI4_PCLK_EN() 		( RCC->APB2ENR |= (1<<13) )
/** @} Clock_Enable_SPI_Clocks */

/**
 * @defgroup Clock_Enable_USART_Clocks Clock Enable USART Clocks
 * @{
 * @brief Macros for enabling clocks to USART peripherals.
 */
#define USART1_PCLK_EN()      ( RCC->APB2ENR |= (1<<4) )
#define USART2_PCLK_EN()      ( RCC->APB1ENR |= (1<<17) )
#define USART3_PCLK_EN()      ( RCC->APB1ENR |= (1<<18) )
#define UART4_PCLK_EN()       ( RCC->APB1ENR |= (1<<19) )
#define UART5_PCLK_EN()       ( RCC->APB1ENR |= (1<<20) )
#define USART6_PCLK_EN()      ( RCC->APB2ENR |= (1<<5) )
/** @} Clock_Enable_USART_Clocks */

/**
 * @defgroup Clock_Enable_SYSCFG_Clocks Clock Enable SYSCFG Clocks
 * @{
 * @brief Macros for enabling clocks to SYSCFG peripherals.
 */
#define SYSCFG_PCLK_EN()      ( RCC->APB2ENR |= (1<<14) )
/** @} Clock_Enable_SYSCFG_Clocks */

/** @} Clock_Enable_Macros */
/********************************** END : Clock Enable Macros ******************************************************/

/********************************** START : Clock Disable Macros ***************************************************/
/**
 * @defgroup Clock_Disable_Macros Clock Disable Macros
 * @{
 */

/**
 * @defgroup Disable_clock_for_GPIOx Disable clock for GPIOx peripherals
 * @{
 */
#define GPIOA_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<0) )
#define GPIOB_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<1) )
#define GPIOC_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<2) )
#define GPIOD_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<3) )
#define GPIOE_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<4) )
#define GPIOF_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<5) )
#define GPIOG_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<6) )
#define GPIOH_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<7) )
#define GPIOI_PCLK_DI()      ( RCC->AHB1ENR &= ~(uint32_t)(1<<8) )
/** @} Disable_clock_for_GPIOx */

/**
 * @defgroup Disable_clock_for_I2Cx Disable clock for I2Cx peripherals
 * @{
 */
#define I2C1_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<21) )
#define I2C2_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<22) )
#define I2C3_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<23) )
/** @} Disable_clock_for_I2Cx */

/**
 * @defgroup Disable_clock_for_SPIx Disable clock for SPIx peripherals
 * @{
 */
#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~(uint32_t)(1<<12) )
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<14) )
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<15) )
#define SPI4_PCLK_DI()      ( RCC->APB2ENR &= ~(uint32_t)(1<<13) )
/** @} Disable_clock_for_SPIx */

/**
 * @defgroup Disable_clock_for_USARTx Disable clock for USARTx peripherals
 * @{
 */
#define USART1_PCLK_DI()      ( RCC->APB2ENR &= ~(uint32_t)(1<<4) )
#define USART2_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<17) )
#define USART3_PCLK_DI()      ( RCC->APB1ENR &= ~(uint32_t)(1<<18) )
#define UART4_PCLK_DI()       ( RCC->APB1ENR &= ~(uint32_t)(1<<19) )
#define UART5_PCLK_DI()       ( RCC->APB1ENR &= ~(uint32_t)(1<<20) )
#define USART6_PCLK_DI()      ( RCC->APB2ENR &= ~(uint32_t)(1<<5) )
/** @} Disable_clock_for_USARTx */

/**
 * @defgroup Disable_clock_for_SYSCFG Disable clock for SYSCFG peripherals
 * @{
 */
#define SYSCFG_PCLK_DI()      ( RCC->APB2ENR &= ~(uint32_t)(1<<14) )
/** @} Disable_clock_for_SYSCFG */

/** @} Clock_Disable_Macros */
/********************************** END : Clock Disable Macros *********************************************************/

/********************************** START : Reset peripherals Macros ***************************************************/
/**
 * @defgroup Reset_Peripherals_Macros Reset Peripherals Macros
 * @{
 * @brief Macros for resetting various peripherals.
 */

/**
 * @defgroup Reset_GPIOx_Reset Reset GPIOx Peripherals
 * @{
 * @brief Macros for resetting GPIO peripherals.
 */
#define GPIOA_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<0) ); ( RCC->AHB1RSTR  &= ~(1<<0) );}while(0)
#define GPIOB_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<1) ); ( RCC->AHB1RSTR  &= ~(1<<1) );}while(0)
#define GPIOC_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<2) ); ( RCC->AHB1RSTR  &= ~(1<<2) );}while(0)
#define GPIOD_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<3) ); ( RCC->AHB1RSTR  &= ~(1<<3) );}while(0)
#define GPIOE_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<4) ); ( RCC->AHB1RSTR  &= ~(1<<4) );}while(0)
#define GPIOF_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<5) ); ( RCC->AHB1RSTR  &= ~(1<<5) );}while(0)
#define GPIOG_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<6) ); ( RCC->AHB1RSTR  &= ~(1<<6) );}while(0)
#define GPIOH_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<7) ); ( RCC->AHB1RSTR  &= ~(1<<7) );}while(0)
#define GPIOI_REG_RESET()     do{ ( RCC->AHB1RSTR |= (1<<8) ); ( RCC->AHB1RSTR  &= ~(1<<8) );}while(0)
/** @} Reset_GPIOx_Reset */

/**
 * @defgroup Reset_I2Cx_Reset Reset I2Cx Peripherals
 * @{
 * @brief Macros for resetting I2C peripherals.
 */
#define I2C1_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<21) ); ( RCC->APB1RSTR  &= ~(1<<21) );}while(0)
#define I2C2_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<22) ); ( RCC->APB1RSTR  &= ~(1<<22) );}while(0)
#define I2C3_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<23) ); ( RCC->APB1RSTR  &= ~(1<<23) );}while(0)
/** @} Reset_I2Cx_Reset */

/**
 * @defgroup Reset_SPIx_Reset Reset SPIx Peripherals
 * @{
 * @brief Macros for resetting SPI peripherals.
 */
#define SPI1_REG_RESET()     do{ ( RCC->APB2RSTR |= (1<<12) ); ( RCC->APB2RSTR  &= ~(1<<12) );}while(0)
#define SPI2_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<14) ); ( RCC->APB1RSTR  &= ~(1<<14) );}while(0)
#define SPI3_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<15) ); ( RCC->APB1RSTR  &= ~(1<<15) );}while(0)
#define SPI4_REG_RESET()     do{ ( RCC->APB2RSTR |= (1<<13) ); ( RCC->APB2RSTR  &= ~(1<<13) );}while(0)
/** @} Reset_SPIx_Reset */

/**
 * @defgroup Reset_USARTx_Reset Reset USARTx Peripherals
 * @{
 * @brief Macros for resetting USART peripherals.
 */
#define USART1_REG_RESET()     do{ ( RCC->APB2RSTR |= (1<<4) );  ( RCC->APB2RSTR  &= ~(1<<4) );}while(0)
#define USART2_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<17) ); ( RCC->APB1RSTR  &= ~(1<<17) );}while(0)
#define USART3_REG_RESET()     do{ ( RCC->APB1RSTR |= (1<<18) ); ( RCC->APB1RSTR  &= ~(1<<18) );}while(0)
#define UART4_REG_RESET()      do{ ( RCC->APB1RSTR |= (1<<19) ); ( RCC->APB1RSTR  &= ~(1<<19) );}while(0)
#define UART5_REG_RESET()      do{ ( RCC->APB1RSTR |= (1<<20) ); ( RCC->APB1RSTR  &= ~(1<<20) );}while(0)
#define USART6_REG_RESET()     do{ ( RCC->APB2RSTR |= (1<<5) );  ( RCC->APB2RSTR  &= ~(1<<5) );}while(0)
/** @} Reset_USARTx_Reset */

/** @} Reset_Peripherals_Macros */
/********************************** END : Reset peripherals Macros ***************************************************/

/**
 * @defgroup GPIO_Base_Address_to_Code GPIO Base Address to Code Conversion Macros
 * @{
 * @brief Macros for converting GPIO base addresses to corresponding port codes.
 */

/**
 * @brief Macro to convert GPIO base address to port code.
 *
 * @param x GPIOx base address.
 * @return Corresponding port code for the given GPIO base address.
 */
#define GPIO_BASEADDR_TO_CODE(x)  (   (x == GPIOA)?0:\
                                      (x == GPIOB)?1:\
                                      (x == GPIOC)?2:\
                                      (x == GPIOD)?3:\
                                      (x == GPIOE)?4:\
                                      (x == GPIOF)?5:\
                                      (x == GPIOG)?6:\
                                      (x == GPIOH)?7:\
                                      (x == GPIOI)?8:0 )

/** @} GPIO_Base_Address_to_Code */

/********************************** START : IRQ (interrupt request) Numbers Macros ***************************************************/

/**
 * @defgroup IRQ_Numbers_Macros IRQ Numbers Macros
 * @{
 * @brief Macros for interrupt request numbers and priority levels.
 */

/**
 * @defgroup IRQ_Numbers EXTI (External Interrupt) IRQ Numbers
 * @{
 * @brief IRQ numbers for EXTI (External Interrupt) sources.
 */
#define IRQ_NO_EXTI0          6
#define IRQ_NO_EXTI1          7 
#define IRQ_NO_EXTI2          8
#define IRQ_NO_EXTI3          9
#define IRQ_NO_EXTI4          10
#define IRQ_NO_EXTI9_5        23
#define IRQ_NO_EXTI15_10      40
/** @} IRQ_Numbers EXTI (External Interrupt) IRQ Numbers */

/**
 * @defgroup IRQ_Numbers SPI IRQ Numbers
 * @{
 * @brief IRQ numbers for SPI sources.
 */
#define IRQ_NO_SPI1           35
#define IRQ_NO_SPI2           36
#define IRQ_NO_SPI3           51
#define IRQ_NO_SPI4           84
/** @} IRQ_Numbers SPI IRQ Numbers */

/**
 * @defgroup IRQ_Numbers I2C IRQ Numbers
 * @{
 * @brief IRQ numbers for I2C sources.
 */
#define IRQ_NO_I2C1_EV        31 
#define IRQ_NO_I2C1_ER        32
#define IRQ_NO_I2C2_EV        33
#define IRQ_NO_I2C2_ER        34
#define IRQ_NO_I2C3_EV        79
#define IRQ_NO_I2C3_ER        80
/** @} IRQ_Numbers I2C IRQ Numbers */

/**
 * @defgroup IRQ_Numbers UART IRQ Numbers
 * @{
 * @brief IRQ numbers for UART sources.
 */
#define IRQ_NO_USART1         37
#define IRQ_NO_USART2         38
#define IRQ_NO_USART3         39
#define IRQ_NO_UART4          52
#define IRQ_NO_UART5          53
#define IRQ_NO_USART6         71
/** @} IRQ_Numbers UART IRQ Numbers */

/** @} IRQ_Numbers_Macros */
/********************************** END : IRQ (interrupt request) Numbers Macros ***************************************************/

/********************************** START : ALL NVIC possible priority levels Macros ***********************************************/

/**
 * @defgroup NVIC_Priority_Levels NVIC Priority Levels Macros
 * @{
 * @brief Macros for all possible priority levels for NVIC.
 */
#define NVIC_IRQ_PRI0     0
#define NVIC_IRQ_PRI1     1
#define NVIC_IRQ_PRI2     2
#define NVIC_IRQ_PRI3     3
#define NVIC_IRQ_PRI4     4
#define NVIC_IRQ_PRI5     5
#define NVIC_IRQ_PRI6     6
#define NVIC_IRQ_PRI7     7
#define NVIC_IRQ_PRI8     8
#define NVIC_IRQ_PRI9     9
#define NVIC_IRQ_PRI10    10
#define NVIC_IRQ_PRI11    11
#define NVIC_IRQ_PRI12    12
#define NVIC_IRQ_PRI13    13
#define NVIC_IRQ_PRI14    14
#define NVIC_IRQ_PRI15    15
/** @} NVIC_Priority_Levels */

/********************************** END : ALL NVIC possible priority levels Macros ********************************************/

/********************************** START : Bit position definitions Macros ***************************************************/

/**
 * @defgroup SPI_Bit_Positions SPI Bit Position Definitions
 * @{
 * @brief Bit position definitions for various registers in the SPI peripheral.
 */
/**
 * @defgroup SPI_CR1_Bit_Positions SPI_CR1 Bit Position Definitions
 * @brief Bit position definitions for SPI_CR1 register.
 * @{
 */
#define SPI_CR1_CPHA        0  /**< Clock Phase */
#define SPI_CR1_CPOL        1  /**< Clock Polarity */
#define SPI_CR1_MSTR        2  /**< Master Selection */
#define SPI_CR1_BR          3  /**< Baud Rate Control */
#define SPI_CR1_SPE         6  /**< SPI Peripheral Enable */
#define SPI_CR1_LSBFIRST    7  /**< Frame Format */
#define SPI_CR1_SSI         8  /**< Internal Slave Select */
#define SPI_CR1_SSM         9  /**< Software Slave Management */
#define SPI_CR1_RXONLY      10 /**< Receive Only */
#define SPI_CR1_DFF         11 /**< Data Frame Format */
#define SPI_CR1_CRCNEXT     12 /**< CRC Transfer Next */
#define SPI_CR1_CRCEN       13 /**< CRC Calculation Enable */
#define SPI_CR1_BIDIOE      14 /**< Output Enable in Bidirectional Mode */
#define SPI_CR1_BIDIMODE    15 /**< Bidirectional Data Mode Enable */
/** @} SPI_CR1_Bit_Positions */

/**
 * @defgroup SPI_CR2_Bit_Positions SPI_CR2 Bit Position Definitions
 * @brief Bit position definitions for SPI_CR2 register.
 * @{
 */
#define SPI_CR2_RXDMAEN     0  /**< Rx Buffer DMA Enable */
#define SPI_CR2_TXDMAEN     1  /**< Tx Buffer DMA Enable */
#define SPI_CR2_SSOE        2  /**< SS Output Enable */
#define SPI_CR2_FRF         4  /**< Frame Format */
#define SPI_CR2_ERRIE       5  /**< Error Interrupt Enable */
#define SPI_CR2_RXNEIE      6  /**< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE       7  /**< TX buffer Empty Interrupt Enable */
/** @} SPI_CR2_Bit_Positions */

/**
 * @defgroup SPI_SR_Bit_Positions SPI_SR Bit Position Definitions
 * @brief Bit position definitions for SPI_SR register.
 * @{
 */
#define SPI_SR_RXNE         0  /**< Receive buffer Not Empty */
#define SPI_SR_TXE          1  /**< Transmit buffer Empty */
#define SPI_SR_CHSIDE       2  /**< Channel Side */
#define SPI_SR_UDR          3  /**< Underrun Flag */
#define SPI_SR_CRCERR       4  /**< CRC Error Flag */
#define SPI_SR_MODF         5  /**< Mode Fault */
#define SPI_SR_OVR          6  /**< Overrun Flag */
#define SPI_SR_BSY          7  /**< Busy Flag */
#define SPI_SR_FRE          8  /**< Frame Format Error Flag */
/** @} SPI_SR_Bit_Positions */


/** @} SPI_Bit_Positions */



/**
 * @defgroup I2C_Bit_Positions I2C Bit Position Definitions
 * @{
 * @brief Bit position definitions for various registers in the I2C peripheral.
 */

/** 
 * @defgroup I2C_CR1_Bit_Positions I2C_CR1 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_CR1 register.
 */
#define I2C_CR1_PE           0    /**< Peripheral Enable */
#define I2C_CR1_SMBUS        1    /**< SMBus Mode */
#define I2C_CR1_SMBTYPE      3    /**< SMBus Type */
#define I2C_CR1_ENARP        4    /**< ARP Enable */
#define I2C_CR1_ENPEC        5    /**< PEC Enable */
#define I2C_CR1_ENGC         6    /**< General Call Enable */
#define I2C_CR1_NOSTRETCH    7    /**< Clock Stretching Disable */
#define I2C_CR1_START        8    /**< Start Generation */
#define I2C_CR1_STOP         9    /**< Stop Generation */
#define I2C_CR1_ACK          10   /**< Acknowledge Enable */
#define I2C_CR1_POS          11   /**< Acknowledge/Not Acknowledge */
#define I2C_CR1_PEC          12   /**< Packet Error Checking */
#define I2C_CR1_ALERT        13   /**< SMBus Alert */
#define I2C_CR1_SWRST        15   /**< Software Reset */
/** @} I2C_CR1_Bit_Positions */

/** 
 * @defgroup I2C_OAR1_Bit_Positions I2C_OAR1 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_OAR1 register.
 */
#define I2C_OAR1_ADD0        0    /**< Addressing Mode Bit 0 */
#define I2C_OAR1_ADD         1    /**< Interface Address */
#define I2C_OAR1_ADDMODE     15   /**< Addressing Mode */
/** @} I2C_OAR1_Bit_Positions */

/** 
 * @defgroup I2C_OAR2_Bit_Positions I2C_OAR2 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_OAR2 register.
 */
#define I2C_OAR2_ENDUAL      0    /**< Dual Addressing Mode Enable */
#define I2C_OAR2_ADD2        1    /**< Interface Address 2 */
/** @} I2C_OAR2_Bit_Positions */

/* 
 * Bit position definitions for I2C_DR
 * Note: Bit positions for I2C_DR are missing in the provided content
 */

/** 
 * @defgroup I2C_CR2_Bit_Positions I2C_CR2 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_CR2 register.
 */
#define I2C_CR2_FREQ      0    /**< Peripheral Clock Frequency */
#define I2C_CR2_ITERREN   8    /**< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN   9    /**< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN   10   /**< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN     11   /**< DMA Requests Enable */
#define I2C_CR2_LAST      12   /**< DMA Last Transfer */
/** @} I2C_CR2_Bit_Positions */

/** 
 * @defgroup I2C_SR1_Bit_Positions I2C_SR1 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_SR1 register.
 */
#define I2C_SR1_SB        0    /**< Start Bit */
#define I2C_SR1_ADDR      1    /**< Address Sent (master mode) / Address Matched (slave mode) */
#define I2C_SR1_BTF       2    /**< Byte Transfer Finished */
#define I2C_SR1_ADD10     3    /**< 10-bit Header Sent (Master mode) */
#define I2C_SR1_STOPF     4    /**< Stop Detection (Slave mode) */
#define I2C_SR1_RxNE      6    /**< Data Register Not Empty (receivers) */
#define I2C_SR1_TxE       7    /**< Data Register Empty (transmitters) */
#define I2C_SR1_BERR      8    /**< Bus Error */
#define I2C_SR1_ARLO      9    /**< Arbitration Lost (master mode) */
#define I2C_SR1_AF        10   /**< Acknowledge Failure */
#define I2C_SR1_OVR       11   /**< Overrun/Underrun */
#define I2C_SR1_PECERR    12   /**< PEC Error in reception */
#define I2C_SR1_TIMEOUT   14   /**< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT  15   /**< SMBus Alert */
/** @} I2C_SR1_Bit_Positions */

/** 
 * @defgroup I2C_SR2_Bit_Positions I2C_SR2 Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_SR2 register.
 */
#define I2C_SR2_MSL         0    /**< Master/Slave */
#define I2C_SR2_BUSY        1    /**< Bus Busy */
#define I2C_SR2_TRA         2    /**< Transmitter/Receiver */
#define I2C_SR2_GENCALL     4    /**< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT  5    /**< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST     6    /**< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF       7    /**< Dual Flag (Slave mode) */
#define I2C_SR2_PEC         8    /**< Packet Error Checking Register */
/** @} I2C_SR2_Bit_Positions */

/** 
 * @defgroup I2C_CCR_Bit_Positions I2C_CCR Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_CCR register.
 */
#define I2C_CCR_CCR         0    /**< Clock Control Register in Fast/Standard mode */
#define I2C_CCR_DUTY        14   /**< Fast Mode Duty Cycle */
#define I2C_CCR_FS          15   /**< I2C Master Mode Selection */
/** @} I2C_CCR_Bit_Positions */

/** 
 * @defgroup I2C_TRISE_Bit_Positions I2C_TRISE Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_TRISE register.
 */
#define I2C_TRISE_TRISE     0    /**< Maximum Rise Time in Fast/Standard mode */
/** @} I2C_TRISE_Bit_Positions */

/** 
 * @defgroup I2C_FLTR_Bit_Positions I2C_FLTR Bit Position Definitions
 * @{
 * @brief Bit position definitions for I2C_FLTR register.
 */
#define I2C_FLTR_DNF        0    /**< Digital Noise Filter */
#define I2C_FLTR_ANOFF      4    /**< Analog Noise Filter */
/** @} I2C_FLTR_Bit_Positions */

/** @} I2C_Bit_Positions */


/**
 * @defgroup USART_Bit_Positions USART Bit Position Definitions
 * @brief Bit position definitions for various registers in the USART peripheral.
 * @{
 */

/**
 * @defgroup USART_SR_Bit_Positions USART_SR Bit Position Definitions
 * @brief Bit position definitions for USART_SR register.
 * @{
 */
#define USART_SR_PE     0  /**< Parity Error Flag */
#define USART_SR_FE     1  /**< Framing Error Flag */
#define USART_SR_NF     2  /**< Noise Flag */
#define USART_SR_ORE    3  /**< Overrun Error Flag */
#define USART_SR_IDLE   4  /**< Idle Line Detected Flag */
#define USART_SR_RXNE   5  /**< Read Data Register Not Empty Flag */
#define USART_SR_TC     6  /**< Transmission Complete Flag */
#define USART_SR_TXE    7  /**< Transmit Data Register Empty Flag */
#define USART_SR_LBD    8  /**< LIN Break Detection Flag */
#define USART_SR_CTS    9  /**< CTS Interrupt Flag */

/** @} USART_SR_Bit_Positions */

/**
 * @defgroup USART_DR_Bit_Positions USART_DR Bit Position Definitions
 * @brief Bit position definitions for USART_DR register.
 * @{
 */
#define USART_DR_DR     0  /**< Data Value (0-8 bits) */

/** @} USART_DR_Bit_Positions */

/**
 * @defgroup USART_BRR_Bit_Positions USART_BRR Bit Position Definitions
 * @brief Bit position definitions for USART_BRR register.
 * @{
 */
#define USART_BRR_DIV_FRACTION   0  /**< Fractional part of the USARTDIV */
#define USART_BRR_DIV_MANTISSA   4  /**< Mantissa part of the USARTDIV */

/** @} USART_BRR_Bit_Positions */

/**
 * @defgroup USART_CR1_Bit_Positions USART_CR1 Bit Position Definitions
 * @brief Bit position definitions for USART_CR1 register.
 * @{
 */
#define USART_CR1_SBK       0  /**< Send Break */
#define USART_CR1_RWU       1  /**< Receiver Wake-Up */
#define USART_CR1_RE        2  /**< Receiver Enable */
#define USART_CR1_TE        3  /**< Transmitter Enable */
#define USART_CR1_IDLEIE    4  /**< IDLE Interrupt Enable */
#define USART_CR1_RXNEIE    5  /**< RXNE Interrupt Enable */
#define USART_CR1_TCIE      6  /**< Transmission Complete Interrupt Enable */
#define USART_CR1_TXEIE     7  /**< TXE Interrupt Enable */
#define USART_CR1_PEIE      8  /**< Parity Error Interrupt Enable */
#define USART_CR1_PS        9  /**< Parity Selection */
#define USART_CR1_PCE       10 /**< Parity Control Enable */
#define USART_CR1_WAKE      11 /**< Receiver Wake-Up Method */
#define USART_CR1_M         12 /**< Word Length */
#define USART_CR1_UE        13 /**< USART Enable */
#define USART_CR1_OVER8     15 /**< Oversampling Mode */

/** @} USART_CR1_Bit_Positions */

/**
 * @defgroup USART_CR2_Bit_Positions USART_CR2 Bit Position Definitions
 * @brief Bit position definitions for USART_CR2 register.
 * @{
 */
#define USART_CR2_ADD       4  /**< Address of the USART node */
#define USART_CR2_LBDL      5  /**< LIN Break Detection Length */
#define USART_CR2_LBDIE     6  /**< LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL      8  /**< Last Bit Clock pulse */
#define USART_CR2_CPHA      9  /**< Clock Phase */
#define USART_CR2_CPOL      10 /**< Clock Polarity */
#define USART_CR2_CLKEN     11 /**< Clock Enable */
#define USART_CR2_STOP      12 /**< STOP[1:0]: STOP bits */
#define USART_CR2_LINEN     14 /**< LIN mode enable */

/** @} USART_CR2_Bit_Positions */

/**
 * @defgroup USART_CR3_Bit_Positions USART_CR3 Bit Position Definitions
 * @brief Bit position definitions for USART_CR3 register.
 * @{
 */
#define USART_CR3_EIE       0  /**< Error Interrupt Enable */
#define USART_CR3_IREN      1  /**< IrDA mode Enable */
#define USART_CR3_IRLP      2  /**< IrDA Low-Power */
#define USART_CR3_HDSEL     3  /**< Half-Duplex Selection */
#define USART_CR3_NACK      4  /**< Smartcard NACK Enable */
#define USART_CR3_SCEN      5  /**< Smartcard Mode Enable */
#define USART_CR3_DMAR      6  /**< DMA Enable Receiver */
#define USART_CR3_DMAT      7  /**< DMA Enable Transmitter */
#define USART_CR3_RTSE      8  /**< RTS Enable */
#define USART_CR3_CTSE      9  /**< CTS Enable */
#define USART_CR3_CTSIE     10 /**< CTS Interrupt Enable */
#define USART_CR3_ONEBIT    11 /**< One Sample Bit Method Enable */

/** @} USART_CR3_Bit_Positions */

/**
 * @defgroup USART_GTPR_Bit_Positions USART_GTPR Bit Position Definitions
 * @brief Bit position definitions for USART_GTPR register.
 * @{
 */
#define USART_GTPR_PSC  0   /**< USART Prescaler Value */
#define USART_GTPR_GT   8   /**< Guard Time Value */

/** @} USART_GTPR_Bit_Positions */

/** @} USART_Bit_Positions */

/**
 * @defgroup RCC_Bit_Positions RCC Bit Position Definitions
 * @brief Bit position definitions for various registers in the RCC peripheral.
 * @{
 */

/**
 * @defgroup RCC_CR_Bit_Positions RCC_CR Bit Position Definitions
 * @brief Bit position definitions for RCC_CR register.
 * @{
 */
#define RCC_CR_HSION        0  /**< HSI Oscillator Enable */
#define RCC_CR_HSIRDY       1  /**< HSI Oscillator Ready */
#define RCC_CR_HSITRIM      3  /**< HSI Oscillator Trimming */
#define RCC_CR_HSICAL       8  /**< HSI Oscillator Calibration */
#define RCC_CR_HSEON        16 /**< HSE Oscillator Enable */
#define RCC_CR_HSERDY       17 /**< HSE Oscillator Ready */
#define RCC_CR_HSEBYP       18 /**< HSE Oscillator Bypass */
#define RCC_CR_CSSON        19 /**< Clock Security System Enable */
#define RCC_CR_PLLON        24 /**< Main PLL Enable */
#define RCC_CR_PLLRDY       25 /**< Main PLL Ready */
#define RCC_CR_PLLI2SON     26 /**< PLLI2S Enable */
#define RCC_CR_PLLI2SRDY    27 /**< PLLI2S Ready */
#define RCC_CR_PLLSAION     28 /**< PLLSAI Enable */
#define RCC_CR_PLLSAIRDY    29 /**< PLLSAI Ready */
/** @} RCC_CR_Bit_Positions */

/**
 * @defgroup RCC_PLLCFGR_Bit_Positions RCC_PLLCFGR Bit Position Definitions
 * @brief Bit position definitions for RCC_PLLCFGR register.
 * @{
 */
#define RCC_PLLCFGR_PLLM    0  /**< Main PLL Division Factor for PLL VCO */
#define RCC_PLLCFGR_PLLN    6  /**< Main PLL Multiplication Factor for VCO */
#define RCC_PLLCFGR_PLLP    16 /**< Main PLL Division Factor for Main System Clock */
#define RCC_PLLCFGR_PLLSRC  22 /**< Main PLL, PLLI2S, and PLLSAI Entry Clock Source */
#define RCC_PLLCFGR_PLLQ    24 /**< Main PLLQ Division Factor for PLLI2S Clock Output */
/** @} RCC_PLLCFGR_Bit_Positions */

/**
 * @defgroup RCC_CFGR_Bit_Positions RCC_CFGR Bit Position Definitions
 * @brief Bit position definitions for RCC_CFGR register.
 * @{
 */
#define RCC_CFGR_SW         0  /**< System Clock Switch */
#define RCC_CFGR_SWS        2  /**< System Clock Switch Status */
#define RCC_CFGR_HPRE       4  /**< AHB Prescaler */
#define RCC_CFGR_PPRE1      10 /**< APB1 Low-Speed Prescaler (APB1CLK) */
#define RCC_CFGR_PPRE2      13 /**< APB2 High-Speed Prescaler (APB2CLK) */
#define RCC_CFGR_RTCPRE     16 /**< HSE division factor for RTC clock */
#define RCC_CFGR_MCO1       21 /**< Microcontroller Clock Output 1 */
#define RCC_CFGR_I2SSRC     23 /**< I2S APB2 Clock Source Selection */
#define RCC_CFGR_MCO1PRE    24 /**< MCO1 Prescaler */
#define RCC_CFGR_MCO2PRE    27 /**< MCO2 Prescaler */
#define RCC_CFGR_MCO2       30 /**< Microcontroller Clock Output 2 */
/** @} RCC_CFGR_Bit_Positions */

/**
 * @defgroup RCC_CIR_Bit_Positions RCC_CIR Bit Position Definitions
 * @brief Bit position definitions for RCC_CIR register.
 * @{
 */
#define RCC_CIR_LSIRDYF     0  /**< LSI Ready Interrupt flag */
#define RCC_CIR_LSERDYF     1  /**< LSE Ready Interrupt flag */
#define RCC_CIR_HSIRDYF     2  /**< HSI Ready Interrupt flag */
#define RCC_CIR_HSERDYF     3  /**< HSE Ready Interrupt flag */
#define RCC_CIR_PLLRDYF     4  /**< PLL Ready Interrupt flag */
#define RCC_CIR_PLLI2SRDYF  5  /**< PLLI2S Ready Interrupt flag */
#define RCC_CIR_PLLSAIRDYF  6  /**< PLLSAI Ready Interrupt flag */
#define RCC_CIR_CSSF        7  /**< Clock Security System Interrupt flag */
#define RCC_CIR_LSIRDYIE    8  /**< LSI Ready Interrupt Enable */
#define RCC_CIR_LSERDYIE    9  /**< LSE Ready Interrupt Enable */
#define RCC_CIR_HSIRDYIE    10 /**< HSI Ready Interrupt Enable */
#define RCC_CIR_HSERDYIE    11 /**< HSE Ready Interrupt Enable */
#define RCC_CIR_PLLRDYIE    12 /**< PLL Ready Interrupt Enable */
#define RCC_CIR_PLLI2SRDYIE 13 /**< PLLI2S Ready Interrupt Enable */
#define RCC_CIR_PLLSAIRDYIE 14 /**< PLLSAI Ready Interrupt Enable */
#define RCC_CIR_LSIRDYC     16 /**< LSI Ready Interrupt Clear */
#define RCC_CIR_LSERDYC     17 /**< LSE Ready Interrupt Clear */
#define RCC_CIR_HSIRDYC     18 /**< HSI Ready Interrupt Clear */
#define RCC_CIR_HSERDYC     19 /**< HSE Ready Interrupt Clear */
#define RCC_CIR_PLLRDYC     20 /**< PLL Ready Interrupt Clear */
#define RCC_CIR_PLLI2SRDYC  21 /**< PLLI2S Ready Interrupt Clear */
#define RCC_CIR_PLLSAIRDYC  22 /**< PLLSAI Ready Interrupt Clear */
/** @} RCC_CIR_Bit_Positions */

/**
 * @defgroup RCC_AHB1RSTR_Bit_Positions RCC_AHB1RSTR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB1RSTR register.
 * @{
 */
#define RCC_AHB1RSTR_GPIOA       0  /**< GPIOA Reset */
#define RCC_AHB1RSTR_GPIOB       1  /**< GPIOB Reset */
#define RCC_AHB1RSTR_GPIOC       2  /**< GPIOC Reset */
#define RCC_AHB1RSTR_GPIOD       3  /**< GPIOD Reset */
#define RCC_AHB1RSTR_GPIOE       4  /**< GPIOE Reset */
#define RCC_AHB1RSTR_GPIOF       5  /**< GPIOF Reset */
#define RCC_AHB1RSTR_GPIOG       6  /**< GPIOG Reset */
#define RCC_AHB1RSTR_GPIOH       7  /**< GPIOH Reset */
#define RCC_AHB1RSTR_GPIOI       8  /**< GPIOI Reset */
#define RCC_AHB1RSTR_CRC         12 /**< CRC Reset */
#define RCC_AHB1RSTR_DMA1        21 /**< DMA1 Reset */
#define RCC_AHB1RSTR_DMA2        22 /**< DMA2 Reset */
#define RCC_AHB1RSTR_ETHMAC      25 /**< Ethernet MAC Reset */
#define RCC_AHB1RSTR_OTGHS       29 /**< USB OTG HS Reset */
#define RCC_AHB1RSTR_OTGHSULPI   30 /**< USB OTG HS ULPI Reset */
/** @} RCC_AHB1RSTR_Bit_Positions */

/**
 * @defgroup RCC_AHB2RSTR_Bit_Positions RCC_AHB2RSTR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB2RSTR register.
 * @{
 */
#define RCC_AHB2RSTR_DCMI        0  /**< DCMI Reset */
#define RCC_AHB2RSTR_CRYP        4  /**< CRYP Reset */
#define RCC_AHB2RSTR_HASH        5  /**< HASH Reset */
#define RCC_AHB2RSTR_RNG         6  /**< RNG Reset */
#define RCC_AHB2RSTR_OTGFS       7  /**< USB OTG FS Reset */
/** @} RCC_AHB2RSTR_Bit_Positions */

/**
 * @defgroup RCC_AHB3RSTR_Bit_Positions RCC_AHB3RSTR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB3RSTR register.
 * @{
 */
#define RCC_AHB3RSTR_FSMC        0  /**< FSMC Reset */
/** @} RCC_AHB3RSTR_Bit_Positions */

/**
 * @defgroup RCC_APB1RSTR_Bit_Positions RCC_APB1RSTR Bit Position Definitions
 * @brief Bit position definitions for RCC_APB1RSTR register.
 * @{
 */
#define RCC_APB1RSTR_TIM2        0  /**< TIM2 Reset */
#define RCC_APB1RSTR_TIM3        1  /**< TIM3 Reset */
#define RCC_APB1RSTR_TIM4        2  /**< TIM4 Reset */
#define RCC_APB1RSTR_TIM5        3  /**< TIM5 Reset */
#define RCC_APB1RSTR_TIM6        4  /**< TIM6 Reset */
#define RCC_APB1RSTR_TIM7        5  /**< TIM7 Reset */
#define RCC_APB1RSTR_TIM12       6  /**< TIM12 Reset */
#define RCC_APB1RSTR_TIM13       7  /**< TIM13 Reset */
#define RCC_APB1RSTR_TIM14       8  /**< TIM14 Reset */
#define RCC_APB1RSTR_WWDG        11 /**< WWDG Reset */
#define RCC_APB1RSTR_SPI2        14 /**< SPI2 Reset */
#define RCC_APB1RSTR_SPI3        15 /**< SPI3 Reset */
#define RCC_APB1RSTR_USART2      17 /**< USART2 Reset */
#define RCC_APB1RSTR_USART3      18 /**< USART3 Reset */
#define RCC_APB1RSTR_UART4       19 /**< UART4 Reset */
#define RCC_APB1RSTR_UART5       20 /**< UART5 Reset */
#define RCC_APB1RSTR_I2C1        21 /**< I2C1 Reset */
#define RCC_APB1RSTR_I2C2        22 /**< I2C2 Reset */
#define RCC_APB1RSTR_I2C3        23 /**< I2C3 Reset */
#define RCC_APB1RSTR_CAN1        25 /**< CAN1 Reset */
#define RCC_APB1RSTR_CAN2        26 /**< CAN2 Reset */
#define RCC_APB1RSTR_PWR         28 /**< Power Interface Reset */
#define RCC_APB1RSTR_DAC         29 /**< DAC Reset */
#define RCC_APB1RSTR_UART7       30 /**< UART7 Reset */
#define RCC_APB1RSTR_UART8       31 /**< UART8 Reset */
/** @} RCC_APB1RSTR_Bit_Positions */

/**
 * @defgroup RCC_APB2RSTR_Bit_Positions RCC_APB2RSTR Bit Position Definitions
 * @brief Bit position definitions for RCC_APB2RSTR register.
 * @{
 */
#define RCC_APB2RSTR_TIM1        0  /**< TIM1 Reset */
#define RCC_APB2RSTR_TIM8        1  /**< TIM8 Reset */
#define RCC_APB2RSTR_USART1      4  /**< USART1 Reset */
#define RCC_APB2RSTR_USART6      5  /**< USART6 Reset */
#define RCC_APB2RSTR_ADC         8  /**< ADC Reset */
#define RCC_APB2RSTR_SDIO        11 /**< SDIO Reset */
#define RCC_APB2RSTR_SPI1        12 /**< SPI1 Reset */
#define RCC_APB2RSTR_SYSCFG      14 /**< System Configuration Controller Reset */
#define RCC_APB2RSTR_TIM9        16 /**< TIM9 Reset */
#define RCC_APB2RSTR_TIM10       17 /**< TIM10 Reset */
#define RCC_APB2RSTR_TIM11       18 /**< TIM11 Reset */
/** @} RCC_APB2RSTR_Bit_Positions */

/**
 * @defgroup RCC_AHB1LPENR_Bit_Positions RCC_AHB1LPENR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB1LPENR register.
 * @{
 */
#define RCC_AHB1LPENR_GPIOALPEN   0  /**< GPIOA Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOBLPEN   1  /**< GPIOB Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOCLPEN   2  /**< GPIOC Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIODLPEN   3  /**< GPIOD Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOELPEN   4  /**< GPIOE Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOFLPEN   5  /**< GPIOF Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOGLPEN   6  /**< GPIOG Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOHLPEN   7  /**< GPIOH Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_GPIOILPEN   8  /**< GPIOI Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_CRCEN       12 /**< CRC Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_DMA1LPEN    21 /**< DMA1 Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_DMA2LPEN    22 /**< DMA2 Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_ETHMACLPEN  25 /**< Ethernet MAC Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_ETHMACTXLPEN 26 /**< Ethernet MAC Transmit Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_ETHMACRXLPEN 27 /**< Ethernet MAC Receive Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_ETHMACPTPLPEN 28 /**< Ethernet MAC PTP Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_OTGHSLPEN   29 /**< USB OTG HS Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB1LPENR_OTGHSHULPI  30 /**< USB OTG HS ULPI Peripheral Clock in Low Power Mode Enable */
/** @} RCC_AHB1LPENR_Bit_Positions */

/**
 * @defgroup RCC_AHB2LPENR_Bit_Positions RCC_AHB2LPENR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB2LPENR register.
 * @{
 */
#define RCC_AHB2LPENR_DCMILPEN   0  /**< DCMI Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB2LPENR_CRYPLPEN   4  /**< CRYP Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB2LPENR_HASHLPEN   5  /**< HASH Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB2LPENR_RNGLPEN    6  /**< RNG Peripheral Clock in Low Power Mode Enable */
#define RCC_AHB2LPENR_OTGFSLPEN  7  /**< USB OTG FS Peripheral Clock in Low Power Mode Enable */
/** @} RCC_AHB2LPENR_Bit_Positions */

/**
 * @defgroup RCC_AHB3LPENR_Bit_Positions RCC_AHB3LPENR Bit Position Definitions
 * @brief Bit position definitions for RCC_AHB3LPENR register.
 * @{
 */
#define RCC_AHB3LPENR_FSMCLPEN   0  /**< FSMC Peripheral Clock in Low Power Mode Enable */
/** @} RCC_AHB3LPENR_Bit_Positions */

/**
 * @defgroup RCC_APB1LPENR_Bit_Positions RCC_APB1LPENR Bit Position Definitions
 * @brief Bit position definitions for RCC_APB1LPENR register.
 * @{
 */
#define RCC_APB1LPENR_TIM2LPEN   0  /**< TIM2 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM3LPEN   1  /**< TIM3 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM4LPEN   2  /**< TIM4 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM5LPEN   3  /**< TIM5 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM6LPEN   4  /**< TIM6 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM7LPEN   5  /**< TIM7 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM12LPEN  6  /**< TIM12 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM13LPEN  7  /**< TIM13 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_TIM14LPEN  8  /**< TIM14 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_WWDGLPEN   11 /**< WWDG Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_SPI2LPEN   14 /**< SPI2 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_SPI3LPEN   15 /**< SPI3 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_USART2LPEN 17 /**< USART2 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_USART3LPEN 18 /**< USART3 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_UART4LPEN  19 /**< UART4 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_UART5LPEN  20 /**< UART5 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_I2C1LPEN   21 /**< I2C1 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_I2C2LPEN   22 /**< I2C2 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_I2C3LPEN   23 /**< I2C3 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_CAN1LPEN   25 /**< CAN1 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_CAN2LPEN   26 /**< CAN2 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_PWRLPEN    28 /**< Power Interface Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_DACLPEN    29 /**< DAC Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_UART7LPEN  30 /**< UART7 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB1LPENR_UART8LPEN  31 /**< UART8 Peripheral Clock in Low Power Mode Enable */
/** @} RCC_APB1LPENR_Bit_Positions */

/**
 * @defgroup RCC_APB2LPENR_Bit_Positions RCC_APB2LPENR Bit Position Definitions
 * @brief Bit position definitions for RCC_APB2LPENR register.
 * @{
 */
#define RCC_APB2LPENR_TIM1LPEN   0  /**< TIM1 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_TIM8LPEN   1  /**< TIM8 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_USART1LPEN 4  /**< USART1 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_USART6LPEN 5  /**< USART6 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_ADCLPEN    8  /**< ADC Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_SDIOLPEN   11 /**< SDIO Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_SPI1LPEN   12 /**< SPI1 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_SYSCFGLPEN 14 /**< System Configuration Controller Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_TIM9LPEN   16 /**< TIM9 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_TIM10LPEN  17 /**< TIM10 Peripheral Clock in Low Power Mode Enable */
#define RCC_APB2LPENR_TIM11LPEN  18 /**< TIM11 Peripheral Clock in Low Power Mode Enable */
/** @} RCC_APB2LPENR_Bit_Positions */

/**
 * @defgroup RCC_BDCR_Bit_Positions RCC_BDCR Bit Position Definitions
 * @brief Bit position definitions for RCC_BDCR register.
 * @{
 */
#define RCC_BDCR_LSEON     0  /**< External Low-Speed Oscillator Enable */
#define RCC_BDCR_LSERDY    1  /**< External Low-Speed Oscillator Ready */
#define RCC_BDCR_LSEBYP    2  /**< External Low-Speed Oscillator Bypass */
#define RCC_BDCR_RTCSEL    8  /**< RTC Clock Source Selection */
#define RCC_BDCR_RTCEN     15 /**< RTC Clock Enable */
#define RCC_BDCR_BDRST     16 /**< Backup Domain Software Reset */
/** @} RCC_BDCR_Bit_Positions */

/**
 * @defgroup RCC_CSR_Bit_Positions RCC_CSR Bit Position Definitions
 * @brief Bit position definitions for RCC_CSR register.
 * @{
 */
#define RCC_CSR_LSION      0  /**< Internal Low-Speed Oscillator Enable */
#define RCC_CSR_LSIRDY     1  /**< Internal Low-Speed Oscillator Ready */
#define RCC_CSR_RMVF       24 /**< Remove Reset Flag */
#define RCC_CSR_OBLRSTF    25 /**< Option Byte Loader Reset Flag */
#define RCC_CSR_PINRSTF    26 /**< PIN Reset Flag */
#define RCC_CSR_PORRSTF    27 /**< POR/PDR Reset Flag */
#define RCC_CSR_SFTRSTF    28 /**< Software Reset Flag */
#define RCC_CSR_IWDGRSTF   29 /**< Independent Watchdog Reset Flag */
#define RCC_CSR_WWDGRSTF   30 /**< Window Watchdog Reset Flag */
#define RCC_CSR_LPWRRSTF   31 /**< Low-Power Reset Flag */
/** @} RCC_CSR_Bit_Positions */

/**
 * @defgroup RCC_SSCGR_Bit_Positions RCC_SSCGR Bit Position Definitions
 * @brief Bit position definitions for RCC_SSCGR register.
 * @{
 */
#define RCC_SSCGR_MODPER    0  /**< Modulation Period */
#define RCC_SSCGR_INCSTEP   13 /**< Increase Step */
#define RCC_SSCGR_SPREADSEL 15 /**< Spread Select */
#define RCC_SSCGR_SSCGEN    31 /**< Spread Spectrum Clock Generation Enable */
/** @} RCC_SSCGR_Bit_Positions */

/**
 * @defgroup RCC_PLLI2SCFGR_Bit_Positions RCC_PLLI2SCFGR Bit Position Definitions
 * @brief Bit position definitions for RCC_PLLI2SCFGR register.
 * @{
 */
#define RCC_PLLI2SCFGR_PLLI2SN  6  /**< PLLI2S N Factor */
#define RCC_PLLI2SCFGR_PLLI2SR  28 /**< PLLI2S R Factor */
/** @} RCC_PLLI2SCFGR_Bit_Positions */

/** @} RCC_Bit_Positions */


/********************************** END : Bit position definitions Macros ***************************************************/

/**
 * @defgroup Generic_Macros Generic Macros
 * @{
 * @brief Generic macros for enabling/disabling, setting/resetting, and handling flags.
 */
#define ENABLE          1           /**< Enable macro */
#define DISABLE         0           /**< Disable macro */
#define SET             ENABLE      /**< Set macro */
#define RESET           DISABLE     /**< Reset macro */
#define GPIO_PIN_SET    SET         /**< GPIO Pin set macro */
#define GPIO_PIN_RESET  RESET       /**< GPIO Pin reset macro */
#define FLAG_SET        SET         /**< Flag set macro */
#define FLAG_RESET      RESET       /**< Flag reset macro */
/** @} Generic_Macros */

#include "stm32f407xx_gpio_driver.h" /**< Include GPIO driver header file */
#include "stm32f407xx_rcc_driver.h"  /**< Include RCC driver header file */
#include "stm32f407xx_i2c_driver.h"  /**< Include I2C driver header file */
#include "stm32f407xx_spi_driver.h"  /**< Include SPI driver header file */
#include "stm32f407xx_usart_driver.h"  /**< Include UART driver header file */

/** @} STM32F407XX_HEADER*/

#endif /* INC_STM32F407XX_H_ */










