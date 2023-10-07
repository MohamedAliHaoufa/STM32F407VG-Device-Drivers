/**
 * @file stm32f407xx_i2c_driver.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and functions prototypes for the STM32F407xx I2C driver.
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INC_STM32F407XX_I2C_DRIVER_H_
#define INC_STM32F407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"
/**
 * @defgroup I2C_Driver I2C Driver
 * @brief I2C driver APIs for STM32F407xx MCU.
 * @{
 */

/**
 * @struct I2C_Config_t
 * @brief Configuration structure for I2C peripheral.
 */
typedef struct
{
    uint32_t I2C_SCLspeed;
    uint8_t I2C_DeviceAdress;   // slave address is 7 bits wide
    uint8_t I2C_ACKControl;
    uint8_t I2C_FMDutyCycle;
} I2C_Config_t;

/**
 * @struct I2C_Handle_t
 * @brief Handle structure for I2C peripheral.
 */
typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxRxState;
    uint8_t DevAddr;
    uint32_t RxSize;
    uint8_t Sr;
} I2C_Handle_t;

/**
 * @defgroup I2C_Macros I2C Macros
 * @brief Macros related to I2C configuration, flags, and events.
 * @{
 */

/**
 * @defgroup I2C_Application_States I2C Application States
 * @brief Possible states of the I2C application.
 * @{
 */
#define I2C_READY           0 /**< I2C application is ready for communication. */
#define I2C_BUSY_IN_RX      1 /**< I2C application is busy receiving data. */
#define I2C_BUSY_IN_TX      2 /**< I2C application is busy transmitting data. */
/** @} */

/**
 * @defgroup I2C_SCL_Speed_Options I2C Serial Clock Speed Options
 * @brief Options for I2C serial clock speed.
 * @{
 */
#define I2C_SC_SPEED_SM     100000   /**< Standard mode serial clock speed, up to 100 KHz. */
#define I2C_SC_SPEED_FM4K   400000   /**< Fast mode serial clock speed, up to 400 KHz. */
#define I2C_SC_SPEED_FM2K   200000   /**< Fast mode serial clock speed, up to 200 KHz. */
/** @} */

/**
 * @defgroup I2C_ACK_Control_Options I2C ACK Control Options
 * @brief Options for controlling the ACK mechanism in I2C communication.
 * @{
 */
#define I2C_ACK_ENABLE      1 /**< Enable ACK mechanism. */
#define I2C_ACK_DISABLE     0 /**< Disable ACK mechanism (default behavior). */
/** @} */

/**
 * @defgroup I2C_FM_Duty_Cycle_Options I2C Fast Mode Duty Cycle Options
 * @brief Options for fast mode duty cycle in I2C communication.
 * @{
 */
#define I2C_FM_DUTY_2       0 /**< Fast mode duty cycle option: Tlow/THigh = 2. */
#define I2C_FM_DUTY_16_9    1 /**< Fast mode duty cycle option: Tlow/THigh = 16/9. */
/** @} */

/**
 * @defgroup I2C_Flags I2C Status Flags
 * @brief Flags indicating various status conditions in I2C communication.
 * @{
 */
#define I2C_FLAG_SB            (1 << I2C_SR1_SB)      /**< Start bit flag. */
#define I2C_FLAG_ADDR          (1 << I2C_SR1_ADDR)    /**< Address sent flag. */
#define I2C_FLAG_BTF           (1 << I2C_SR1_BTF)     /**< Byte transfer finished flag. */
#define I2C_FLAG_ADD10         (1 << I2C_SR1_ADD10)   /**< 10-bit header sent flag. */
#define I2C_FLAG_STOPF         (1 << I2C_SR1_STOPF)   /**< Stop detection flag. */
#define I2C_FLAG_RxNE          (1 << I2C_SR1_RxNE)    /**< Receive data register not empty flag. */
#define I2C_FLAG_TxE           (1 << I2C_SR1_TxE)     /**< Transmit data register empty flag. */
#define I2C_FLAG_BERR          (1 << I2C_SR1_BERR)    /**< Bus error flag. */
#define I2C_FLAG_ARLO          (1 << I2C_SR1_ARLO)    /**< Arbitration lost error flag. */
#define I2C_FLAG_AF            (1 << I2C_SR1_AF)      /**< Acknowledge failure flag. */
#define I2C_FLAG_OVR           (1 << I2C_SR1_OVR)     /**< Overrun/underrun error flag. */
#define I2C_FLAG_PECERR        (1 << I2C_SR1_PECERR)  /**< PEC error in reception flag. */
#define I2C_FLAG_TIMEOUT       (1 << I2C_SR1_TIMEOUT) /**< Timeout error flag. */
#define I2C_FLAG_SMBALERT      (1 << I2C_SR1_SMBALERT)/**< SMBus alert flag. */
/** @} */

/**
 * @defgroup I2C_Repeated_Start_Macros I2C Repeated Start Macros
 * @brief Macros for enabling or disabling repeated start conditions in I2C communication.
 * @{
 */
#define I2C_ENABLE_SR      SET    /**< Macro to enable repeated start condition (SET). */
#define I2C_DISABLE_SR     RESET  /**< Macro to disable repeated start condition (RESET). */
/** @} */

/**
 * @defgroup I2C_Application_Event_Macros I2C Application Event Macros
 * @brief Macros for I2C application events.
 * @{
 */
