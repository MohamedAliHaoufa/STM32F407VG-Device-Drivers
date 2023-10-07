/**
 * @file stm32f407xx_usart_driver.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and functions prototypes for the STM32F407xx USART driver.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef INC_STM32F407XX_USART_DRIVER_H_
#define INC_STM32F407XX_USART_DRIVER_H_

#include "stm32f407xx.h"

/**
 * @defgroup USART_Driver USART Driver
 * @brief USART driver APIs for STM32F407xx MCU.
 * @{
 */

/**
 * @struct USART_Config_t
 * @brief Configuration structure for USART (Universal Synchronous Asynchronous Receiver Transmitter) peripheral.
 */
typedef struct
{
    uint8_t USART_Mode;             /**< Specifies the USART operating mode (e.g., transmit, receive, or both). */
    uint8_t USART_Baud;             /**< Specifies the baud rate for serial communication. */
    uint8_t USART_NoOfStopBits;     /**< Specifies the number of stop bits to use in each frame. */
    uint8_t USART_WordLength;       /**< Specifies the word length (number of data bits) for each frame. */
    uint8_t USART_ParityControl;    /**< Specifies the parity control mode for error checking. */
    uint8_t USART_HWFlowControl;    /**< Specifies the hardware flow control mode, if applicable. */
} USART_Config_t;


/**
 * @struct USART_Handle_t
 * @brief Handle structure for USART peripheral.
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;     /**< Pointer to the USART peripheral's base address. */
    USART_Config_t USART_Config; /**< USART configuration structure. */
    uint8_t *pTxBuffer;     	 /**< Pointer to the transmit buffer. */
    uint8_t *pRxBuffer;    		 /**< Pointer to the receive buffer. */
    uint32_t TxLen;        		 /**< Length of data to be transmitted. */
    uint32_t RxLen;      	     /**< Length of data to be received. */
    uint8_t TxBusyState;         /**< Transmitter state: BUSY (1) or IDLE (0). */
    uint8_t RxBusyState;         /**< Receiver state: BUSY (1) or IDLE (0). */
} USART_Handle_t;



/**
 * @defgroup USART_APIS USART APIs
 * @brief USART driver APIs for STM32F407xx MCU.
 * @{
 */

/**
 * @brief Enable or disable the peripheral clock for the given USARTx.
 *
 * @param pUSARTx Pointer to the USART peripheral.
 * @param EnorDi  ENABLE or DISABLE the clock.
 */
void USART_PeripheralClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/**
 * @brief Set the baud rate for a USART peripheral.
 *
 * This function calculates and sets the baud rate for a USART peripheral based on
 * the provided baud rate and the system's APB clock frequency.
 *
 * @param pUSARTx       Pointer to the USART peripheral.
 * @param BaudRate      Desired baud rate (in bits per second).
 *
 * @note The function assumes that the USART is already initialized and configured.
 *
 * @warning This function may not work as expected if the USART peripheral is not
 *          properly configured.
 *
 * @return None
 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

/**
 * @brief Initialize the USART peripheral.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_Init(USART_Handle_t *pUSARTHandle);

/**
 * @brief Deinitialize the USART peripheral.
 *
 * @param pUSARTx Pointer to the USART peripheral.
 */
void USART_DeInit(USART_RegDef_t *pUSARTx);


/**
 * @brief Send data over USART.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pTxBuffer   Pointer to the transmit buffer.
 * @param Len         Length of data to be sent.
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);

/**
 * @brief Receive data from USART.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pRxBuffer   Pointer to the receive buffer.
 * @param Len         Length of data to be received.
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);


/**
 * @brief Send data over USART using interrupt-driven communication.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pTxBuffer    Pointer to the transmit buffer.
 * @param Len          Length of data to be sent.
 * @return uint8_t     Transmission status.
 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);

/**
 * @brief Receive data from USART using interrupt-driven communication.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pRxBuffer    Pointer to the receive buffer.
 * @param Len          Length of data to be received.
 * @return uint8_t     Reception status.
 */
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);


