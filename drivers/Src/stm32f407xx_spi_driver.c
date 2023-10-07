/**
 * @file stm32f407xx_spi_driver.c
 * @author Mohamed Ali Haoufa
 * @brief This file contains the implementation of the SPI driver APIs.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

// Include the header file for GPIO driver
#include "../drivers/Inc/stm32f407xx_spi_driver.h"

/**
 * @defgroup SPI_Private_Helper_Functions SPI Private Helper Functions
 * @brief These are private helper functions for managing interrupts in SPI communication.
 * @{
 */

/**
 * @brief SPI Transmit Buffer Empty Interrupt Handler.
 *
 * This function is called when the SPI transmit buffer becomes empty and is ready to accept new data.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for the transmit buffer empty condition.
 */
static void SPI_TXE_Interrupt_Handle(SPI_Handle_t *pSPIHandle);

/**
 * @brief SPI Receive Buffer Not Empty Interrupt Handler.
 *
 * This function is called when the SPI receive buffer contains new data to be read.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for the receive buffer not empty condition.
 */
static void SPI_RXNE_Interrupt_Handle(SPI_Handle_t *pSPIHandle);

/**
 * @brief SPI Overrun Error Interrupt Handler.
 *
 * This function is called when an overrun error occurs in the SPI communication.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for overrun error conditions.
 */
static void SPI_OVE_ERR_Interrupt_Handle(SPI_Handle_t *pSPIHandle);

/** @} */



/**
 * @brief Enables or disables the peripheral clock for the SPI port.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param EnorDi ENABLE to enable clock, DISABLE to disable clock.
 */
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
    if (EnorDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_EN();

        } else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();

        } else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();

        } else if(pSPIx == SPI4)
        {
            SPI4_PCLK_EN();

        }
    }
    else
    {
        if (EnorDi == DISABLE)
        {
            if (pSPIx == SPI1)
            {
                SPI1_PCLK_DI();

            } else if(pSPIx == SPI2)
            {
                SPI2_PCLK_DI();

            } else if(pSPIx == SPI3)
            {
                SPI3_PCLK_DI();

            } else if(pSPIx == SPI4)
            {
                SPI4_PCLK_DI();

            }
        }
    }
}

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
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if (EnorDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

/*************************************************************************************************************************
 * Init and DeInit
 */

/**
 * @brief Initializes the SPI port pin according to the configuration.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle){

	//peripheral clock enable
	SPI_PeripheralClockControl(pSPIHandle->pSPIx, ENABLE);
	//first lets configure the SPI_CR1 Register
	uint32_t tempreg =0;

	// 1. Configure the device mode
	tempreg |= pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. configure the bus config
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FULL_DUPLEX){
		// BIDI mode should be cleared
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HALF_DUPLEX){
		// BIDI mode should be set
		tempreg |= (1<<SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY){
		// BIDI mode should be cleared
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);
		// RXONLY bit must be set
		tempreg |= (1<<SPI_CR1_RXONLY);

	}
	// 3. Configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. Configure the DFF
	tempreg |= pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF;

	// 5. Configure the CPOL
	tempreg |= pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;

	// 6. Configure the CPHA
	tempreg |= pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA;

	// 7. Configure the SSM
	tempreg |= pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;
}

/**
 * @brief Deinitializes the SPI port.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx){

    if (pSPIx == SPI1)
    {
        SPI1_REG_RESET();

    } else if(pSPIx == SPI2)
    {
        SPI2_REG_RESET();

    } else if(pSPIx == SPI3)
    {
        SPI3_REG_RESET();

    } else if(pSPIx == SPI4)
    {
        SPI4_REG_RESET();

    }
}

/**
 * @brief Get the status of a specific SPI flag.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param FlagName Flag to check (e.g., SPI_TXE_FLAG, SPI_RXNE_FLAG).
 *
 * @return FLAG_SET if the flag is set, FLAG_RESET if not.
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/***********************************************************************************************************************
 * Send and Receive Data
 */

/**
 * @brief Sends data over SPI. it's a blocking call.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param pTxBuffer Pointer to the transmit buffer.
 * @param Len Length of data to be sent.
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){

	while(Len > 0){
		//while(! (pSPIx->SR & (1<<SPI_SR_TXE) ));
		// wait until TXE is set
		while( SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET );

		// 2. check the DFF in CR1
		if(pSPIx->CR1 & SPI_CR1_DFF){
			// 16 bit DDR
			// 1. Load the data into the DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;

		} else {
			// 8 bit DDR
			// 1. Load the data into the DR
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}

/**
 * @brief Receives data over SPI.
 *
 * @param pSPIx Pointer to the SPI peripheral.
 * @param pRxBuffer Pointer to the receive buffer.
 * @param Len Length of data to be received.
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){

	while(Len > 0){
		//while(! (pSPIx->SR & (1<<SPI_SR_RXNE) ));
		// wait until RXNE is set
		while( SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET );

		// 2. check the DFF in CR1
		if(pSPIx->CR1 & SPI_CR1_DFF){
			// 16 bit DDR
			// 1. read the data from the DR
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;

		} else {
			// 8 bit DDR
			// 1. read the data from the DR
			*(pRxBuffer) = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}

}

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
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if (EnorDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else {
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

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
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if (EnorDi == ENABLE){
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else {
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

/************************************************************************************************************************
 * IRQ configuration and ISR handling
 */

/**
 * @brief Configures the IRQ for a specific SPI pin.
 *
 * @param IRQNumber IRQ number.
 * @param EnorDi ENABLE to enable IRQ, DISABLE to disable IRQ.
 */
void SPI_IRQinterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){

    // in cortex M4 generic user guide p219 in NVIC registers
    if (EnorDi == ENABLE)
    {
        if (IRQNumber <= 31 )
        {
            //program ISER0 register
            //derefrence the address of The ISER0 register and put the value
            *NVIC_ISER0 = (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64 )
        {
            //program ISER1 register
            *NVIC_ISER1 = (1 << IRQNumber % 32); // 32 is the 0 so 32%32=0

        } else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            //program ISER2 register // 64 to 95
            *NVIC_ISER2 = (1 << IRQNumber % 64);

        }
    }
    else if(EnorDi == DISABLE) {

        if (IRQNumber <=31 )
        {
            //program ICER0 register
            *NVIC_ICER0 = (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64 )
        {
            //program ICER1 register
            *NVIC_ICER1 = (1 << IRQNumber % 32 );

        } else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            //program ICER2 register // 64 to 95
            *NVIC_ICER2 = (1 << IRQNumber % 64);
        }
    }
}

