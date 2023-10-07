/**
 * @file stm32f407xx_gpio_driver.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains the GPIO driver API declarations for the STM32F407xx MCU.
 * @version 0.1
 * @date 2023-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// The peripheral specific headerfile 

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

/**
 * @defgroup GPIO_Driver GPIO Driver
 * @brief GPIO driver APIs for STM32F407xx MCU.
 * @{
 */

/**
 * @brief Configuration structure for GPIO pin.
 */
typedef struct
{
    uint32_t GPIO_PinNumber;        /*!< Specifies the GPIO pin number. */
    uint32_t GPIO_PinMode;          /*!< Specifies the mode of the GPIO pin. */
    uint32_t GPIO_PinSpeed;         /*!< Specifies the speed of the GPIO pin. */
    uint32_t GPIO_PinPuPdControl;   /*!< Specifies the pull-up/pull-down configuration for the GPIO pin. */
    uint32_t GPIO_PinPinOPType;     /*!< Specifies the output type of the GPIO pin. */
    uint32_t GPIO_PinAltFunMode;    /*!< Specifies the alternate function mode of the GPIO pin. */
} GPIO_PinConfig_t;

/**
 * @brief Handle structure for GPIO pin.
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;       /*!< Holds the base address of the GPIO port to which the pin belongs. */
    GPIO_PinConfig_t GPIO_PinConfig; /*!< Holds GPIO pin configuration settings. */
} GPIO_Handle_t;

/**
 * @defgroup GPIO_MACROS GPIO Macros
 * @brief Macros for GPIO configuration and settings.
 * @{
 */

/**
 * @defgroup GPIO_PIN_NUMBERS GPIO Pin Numbers
 * @brief Possible GPIO pin numbers.
 * @{
 */
#define GPIO_PIN_NO_0    0
#define GPIO_PIN_NO_1    1
#define GPIO_PIN_NO_2    2
#define GPIO_PIN_NO_3    3
#define GPIO_PIN_NO_4    4
#define GPIO_PIN_NO_5    5
#define GPIO_PIN_NO_6    6
#define GPIO_PIN_NO_7    7
#define GPIO_PIN_NO_8    8
#define GPIO_PIN_NO_9    9
#define GPIO_PIN_NO_10   10
#define GPIO_PIN_NO_11   11
#define GPIO_PIN_NO_12   12
#define GPIO_PIN_NO_13   13
#define GPIO_PIN_NO_14   14
#define GPIO_PIN_NO_15   15
/** @} */

/**
 * @defgroup GPIO_PIN_MODES GPIO Pin Modes
 * @brief Possible GPIO pin modes.
 * @{
 */
#define GPIO_MODE_IN          0 /*!< GPIO Input mode. */
#define GPIO_MODE_OUT         1 /*!< GPIO Output mode. */
#define GPIO_MODE_ALTFN       2 /*!< GPIO Alternate Function mode. */
#define GPIO_MODE_ANALOG      3 /*!< GPIO Analog mode. */
#define GPIO_MODE_IT_FT       4 /*!< GPIO Interrupt Falling-Edge Trigger mode. */
#define GPIO_MODE_IT_RT       5 /*!< GPIO Interrupt Rising-Edge Trigger mode. */
#define GPIO_MODE_IT_RFT      6 /*!< GPIO Interrupt Rising-Falling Edge Trigger mode. */
/** @} */

/**
 * @defgroup GPIO_SPEEDS GPIO Output Speeds
 * @brief Possible GPIO pin output speeds.
 * @{
 */
#define GPIO_SPEED_LOW        0 /*!< GPIO Output speed Low. */
#define GPIO_SPEED_MEDIUM     1 /*!< GPIO Output speed Medium. */
#define GPIO_SPEED_FAST       2 /*!< GPIO Output speed Fast. */
#define GPIO_SPEED_HIGH       3 /*!< GPIO Output speed High. */
/** @} */

/**
 * @defgroup GPIO_PUPD GPIO Pull-up/Pull-down Configurations
 * @brief Possible GPIO pin pull-up and pull-down configurations.
 * @{
 */
#define GPIO_NO_PUPD          0 /*!< No pull-up/pull-down configuration. */
#define GPIO_PIN_PU           1 /*!< GPIO Pull-up configuration. */
#define GPIO_PIN_PD           2 /*!< GPIO Pull-down configuration. */
/** @} */

/**
 * @defgroup GPIO_OUTPUT_TYPES GPIO Output Types
 * @brief Possible GPIO pin output types.
 * @{
 */
#define GPIO_OP_TYPE_PP       0 /*!< GPIO Output type Push-Pull mode. */
#define GPIO_OP_TYPE_OD       1 /*!< GPIO Output type Open-Drain mode. */
/** @} */

/** @} */ // End of GPIO Macros group

/**
 * @defgroup GPIO_APIS GPIO APIs
 * @brief APIs supported by the GPIO driver.
 * @{
 */

/**
 * @brief Enables or disables the peripheral clock for the GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @param EnorDi ENABLE to enable clock, DISABLE to disable clock.
 */
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/**
 * @brief Initializes the GPIO port pin according to the configuration.
 *
 * @param pGPIOHandle Pointer to the GPIO handle structure.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

/**
 * @brief Deinitializes the GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/**
 * @brief Reads a value from a specific GPIO pin.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @param PinNumber GPIO pin number.
 * @return uint8_t 1 if the pin is set, 0 if the pin is reset.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/**
 * @brief Reads a value from the entire GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @return uint16_t Content of the input data register.
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

/**
 * @brief Writes a value to a specific GPIO pin.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @param PinNumber GPIO pin number.
 * @param value Value to write (1 or 0).
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t value);

/**
 * @brief Writes a value to the entire GPIO port.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @param value Value to write.
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);

/**
 * @brief Toggles the output value of a specific GPIO pin.
 *
 * @param pGPIOx Pointer to the GPIO peripheral.
 * @param PinNumber GPIO pin number.
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber);

/**
 * @brief Configures the IRQ for a specific GPIO pin.
 *
 * @param IRQNumber IRQ number.
 * @param EnorDi ENABLE to enable IRQ, DISABLE to disable IRQ.
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);

/**
 * @brief Configures the priority for a specific IRQ.
 *
 * @param IRQNumber IRQ number.
 * @param IRQpriority Priority value.
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQpriority);

/**
 * @brief Handles the IRQ for a specific GPIO pin.
 *
 * @param PinNumber GPIO pin number.
 */
void GPIO_IRQHandling(uint16_t PinNumber);

/** @} */

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
