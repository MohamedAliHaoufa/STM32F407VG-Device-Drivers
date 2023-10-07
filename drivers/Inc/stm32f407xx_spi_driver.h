/**
 * @file stm32f407xx_spi_driver.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and functions prototypes for the STM32F407xx SPI driver.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"
/**
 * @defgroup SPI_Driver SPI Driver
 * @brief SPI driver APIs for STM32F407xx MCU.
 * @{
 */

/**
 * @struct SPI_Config_t
 * @brief Configuration structure for SPI peripheral.
 */
typedef struct
{
    uint8_t SPI_DeviceMode; /**< SPI device mode (Master/Slave). */
    uint8_t SPI_BusConfig;  /**< SPI bus configuration (Full-duplex/Half-duplex/...). */
    uint8_t SPI_SclkSpeed;  /**< SPI serial clock speed (Prescaler selection). */
    uint8_t SPI_DFF;        /**< SPI data frame format (8/16-bit data frame). */
    uint8_t SPI_CPOL;       /**< SPI clock polarity (Idle state polarity). */
    uint8_t SPI_CPHA;       /**< SPI clock phase (Data capture on rising/falling edge). */
    uint8_t SPI_SSM;        /**< SPI software slave management (Enable/Disable). */
} SPI_Config_t;


/**
 * @struct SPI_Handle_t
 * @brief Handle structure for SPI peripheral.
 */
typedef struct
{
    SPI_RegDef_t *pSPIx;    /**< Pointer to the SPI peripheral's base address. */
    SPI_Config_t SPI_Config; /**< SPI configuration structure. */
    uint8_t *pTxBuffer;     /**< Pointer to the transmit buffer. */
    uint8_t *pRxBuffer;     /**< Pointer to the receive buffer. */
    uint32_t TxLen;         /**< Length of data to be transmitted. */
    uint32_t RxLen;         /**< Length of data to be received. */
    uint8_t TxState;        /**< Transmit state (used for interrupt-driven transmission). */
    uint8_t RxState;        /**< Receive state (used for interrupt-driven reception). */
} SPI_Handle_t;

/**
 * @defgroup SPI_APIS SPI APIs
 * @brief APIs supported by the SPI driver.
 * @{
 */

/**
 * @brief Enables or disables the peripheral clock for the SPI port.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param EnorDi ENABLE to enable clock, DISABLE to disable clock.
 */
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/**
 * @brief Enables or disables the SPI peripheral.
 *
 * This function allows you to enable or disable the SPI peripheral. When enabled, the SPI port can send and receive data. When disabled, the SPI port is inactive and cannot send or receive data.
 *
 * @param pSPIx Pointer to the SPI peripheral's register structure.
 * @param EnorDi ENABLE to enable the SPI peripheral, DISABLE to disable it.
 *
 * @note Disabling the SPI peripheral will halt ongoing SPI transactions.
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/**
 * @brief Initializes the SPI port pin according to the configuration.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);

/**
 * @brief Deinitializes the SPI port.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/**
 * @brief Get the status of a specific SPI flag.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param FlagName Flag to check (e.g., SPI_TXE_FLAG, SPI_RXNE_FLAG).
 *
 * @return FLAG_SET if the flag is set, FLAG_RESET if not.
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t FlagName);

/**
 * @brief Sends data over SPI.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param pTxBuffer Pointer to the transmit buffer.
 * @param Len Length of data to be sent.
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

/**
 * @brief Receives data over SPI.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param pRxBuffer Pointer to the receive buffer.
 * @param Len Length of data to be received.
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);


/**
 * @brief Sends data over SPI using interrupt-driven communication.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * @param pTxBuffer Pointer to the transmit buffer.
 * @param Len Length of data to be sent.
 *
 * @note This function sets up and initiates the transmission of data over SPI using interrupts.
 *       The data transmission will be handled asynchronously, and the user should implement
 *       the necessary interrupt handler to process data when the transmission is complete.
 *
 * @return
 *   - @ref SPI_READY: If the SPI is ready for communication and the data transmission is successfully initiated.
 *   - @ref SPI_BUSY_IN_TX: If a previous transmission is still ongoing.
 *   - @ref SPI_ERROR_INVALID_ARG: If the input parameters are invalid.
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);

/**
 * @brief Receives data over SPI using interrupt-driven communication.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * @param pRxBuffer Pointer to the receive buffer.
 * @param Len Length of data to be received.
 *
 * @note This function sets up and initiates the reception of data over SPI using interrupts.
 *       The data reception will be handled asynchronously, and the user should implement
 *       the necessary interrupt handler to process received data.
 *
 * @return
 *   - @ref SPI_READY: If the SPI is ready for communication and the data reception is successfully initiated.
 *   - @ref SPI_BUSY_IN_RX: If a previous reception is still ongoing.
 *   - @ref SPI_ERROR_INVALID_ARG: If the input parameters are invalid.
 */
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);


/**
 * @brief Configures the IRQ for a specific SPI pin.
 *
 * @param IRQNumber IRQ number.
 * @param EnorDi ENABLE to enable IRQ, DISABLE to disable IRQ.
 */