/**
 * @brief Configures the priority for a specific IRQ.
 *
 * @param IRQNumber IRQ number.
 * @param IRQpriority Priority value.
 */
void SPI_IRQperiorityConfig(uint8_t IRQNumber, uint32_t IRQpriority){

    // there is 60 interrupt priority register IPR each 32Bit 4section eachsection 8bits
    //for exp : from the IRQ237 -> 237/4 = 59( touch IPR59 register ) ;
    // 237%4 = 1(the section position of the IRQ237) ;  shift by 1*8 to touch IRQ237

    // 1.first let's find out the ipr register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift_amount = ( 8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQpriority << shift_amount) ; // uint32_t will increment by 4 each increment

}

/**
 * @brief Handles the IRQ for a specific SPI pin.
 *
 * @param PinNumber SPI pin number.
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle){

	uint8_t temp1, temp2;

	// first let's check for the TXE
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_TXE) ;
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE) ;

	if(temp1 && temp2){
		// Handle the TXE Interrupt
		SPI_TXE_Interrupt_Handle(pSPIHandle);
	}

	// secondly let's check for the RXNE
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_RXNE) ;
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE) ;

	if(temp1 && temp2){
		// Handle the RXNE Interrupt
		SPI_RXNE_Interrupt_Handle(pSPIHandle);

	}

	// Thirdly let's check for the OVR
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_SR_OVR) ;
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE) ;

	if(temp1 && temp2){
		// Handle the OVR Interrupt
		SPI_OVE_ERR_Interrupt_Handle(pSPIHandle);

	}

}

/***********************************************************************************************************************
 * Send and Receive Data (Interrupt mode)
 */

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
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len){

	uint8_t status = pSPIHandle->TxState;

	if(status != SPI_BUSY_IN_TX){

	// 1. Save the Tx buffer address and Len information in some global variables
	pSPIHandle->pTxBuffer = pTxBuffer;
	pSPIHandle->TxLen = Len;

	// 2. Mark the SPI state as busy in transmission so that
	//    no other code can take over same SPI peripheral until transmission is over
	pSPIHandle->TxState = SPI_BUSY_IN_TX;

	// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
	pSPIHandle->pSPIx->CR2 = (1 << SPI_CR2_TXEIE);

	// 4. Data Transmission will be handled by the ISR handler code
	}

	return status;
}

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
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len){

	uint8_t status = pSPIHandle->RxState;

	if(status != SPI_BUSY_IN_RX){

	// 1. Save the Rx buffer address and Len information in some global variables
	pSPIHandle->pRxBuffer = pRxBuffer;
	pSPIHandle->RxLen = Len;

	// 2. Mark the SPI state as busy in reception so that
	//    no other code can take over same SPI peripheral until reception is over
	pSPIHandle->RxState = SPI_BUSY_IN_RX;

	// 3. Enable the RXEIE control bit to get interrupt whenever RXNE flag is set in SR
	pSPIHandle->pSPIx->CR2 = (1 << SPI_CR2_RXNEIE);

	// 4. Data Transmission will be handled by the ISR handler code
	}
	return status;
}