/**
 * @brief Control the USART peripheral (ENABLE/DISABLE).
 *
 * @param pUSARTx Pointer to the USART peripheral.
 * @param EnorDi  ENABLE or DISABLE the peripheral.
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/**
 * @brief Get the status of a specific USART flag.
 *
 * @param pUSARTx   Pointer to the USART peripheral.
 * @param FlagName  Name of the flag to check.
 * @return uint8_t  Status of the flag (FLAG_SET or FLAG_RESET).
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t FlagName);

/**
 * @brief Clear a specific USART flag.
 *
 * @param pUSARTx   Pointer to the USART peripheral.
 * @param FlagName  Name of the flag to clear.
 */
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t FlagName);

/**
 * @brief Close USART transmission.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_CloseTransmission(USART_Handle_t *pUSARTHandle);

/**
 * @brief Close USART reception.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_CloseReception(USART_Handle_t *pUSARTHandle);

/**
 * @brief Configure IRQ number and enable/disable IRQ.
 *
 * @param IRQNumber IRQ number to configure.
 * @param EnorDi    ENABLE or DISABLE IRQ.
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);

/**
 * @brief Set the priority of an IRQ.
 *
 * @param IRQNumber     IRQ number to set priority for.
 * @param IRQPriority   Priority to be set.
 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Handle USART interrupts.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

/**
 * @brief Application callback function for USART events.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param AppEv        USART application event.
 */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv);

/**
 * @brief Clears the error flags in the USART status register.
 *
 * This function clears any error flags that may have been set in the USART status
 * register (SR). It is commonly used to clear error flags before resuming USART
 * communication after an error condition.
 *
 * @param pUSARTx Pointer to the USART peripheral.
 *
 *
 * @warning Do not call this function during active USART communication, as it
 * may cause data loss.
 */
void USART_ClearEventErrFlag(USART_RegDef_t *pUSARTx);

/** @} */

/**
 * @defgroup USART_Macros USART Macros
 * @brief Macros related to USART configuration, flags, and events.
 * @{
 */


/**
 * @defgroup USART_Mode USART Transmission Modes
 * @brief Possible options for USART transmission mode.
 * @{
 */
#define USART_MODE_ONLY_TX 0 /**< Only transmit mode. */
#define USART_MODE_ONLY_RX 1 /**< Only receive mode. */
#define USART_MODE_TXRX     2 /**< Transmit and receive mode. */
/** @} */

/**
 * @defgroup USART_Baud USART Baud Rates
 * @brief Possible options for USART baud rates.
 * @{
 */
#define USART_STD_BAUD_1200     (uint8_t)1200
#define USART_STD_BAUD_2400     (uint8_t)2400
#define USART_STD_BAUD_9600     (uint8_t)9600
#define USART_STD_BAUD_19200    (uint8_t)19200
#define USART_STD_BAUD_38400    (uint8_t)38400
#define USART_STD_BAUD_57600    (uint8_t)57600
#define USART_STD_BAUD_115200   (uint8_t)115200
#define USART_STD_BAUD_230400   (uint8_t)230400
#define USART_STD_BAUD_460800   (uint8_t)460800
#define USART_STD_BAUD_921600   (uint8_t)921600
#define USART_STD_BAUD_2M       (uint8_t)2000000
#define USART_STD_BAUD_3M       (uint8_t)3000000
/** @} */

/**
 * @defgroup USART_ParityControl USART Parity Control
 * @brief Possible options for USART parity control.
 * @{
 */
#define USART_PARITY_EN_ODD     2 /**< Enable USART parity control with odd parity. */
#define USART_PARITY_EN_EVEN    1 /**< Enable USART parity control with even parity. */
#define USART_PARITY_DISABLE    0 /**< Disable USART parity control. */
/** @} */

/**
 * @defgroup USART_WordLength USART Word Lengths
 * @brief Possible options for USART word length.
 * @{
 */