void SPI_IRQinterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);

/**
 * @brief Configures the priority for a specific IRQ.
 *
 * @param IRQNumber IRQ number.
 * @param IRQpriority Priority value.
 */
void SPI_IRQperiorityConfig(uint8_t IRQNumber, uint32_t IRQpriority);

/**
 * @brief Handles the IRQ for a specific SPI pin.
 *
 * @param PinNumber SPI pin number.
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/**
 * @brief Enables or disables the Software Slave Management (SSI) configuration for the SPI peripheral.
 *
 * @param pSPIx   Pointer to the SPI peripheral.
 * @param EnorDi  ENABLE to enable SSI, DISABLE to disable SSI.
 *
 * @note SSI is used to control the slave select (NSS) pin in software. Enabling SSI ensures that the NSS pin
 *       remains high, even when the SPI is configured as a master. Disabling SSI allows the NSS pin to be
 *       controlled by the hardware or pulled to low, as specified in the SPI configuration.
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/**
 * @brief Enables or disables the SPI Slave Select Output Enable (SSOE) configuration for the SPI peripheral.
 *
 * @param pSPIx   Pointer to the SPI peripheral.
 * @param EnorDi  ENABLE to enable SSOE, DISABLE to disable SSOE.
 *
 * @note SSOE is used to configure the behavior of the NSS pin when the SPI is configured as a master. When SSOE is enabled,
 *       NSS pin output is automatically managed (driven low or high) by the hardware based on the SPI state. When SSOE is
 *       disabled, NSS pin is under software control, and you must use the SPI_SSIConfig function to manage it.
 */
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/**
 * @brief Clears the overrun error (OVR) flag in the SPI peripheral.
 *
 * This function clears the overrun error flag in the status register of the SPI peripheral.
 * Overrun errors occur when new data is received before the previous data is read, causing
 * data loss.
 *
 * @param pSPIx Pointer to the SPI peripheral for which the overrun error flag should be cleared.
 */
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);

/**
 * @brief Closes the transmission operation on the SPI peripheral.
 *
 * This function is used to close the transmission operation on the SPI peripheral after
 * all the data has been transmitted. It disables the transmit buffer empty interrupt and
 * sets the transmission state to idle.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);

/**
 * @brief Closes the reception operation on the SPI peripheral.
 *
 * This function is used to close the reception operation on the SPI peripheral after
 * all the data has been received. It disables the receive buffer not empty interrupt and
 * sets the reception state to idle.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/**
 * @brief SPI Application Event Callback.
 *
 * This function serves as a callback that can be overridden by the application to handle
 * SPI-related events. It is called when specific events occur during SPI communication
 * and allows the application to take custom actions.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * @param AppEv The SPI application event that occurred (e.g., transmission complete, reception complete).
 *
 * @note This is a weak implementation, and the application can override this function to provide
 *       custom event handling.
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);

/** @} */

/**
 * @defgroup SPI_Macros SPI Macros
 * @brief Macros related to SPI configuration, flags, and events.
 * @{
 */

/**
 * @defgroup SPI_Application_States SPI Application States
 * @brief Possible states of the SPI application.
 * @{
 */
#define SPI_DEVICE_MODE_MASTER   1 /**< SPI device mode: Master */
#define SPI_DEVICE_MODE_SLAVE    0 /**< SPI device mode: Slave */
/** @} */

/**
 * @defgroup SPI_ACK_Control_Options SPI ACK Control Options
 * @brief Options for controlling the ACK mechanism in SPI communication.
 * @{
 */
#define SPI_BUS_CONFIG_FULL_DUPLEX        1 /**< Full-duplex communication */
#define SPI_BUS_CONFIG_HALF_DUPLEX        2 /**< Half-duplex communication */
#define SPI_BUS_CONFIG_SIMPLEX_RX_ONLY    3 /**< Simplex reception-only mode */
//#define SPI_BUS_CONFIG_SIMPLEX_TX_ONLY    4 /**< Simplex transmission-only mode - just disconnect the MISO line */

/** @} */

/**
 * @defgroup SPI_SCLK_Speed_Options SPI Serial Clock Speed Options
 * @brief Options for SPI serial clock speed.
 * @{
 */
#define SPI_SCLK_SPEED_DIV2     0 /**< Serial clock speed: Fpclk / 2 */
#define SPI_SCLK_SPEED_DIV4     1 /**< Serial clock speed: Fpclk / 4 */
#define SPI_SCLK_SPEED_DIV8     2 /**< Serial clock speed: Fpclk / 8 */
#define SPI_SCLK_SPEED_DIV16    3 /**< Serial clock speed: Fpclk / 16 */
#define SPI_SCLK_SPEED_DIV32    4 /**< Serial clock speed: Fpclk / 32 */
#define SPI_SCLK_SPEED_DIV64    5 /**< Serial clock speed: Fpclk / 64 */
#define SPI_SCLK_SPEED_DIV128   6 /**< Serial clock speed: Fpclk / 128 */
#define SPI_SCLK_SPEED_DIV256   7 /**< Serial clock speed: Fpclk / 256 */
/** @} */