#define I2C_EV_TX_CMPLT     0 /**< Event: Transmission complete. */
#define I2C_EV_RX_CMPLT     1 /**< Event: Reception complete. */
#define I2C_EV_STOP         2 /**< Event: Stop condition. */
#define I2C_ERROR_BERR      3 /**< Event: Bus error. */
#define I2C_ERROR_ARLO      4 /**< Event: Arbitration lost error. */
#define I2C_ERROR_AF        5 /**< Event: Acknowledge failure. */
#define I2C_ERROR_OVR       6 /**< Event: Overrun/underrun error. */
#define I2C_ERROR_TIMEOUT   7 /**< Event: Timeout error. */
#define I2C_EV_DATA_REQ     8 /**< Event: Data request. */
#define I2C_EV_DATA_RCV     9 /**< Event: Data reception. */
/** @} */

/** @} */ // End of I2C_Macros group



/**
 * @defgroup I2C_APIS I2C APIs
 * @brief APIs supported by the I2C driver.
 * @{
 */

/**
 * @brief Controls the peripheral clock of the I2C peripheral.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param EnorDi ENABLE to enable the clock, DISABLE to disable.
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi );

/**
 * @brief Initializes the I2C peripheral.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 */
void I2C_Init( I2C_Handle_t *pI2CHandle );

/**
 * @brief Deinitializes the I2C peripheral.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 */
void I2C_DeInit( I2C_RegDef_t *pI2Cx );

/**
 * @brief Sends data in master mode over the I2C bus.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 * @param pTxBuffer Pointer to the transmit buffer.
 * @param Len Length of data to be sent.
 * @param SlaveAddr Slave address to communicate with.
 * @param SR Repeated start setting.
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t SR);

/**
 * @brief Receives data in master mode over the I2C bus.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 * @param pRxBuffer Pointer to the receive buffer.
 * @param Len Length of data to be received.
 * @param SlaveAddr Slave address to communicate with.
 * @param SR Repeated start setting.
 */
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t SR);

/**
 * @brief Sends a single byte of data in slave mode over the I2C bus.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param data Data to be sent.
 */
void I2C_SlaveSendData( I2C_RegDef_t *pI2Cx , uint8_t data );

/**
 * @brief Receives a single byte of data in slave mode over the I2C bus.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @return uint8_t Received data.
 */
uint8_t I2C_SlaveReceiveData( I2C_RegDef_t *pI2Cx );

/**
 * @brief Sends data in master mode over the I2C bus with interrupt support.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 * @param pTxBuffer Pointer to the transmit buffer.
 * @param Len Length of data to be sent.
 * @param SlaveAddr Slave address to communicate with.
 * @param SR Repeated start setting.
 * @return uint8_t Status flag.
 */
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t SR);

/**
 * @brief Receives data in master mode over the I2C bus with interrupt support.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 * @param pRxBuffer Pointer to the receive buffer.
 * @param Len Length of data to be received.
 * @param SlaveAddr Slave address to communicate with.
 * @param SR Repeated start setting.
 * @return uint8_t Status flag.
 */
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t SR);

/**
 * @brief Closes the transmission process.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 */
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);

/**
 * @brief Closes the reception process.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 */
void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);

/**
 * @brief Configures IRQ interrupt for the I2C peripheral.
 * 
 * @param IRQNumber IRQ number.
 * @param EnorDi ENABLE to enable the IRQ, DISABLE to disable.
 */
void I2C_IRQInterruptConfig( uint8_t IRQNumber, uint8_t EnorDi );

/**
 * @brief Configures IRQ priority for the I2C peripheral.
 * 
 * @param IRQNumber IRQ number.
 * @param IRQPriority IRQ priority value.
 */
void I2C_IRQPriorityConfig( uint8_t IRQNumber, uint32_t IRQPriority );

/**
 * @brief Handles I2C event interrupt.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 */
void I2C_EV_IRQHandling( I2C_Handle_t *pI2CHandle);

/**
 * @brief Handles I2C error interrupt.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 */
void I2C_ER_IRQHandling( I2C_Handle_t *pI2CHandle);

/**
 * @brief Controls peripheral operation in master mode.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param EnorDi ENABLE to enable, DISABLE to disable.
 */
void I2C_PeripheralControl( I2C_RegDef_t *pI2Cx, uint8_t EnorDi );

/**
 * @brief Retrieves the flag status of the specified I2C flag.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param FlagName Flag to check.
 * @return uint8_t FLAG_SET if flag is set, FLAG_RESET if not.
 */
uint8_t I2C_GetFlagStatus( I2C_RegDef_t *pI2Cx, uint32_t FlagName );

/**
 * @brief Manages ACKing during I2C communication.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param EnorDi I2C_ACK_ENABLE to enable ACKing, I2C_ACK_DISABLE to disable.
 */
void I2C_ManageAcking( I2C_RegDef_t *pI2Cx, uint8_t EnorDi );

/**
 * @brief Generates a stop condition on the I2C bus.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 */
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

/**
 * @brief Enables or disables callback events for the I2C slave.
 * 
 * @param pI2Cx Pointer to the I2C peripheral.
 * @param EnorDi ENABLE to enable callback events, DISABLE to disable.
 */
void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

/**
 * @brief Handles application events for the I2C communication.
 * 
 * @param pI2CHandle Pointer to the I2C handle structure.
 * @param AppEv Application event to be handled.
 */
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);

/** @} */


#endif  /* INC_STM32F407XX_H_ */