/***********************************************************************************************************************
 * Interrupt handling APIs
 */

/**
 * @brief SPI Transmit Buffer Empty Interrupt Handler.
 *
 * This function is called when the SPI transmit buffer becomes empty and is ready to accept new data.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for the transmit buffer empty condition.
 */
static void SPI_TXE_Interrupt_Handle(SPI_Handle_t *pSPIHandle){

	// 2. check the DFF in CR1
	if(pSPIHandle->pSPIx->CR1 & SPI_CR1_DFF){
		// 16 bit DDR
		// 1. Load the data into the DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;

	} else {
		// 8 bit DDR
		// 1. Load the data into the DR
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	if(! pSPIHandle->TxLen){
		// TxLen is zero, so close the spi transmission and inform the application that
		// Tx is over
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}

/**
 * @brief SPI Receive Buffer Not Empty Interrupt Handler.
 *
 * This function is called when the SPI receive buffer contains new data to be read.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for the receive buffer not empty condition.
 */
static void SPI_RXNE_Interrupt_Handle(SPI_Handle_t *pSPIHandle){

	// 2. check the DFF in CR1
	if(pSPIHandle->pSPIx->CR1 & SPI_CR1_DFF){
		// 16 bit DDR
		// 1. read the data from the DR
		*((uint16_t*)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->RxLen--;
		(uint16_t*)pSPIHandle->pRxBuffer++;

	} else {
		// 8 bit DDR
		// 1. read the data from the DR
		*(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++;
	}

	if(! pSPIHandle->RxLen){
		// RxLen is zero, so close the spi Reception and inform the application that
		// Rx is over
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}

/**
 * @brief SPI Overrun Error Interrupt Handler.
 *
 * This function is called when an overrun error occurs in the SPI communication.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 * It handles the interrupt for overrun error conditions.
 */
static void SPI_OVE_ERR_Interrupt_Handle(SPI_Handle_t *pSPIHandle){

	uint8_t temp;
	// 1. Clear the OVR flag
	// we have to read from the SPI_DR register and then read access to SPI_SR register
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX){
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;
	}
	// 2. inform the Application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
	(void)temp;
}

/**
 * @brief Clears the overrun error (OVR) flag in the SPI peripheral.
 *
 * This function clears the overrun error flag in the status register of the SPI peripheral.
 * Overrun errors occur when new data is received before the previous data is read, causing
 * data loss.
 *
 * @param pSPIx Pointer to the SPI peripheral for which the overrun error flag should be cleared.
 */
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;

}

/**
 * @brief Closes the transmission operation on the SPI peripheral.
 *
 * This function is used to close the transmission operation on the SPI peripheral after
 * all the data has been transmitted. It disables the transmit buffer empty interrupt and
 * sets the transmission state to idle.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle){

	// this prevents interrupts from setting up of TXE flag
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
	// Reset the buffer, length and the state members
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
}

/**
 * @brief Closes the reception operation on the SPI peripheral.
 *
 * This function is used to close the reception operation on the SPI peripheral after
 * all the data has been received. It disables the receive buffer not empty interrupt and
 * sets the reception state to idle.
 *
 * @param pSPIHandle Pointer to the SPI handle structure.
 */
void SPI_CloseReception(SPI_Handle_t *pSPIHandle){

	// this prevents interrupts from setting up of RXNE flag
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
	// Reset the buffer, length and the state members
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;
}

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
__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv){

	// This is a weak implementation and the appication may override this function.
}