#define USART_WORDLEN_8BITS  0 /**< 8-bit data word length. */
#define USART_WORDLEN_9BITS  1 /**< 9-bit data word length. */
/** @} */

/**
 * @defgroup USART_NoOfStopBits USART Stop Bits
 * @brief Possible options for USART stop bits.
 * @{
 */
#define USART_STOPBITS_1     0 /**< 1 stop bit. */
#define USART_STOPBITS_0_5   1 /**< 0.5 stop bits. */
#define USART_STOPBITS_2     2 /**< 2 stop bits. */
#define USART_STOPBITS_1_5   3 /**< 1.5 stop bits. */
/** @} */

/**
 * @defgroup USART_HWFlowControl USART Hardware Flow Control
 * @brief Possible options for USART hardware flow control.
 * @{
 */
#define USART_HW_FLOW_CTRL_NONE     0 /**< No hardware flow control. */
#define USART_HW_FLOW_CTRL_CTS      1 /**< Hardware flow control using CTS (Clear To Send). */
#define USART_HW_FLOW_CTRL_RTS      2 /**< Hardware flow control using RTS (Request To Send). */
#define USART_HW_FLOW_CTRL_CTS_RTS  3 /**< Hardware flow control using both CTS and RTS. */
/** @} */

/**
 * @brief USART Status Flags
 *
 * @defgroup USART_FLAG_Status USART Status Flags
 * @brief Defines flags for USART status.
 * @{
 */
#define USART_FLAG_PE     (1 << USART_SR_PE)    /**< USART Parity error flag */
#define USART_FLAG_FE     (1 << USART_SR_FE)    /**< USART Framing error flag */
#define USART_FLAG_NE     (1 << USART_SR_NE)    /**< USART Noise error flag */
#define USART_FLAG_ORE    (1 << USART_SR_ORE)   /**< USART Overrun error flag */
#define USART_FLAG_IDLE   (1 << USART_SR_IDLE)  /**< USART Idle line detected flag */
#define USART_FLAG_RXNE   (1 << USART_SR_RXNE)  /**< USART Receive buffer not empty flag */
#define USART_FLAG_TC     (1 << USART_SR_TC)    /**< USART Transmission complete flag */
#define USART_FLAG_TXE    (1 << USART_SR_TXE)   /**< USART Transmit buffer empty flag */
/** @} */

/**
 * @defgroup USART_Application_States USART Application States
 * @brief Defines possible states of the USART application.
 * @{
 */
#define USART_READY      0   /**< USART is ready for communication */
#define USART_BUSY_IN_RX 1   /**< USART is busy receiving data */
#define USART_BUSY_IN_TX 2   /**< USART is busy transmitting data */
/** @} */

/**
 * @defgroup USART_Application_Events USART Application Events
 * @brief Defines possible events that can occur in the USART application.
 * @{
 */
#define 	USART_EVENT_TX_CMPLT   0 /**< Interrupt Event indicating the completion of a transmit operation. */
#define		USART_EVENT_RX_CMPLT   1 /**< Interrupt Event indicating the completion of a receive operation. */
#define		USART_EVENT_IDLE       2 /**< Interrupt Event indicating an idle line detection during USART communication. */
#define		USART_EVENT_CTS        3 /**< Interrupt Event indicating a change in CTS (Clear To Send) signal during USART communication. */
#define		USART_EVENT_PE         4 /**< Interrupt Event indicating a parity error during USART communication. */
#define		USART_ERR_FE     	   5 /**< Interrupt Event indicating a framing error during USART communication. */
#define		USART_ERR_NE    	   6 /**< Interrupt Event indicating a noise error during USART communication. */
#define		USART_ERR_ORE    	   7 /**< Interrupt Event indicating an overrun error during USART communication. */
/** @} */


/** @} */ // End of USART_Macros group

/** @} */

#endif /* INC_STM32F407XX_USART_DRIVER_H_ */