/**
 * @defgroup SPI_Data_Frame_Format_Options SPI Data Frame Format Options
 * @brief Options for SPI data frame format.
 * @{
 */
#define SPI_DFF_8BITS   0 /**< Data frame format: 8 bits per frame */
#define SPI_DFF_16BITS  1 /**< Data frame format: 16 bits per frame */
/** @} */

/**
 * @defgroup SPI_CPOL_Options SPI Clock Polarity Options
 * @brief Options for SPI clock polarity.
 * @{
 */
#define SPI_CPOL_HIGH   1 /**< Clock polarity: High when idle */
#define SPI_CPOL_LOW    0 /**< Clock polarity: Low when idle */
/** @} */

/**
 * @defgroup SPI_CPHA_Options SPI Clock Phase Options
 * @brief Options for SPI clock phase.
 * @{
 */
#define SPI_CPHA_HIGH   1 /**< Clock phase: Data sampled on the second edge */
#define SPI_CPHA_LOW    0 /**< Clock phase: Data sampled on the first edge */
/** @} */

/**
 * @defgroup SPI_SSM_Options SPI Slave Select Management Options
 * @brief Options for SPI slave select management.
 * @{
 */
#define SPI_SSM_EN  1 /**< Slave select management: Enable (Software controlled) */
#define SPI_SSM_DI  0 /**< Slave select management: Disable (Hardware controlled) */
/** @} */

/**
 * @brief SPI Status Flags
 *
 * @defgroup SPI_FLAG_Status SPI Status Flags
 * @brief Defines flags for SPI status.
 * @{
 */

#define SPI_RXNE_FLAG  	(1 << SPI_SR_RXNE)   /**< Receive buffer not empty flag */
#define SPI_TXE_FLAG   	(1 << SPI_SR_TXE)    /**< Transmit buffer empty flag */
#define SPI_CHSIDE_FLAG (1 << SPI_SR_CHSIDE) /**< Channel side flag */
#define SPI_UDR_FLAG   	(1 << SPI_SR_UDR)    /**< Underrun flag */
#define SPI_CRCERR_FLAG (1 << SPI_SR_CRCERR) /**< CRC error flag */
#define SPI_MODF_FLAG  	(1 << SPI_SR_MODF)   /**< Mode fault flag */
#define SPI_OVR_FLAG   	(1 << SPI_SR_OVR)    /**< Overrun flag */
#define SPI_BUSY_FLAG   (1 << SPI_SR_BSY)    /**< Busy flag */
#define SPI_FRE_FLAG   	(1 << SPI_SR_FRE)    /**< Frame format error flag */
/** @} */

/**
 * @defgroup SPI_Application_States SPI Application States
 * @brief Defines possible states of the SPI application.
 * @{
 */

#define SPI_READY      0   /**< SPI is ready for communication */
#define SPI_BUSY_IN_RX 1   /**< SPI is busy receiving data */
#define SPI_BUSY_IN_TX 2   /**< SPI is busy transmitting data */
/** @} */

/**
 * @defgroup SPI_Application_Events SPI Application Events
 * @brief Defines possible events that can occur in the SPI application.
 * @{
 */

#define SPI_EVENT_TX_CMPLT  1 /**< Event indicating the completion of a transmit operation. */
#define SPI_EVENT_RX_CMPLT  2 /**< Event indicating the completion of a receive operation. */
#define SPI_EVENT_OVR_ERR   3 /**< Event indicating an overrun error during SPI communication. */
#define SPI_EVENT_CRC_ERR   4 /**< Event indicating a CRC (Cyclic Redundancy Check) error in SPI communication. */
/** @} */


/**
 * @defgroup SPI SPI Communication CMDs
 * @brief Defines a set of COMMANDs for SPI communication.
 * @{
 */

#define CMD_LED_CTRL    0x50 /**< CMD to control an LED. */
#define CMD_SENSOR_READ 0x51 /**< CMD to read a sensor. */
#define CMD_LED_READ    0x52 /**< CMD to read the LED state. */
#define CMD_PRINT       0x53 /**< CMD to print data. */
#define CMD_ID_READ     0x54 /**< CMD to read an ID. */
/** @} */

/**
 * @defgroup LED_Control LED Control Macros
 * @brief Defines macros for controlling LEDs, including the LED state and pin number.
 * @{
 */

#define LED_ON   1 /**< Represents the LED ON state. */
#define LED_OFF  0 /**< Represents the LED OFF state. */
#define LED_PIN  9 /**< Represents the Arduino LED pin number. */
/** @} */


/**
 * @defgroup Analog_Pins Arduino Analog Pins
 * @brief Defines a set of macros representing Arduino analog pins.
 * @{
 */

#define ANALOG_PIN0 0 /**< Represents analog pin 0. */
#define ANALOG_PIN1 1 /**< Represents analog pin 1. */
#define ANALOG_PIN2 2 /**< Represents analog pin 2. */
#define ANALOG_PIN3 3 /**< Represents analog pin 3. */
#define ANALOG_PIN4 4 /**< Represents analog pin 4. */
/** @} */



/** @} */ // End of SPI_Macros group

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
