/**
 * @file stm32f407xx_usart_driver.c
 * @author Mohamed Ali Haoufa
 * @brief This file contains the implementation of the USART driver APIs.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

// Include the header file for USART driver
#include "../drivers/Inc/stm32f407xx_usart_driver.h"

/**
 * @defgroup USART_Private_Helper_Functions USART Private Helper Functions
 * @brief These are private helper functions for managing interrupts in USART communication.
 * @{
 */
static void USART_TC_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_TXE_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_RXNE_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_CTS_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_IDLE_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_ORE_ERR_RXNEIE_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_FE_ERR_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_NE_ERR_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
static void USART_ORE_ERR_EIE_Interrupt_Handle(USART_Handle_t *pUSARTHandle);
/** @} */

/**
 * @brief Enable or disable the peripheral clock for the given USARTx.
 *
 * @param pUSARTx Pointer to the USART peripheral.
 * @param EnorDi  ENABLE or DISABLE the clock.
 */
void USART_PeripheralClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pUSARTx == USART1)
        {
            USART1_PCLK_EN();

        } else if(pUSARTx == USART2)
        {
            USART2_PCLK_EN();

        } else if(pUSARTx == USART3)
        {
            USART3_PCLK_EN();

        } else if(pUSARTx == UART4)
        {
            UART4_PCLK_EN();

        } else if(pUSARTx == UART5)
        {
            UART5_PCLK_EN();

        } else if(pUSARTx == USART6)
        {
            USART6_PCLK_EN();

        }
    }
    else
    {
        if (EnorDi == DISABLE)
        {
            if (pUSARTx == USART1)
            {
                USART1_PCLK_DI();

            } else if(pUSARTx == USART2)
            {
                USART2_PCLK_DI();

            } else if(pUSARTx == USART3)
            {
                USART3_PCLK_DI();

            } else if(pUSARTx == UART4)
            {
                UART4_PCLK_DI();

            } else if(pUSARTx == UART5)
            {
                UART5_PCLK_DI();

            } else if(pUSARTx == USART6)
            {
                USART6_PCLK_DI();

            }
        }
    }
}

/**
 * @brief Control the USART peripheral (ENABLE/DISABLE).
 *
 * @param pUSARTx Pointer to the USART peripheral.
 * @param EnorDi  ENABLE or DISABLE the peripheral.
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi){
	if (EnorDi == ENABLE){
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else {
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}

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
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
	uint32_t PCLKx;

	uint32_t usartdiv;

	//variables to hold Mantissa and Fraction values
	uint32_t M_part,F_part;

  uint32_t tempreg=0;

  //Get the value of APB bus clock in to the variable PCLKx
  if(pUSARTx == USART1 || pUSARTx == USART6)
  {
	   //USART1 and USART6 are hanging on APB2 bus
	   PCLKx = RCC_GetPCLK2Value();
  }else
  {
	   PCLKx = RCC_GetPCLK1Value();
  }

  //Check for OVER8 configuration bit
  if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
  {
	   //OVER8 = 1 , over sampling by 8
	   usartdiv = ((25 * PCLKx) / (2 *BaudRate));
  }else
  {
	   //OVER8 = 0 , over sampling by 16
	   usartdiv = ((25 * PCLKx) / (4 *BaudRate));

  }

  //Calculate the Mantissa part
  M_part = usartdiv/100;

  //Place the Mantissa part in appropriate bit position . refer USART_BRR
  tempreg |= M_part << USART_BRR_DIV_MANTISSA;

  //Extract the fraction part
  F_part = (usartdiv - (M_part * 100));

  //Calculate the final fractional
  if(pUSARTx->CR1 & ( 1 << USART_CR1_OVER8))
   {
	  //OVER8 = 1 , over sampling by 8
	  F_part = ((( F_part * 8)+ 50) / 100) & ((uint8_t)0x07);

   }else
   {
	   //over sampling by 16
	   F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

   }

  //Place the fractional part in appropriate bit position . refer USART_BRR
  tempreg |= F_part << USART_BRR_DIV_FRACTION;

  //copy the value of tempreg in to BRR register
  pUSARTx->BRR = tempreg;
}

/**
 * @brief Initialize the USART peripheral.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{

	//Temporary variable
	uint32_t tempreg=0;

/******************************** Configuration of CR1******************************************/

	//enable the Clock for given USART peripheral
	USART_PeripheralClockControl(pUSARTHandle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{
		//enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{
		//enable the Transmitter bit field
		tempreg |= (1 << USART_CR1_TE);

	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		//enable the both Transmitter and Receiver bit fields
		tempreg |= ( ( 1 << USART_CR1_RE) | ( 1 << USART_CR1_TE) );
	}

    //configure the Word length configuration item
	tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M ;


    //Configuration of parity control bit fields
	if ( pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		//enale the parity control
		tempreg |= ( 1 << USART_CR1_PCE);

		//enable EVEN parity
		//Not required because by default EVEN parity will be selected once you enable the parity control

	}else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD )
	{
		//enable the parity control
	    tempreg |= ( 1 << USART_CR1_PCE);

	    //enable ODD parity
	    tempreg |= ( 1 << USART_CR1_PS);

	}

   //Program the CR1 register
	pUSARTHandle->pUSARTx->CR1 = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg=0;

	//configure the number of stop bits inserted during USART frame transmission
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

	//Program the CR2 register
	pUSARTHandle->pUSARTx->CR2 = tempreg;

/******************************** Configuration of CR3******************************************/

	tempreg=0;

	//Configuration of USART hardware flow control
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//enable CTS flow control
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//enable RTS flow control
		tempreg |= (1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//enable both CTS and RTS Flow control
		tempreg |= ( (1 << USART_CR3_RTSE) | ( 1 << USART_CR3_CTSE) );
	}


	pUSARTHandle->pUSARTx->CR3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	//configure the baud rate
	//We will cover this in the lecture. No action required here
	USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);

}

/**
 * @brief Deinitialize the USART peripheral.
 *
 * @param pUSARTx Pointer to the USART peripheral.
 */
void USART_DeInit(USART_RegDef_t *pUSARTx)
{

    if (pUSARTx == USART1)
    {
        USART1_REG_RESET();

    } else if(pUSARTx == USART2)
    {
        USART2_REG_RESET();

    } else if(pUSARTx == USART3)
    {
        USART3_REG_RESET();

    } else if(pUSARTx == UART4)
    {
        UART4_REG_RESET();

    } else if(pUSARTx == UART5)
    {
        UART5_REG_RESET();

    } else if(pUSARTx == USART6)
    {
        USART6_REG_RESET();

    }

}


/**
 * @brief Send data over USART.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pTxBuffer   Pointer to the transmit buffer.
 * @param Len         Length of data to be sent.
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint16_t *pdata;
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TXE));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//increment pTxBuffer twice
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);

			//increment the buffer address
			pTxBuffer++;
		}
	}

	//wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TC));
}

/**
 * @brief Receive data from USART.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pRxBuffer   Pointer to the receive buffer.
 * @param Len         Length of data to be received.
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	   //Loop over until "Len" number of bytes are transferred
		for(uint32_t i = 0 ; i < Len; i++)
		{
			//wait until RXNE flag is set in the SR
			while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_RXNE));

			//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
			if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
			{
				//We are going to receive 9bit data in a frame

				//check are we using USART_ParityControl control or not
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					//No parity is used. so, all 9bits will be of user data

					//read only first 9 bits. so, mask the DR with 0x01FF
					*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

					//Now increment the pRxBuffer two times
					pRxBuffer++;
					pRxBuffer++;
				}
				else
				{
					//Parity is used, so, 8bits will be of user data and 1 bit is parity
					 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);

					 //Increment the pRxBuffer
					 pRxBuffer++;
				}
			}
			else
			{
				//We are going to receive 8bit data in a frame

				//check are we using USART_ParityControl control or not
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					//No parity is used , so all 8bits will be of user data

					//read 8 bits from DR
					 *pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0XFF);;
				}

				else
				{
					//Parity is used, so , 7 bits will be of user data and 1 bit is parity

					//read only 7 bits , hence mask the DR with 0X7F
					 *pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0X7F);

				}

				//increment the pRxBuffer
				pRxBuffer++;
			}
		}
}

/**
 * @brief Send data over USART using interrupt-driven communication.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pTxBuffer    Pointer to the transmit buffer.
 * @param Len          Length of data to be sent.
 * @return uint8_t     Transmission status.
 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		//enable interrupt for TXE
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);

		//enable interrupt for TC
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);


	}

	return txstate;
}

/**
 * @brief Receive data from USART using interrupt-driven communication.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param pRxBuffer    Pointer to the receive buffer.
 * @param Len          Length of data to be received.
 * @return uint8_t     Reception status.
 */
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		(void)pUSARTHandle->pUSARTx->DR;

		//enable interrupt for RXNE
		pUSARTHandle->pUSARTx->CR1 = (1 << USART_CR1_RXNEIE);

	}

	return rxstate;
}

/**
 * @brief Get the status of a specific USART flag.
 *
 * @param pUSARTx   Pointer to the USART peripheral.
 * @param FlagName  Name of the flag to check.
 * @return uint8_t  Status of the flag (FLAG_SET or FLAG_RESET).
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t FlagName){
	if(pUSARTx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/**
 * @brief Clear a specific USART flag.
 *
 * @param pUSARTx   Pointer to the USART peripheral.
 * @param FlagName  Name of the flag to clear.
 */
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t FlagName){
	pUSARTx->SR &= ~(uint32_t)(1 << FlagName);
}

/************************************************************************************************************************
 * IRQ configuration and ISR handling
 */

/**
 * @brief Configure IRQ number and enable/disable IRQ.
 *
 * @param IRQNumber IRQ number to configure.
 * @param EnorDi    ENABLE or DISABLE IRQ.
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){

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
 * @brief Set the priority of an IRQ.
 *
 * @param IRQNumber     IRQ number to set priority for.
 * @param IRQPriority   Priority to be set.
 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // there is 60 interrupt priority register IPR each 32Bit 4section eachsection 8bits
    //for exp : from the IRQ237 -> 237/4 = 59( touch IPR59 register ) ;
    // 237%4 = 1(the section position of the IRQ237) ;  shift by 1*8 to touch IRQ237

    // 1.first let's find out the ipr register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift_amount = ( 8 * iprx_section ) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount) ; // uint32_t will increment by 4 each increment

}

/**
 * @brief Handle USART interrupts.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{

	uint32_t temp1 , temp2, temp3;



/*************************Check for TC flag ********************************************/

    //check the state of TC bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TC);

	 //check the state of TCIE bit in the CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TCIE);

	if(temp1 && temp2 )
	{
		//this interrupt is because of TC
		// Handle the TC Interrupt
		USART_TC_Interrupt_Handle(pUSARTHandle);

	}

/*************************Check for TXE flag ********************************************/

	//check the state of TXE bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_TXE);

	//check the state of TXEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_TXEIE);


	if(temp1 && temp2 )
	{
		//this interrupt is because of TXE
		// Handle the TXE Interrupt
		USART_TXE_Interrupt_Handle(pUSARTHandle);

	}

/*************************Check for RXNE flag ********************************************/

	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_RXNE);
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_RXNEIE);


	if(temp1 && temp2 )
	{
		//this interrupt is because of rxne
		// Handle the RXNE Interrupt
		USART_RXNE_Interrupt_Handle(pUSARTHandle);

	}


/*************************Check for CTS flag ********************************************/
//Note : CTS feature is not applicable for UART4 and UART5

	//check the status of CTS bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_CTS);

	//check the state of CTSE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSE);

	//check the state of CTSIE bit in CR3 (This bit is not available for UART4 & UART5.)
	temp3 = pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_CTSIE);
	(void)temp3; // just to avoid warnings

	if(temp1  && temp2 )
	{
		// Handle the CTS Interrupt
		USART_CTS_Interrupt_Handle(pUSARTHandle);
	}

/*************************Check for IDLE detection flag ********************************************/

	//check the status of IDLE flag bit in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & ( 1 << USART_SR_IDLE);

	//check the state of IDLEIE bit in CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & ( 1 << USART_CR1_IDLEIE);


	if(temp1 && temp2)
	{
		// Handle the IDLE Interrupt
		USART_IDLE_Interrupt_Handle(pUSARTHandle);

	}

/*************************Check for Overrun detection flag ********************************************/

	//check the status of ORE flag  in the SR
	temp1 = pUSARTHandle->pUSARTx->SR & USART_SR_ORE;

	//check the status of RXNEIE  bit in the CR1
	temp2 = pUSARTHandle->pUSARTx->CR1 & USART_CR1_RXNEIE;


	if(temp1  && temp2 )
	{
		// Handle the ORE Interrupt from the RXNEIE control bit
		USART_ORE_ERR_RXNEIE_Interrupt_Handle(pUSARTHandle);
	}



/*************************Check for Error Flag ********************************************/

//Noise Flag, Overrun error and Framing Error in multibuffer communication
//We dont discuss multibuffer communication in this course. please refer to the RM
//The blow code will get executed in only if multibuffer mode is used.

	temp2 =  pUSARTHandle->pUSARTx->CR3 & ( 1 << USART_CR3_EIE) ;

	if(temp2 )
	{
		temp1 = pUSARTHandle->pUSARTx->SR;
		if(temp1 & ( 1 << USART_SR_FE))
		{
			/*
				This bit is set by hardware when a de-synchronization, excessive noise or a break character
				is detected. It is cleared by a software sequence (an read to the USART_SR register
				followed by a read to the USART_DR register).
			*/
			// handle the FE Interrupt
			USART_FE_ERR_Interrupt_Handle(pUSARTHandle);
		}

		if(temp1 & ( 1 << USART_SR_NF) )
		{
			/*
				This bit is set by hardware when noise is detected on a received frame. It is cleared by a
				software sequence (an read to the USART_SR register followed by a read to the
				USART_DR register).
			*/
			// Handle the NF Interrupt
			USART_NE_ERR_Interrupt_Handle(pUSARTHandle);
		}

		if(temp1 & ( 1 << USART_SR_ORE) )
		{
			/*
			 * The Overrun Error (ORE) bit is set by the USART hardware when new data is received
			 * while the receive buffer (RDR) shift register is still holding unread data. It indicates that some
			 * previously received data was not read before new data arrived, a common situation in
			 * high-speed communication scenarios.
			 */
			// Handle the ORE Interrupt from the EIE control bit
			USART_ORE_ERR_EIE_Interrupt_Handle(pUSARTHandle);
		}
	}


}

/**
 * @brief Application callback function for USART events.
 *
 * This function serves as a callback that can be overridden by the application to handle
 * USART-related events. It is called when specific events occur during USART communication
 * and allows the application to take custom actions.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 * @param AppEv        USART application event.
 *
 * @note This is a weak implementation, and the application can override this function to provide
 *       custom event handling.
 */
__weak void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv){

	// This is a weak implementation and the appication may override this function.
}


/**
 * @brief Clears the event/error flags in the USART status register.
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
void USART_ClearEventErrFlag(USART_RegDef_t *pUSARTx){
	uint8_t temp;
	temp = pUSARTx->DR;
	temp = pUSARTx->SR;
	(void)temp;

}

/**
 * @brief Close USART transmission.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_CloseTransmission(USART_Handle_t *pUSARTHandle){
	//clear the TXEIE bit (disable interrupt for TXE flag )
	pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_TXEIE);
	pUSARTHandle->pTxBuffer = NULL;
	pUSARTHandle->TxLen = 0;
	pUSARTHandle->TxBusyState = USART_READY;
}

/**
 * @brief Close USART reception.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
void USART_CloseReception(USART_Handle_t *pUSARTHandle){
	//disable the rxne
	pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_RXNEIE );
	pUSARTHandle->pRxBuffer = NULL;
	pUSARTHandle->RxLen = 0;
	pUSARTHandle->RxBusyState = USART_READY;
}

/**
 * @brief USART Transmission Complete Interrupt Handle.
 *
 * This function handles the USART Transmission Complete (TC) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_TC_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	//close transmission and call application callback if TxLen is zero
	if ( pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
	{
		//Check the TxLen . If it is zero then close the data transmission
		if(! pUSARTHandle->TxLen )
		{
			//clear the TC flag
			USART_ClearFlag(pUSARTHandle->pUSARTx, USART_SR_TC);

			//clear the TCIE control bit
			pUSARTHandle->pUSARTx->CR1 &= ~( 1 << USART_CR1_TCIE);

			//Reset the application state
			pUSARTHandle->TxBusyState = USART_READY;

			//Reset Buffer address to NULL
			pUSARTHandle->pTxBuffer = NULL;

			//Reset the length to zero
			pUSARTHandle->TxLen = 0;

			//Call the application call back with event USART_EVENT_TX_CMPLT
			USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_TX_CMPLT);
		}
	}
}

/**
 * @brief USART Transmit Data Register Empty Interrupt Handle.
 *
 * This function handles the USART Transmit Data Register Empty (TXE) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_TXE_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	uint16_t *pdata;

	if(pUSARTHandle->TxBusyState == USART_BUSY_IN_TX)
	{
		//Keep sending data until Txlen reaches to zero
		if(pUSARTHandle->TxLen > 0)
		{
			//Check the USART_WordLength item for 9BIT or 8BIT in a frame
			if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
			{
				//if 9BIT load the DR with 2bytes masking  the bits other than first 9 bits
				pdata = (uint16_t*) pUSARTHandle->pTxBuffer;
				pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

				//check for USART_ParityControl
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					//No parity is used in this transfer , so 9bits of user data will be sent
					//increment pTxBuffer twice
					pUSARTHandle->pTxBuffer++;
					pUSARTHandle->pTxBuffer++;
					pUSARTHandle->TxLen-=2;
				}
				else
				{
					//Parity bit is used in this transfer . so 8bits of user data will be sent
					//The 9th bit will be replaced by parity bit by the hardware
					pUSARTHandle->pTxBuffer++;
					pUSARTHandle->TxLen-=1;
				}
			}
			else
			{
				//This is 8bit data transfer
				pUSARTHandle->pUSARTx->DR = (*pUSARTHandle->pTxBuffer  & (uint8_t)0xFF);

				//increment the buffer address
				pUSARTHandle->pTxBuffer++;
				pUSARTHandle->TxLen-=1;
			}

		}
		if (pUSARTHandle->TxLen == 0 )
		{
			//TxLen is zero
			USART_CloseTransmission(pUSARTHandle);
			USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_TX_CMPLT);

		}
	}
}

/**
 * @brief USART Receive Data Register Not Empty Interrupt Handle.
 *
 * This function handles the USART Receive Data Register Not Empty (RXNE) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_RXNE_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	if(pUSARTHandle->RxBusyState == USART_BUSY_IN_RX)
	{
		if(pUSARTHandle->RxLen > 0)
		{
			//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
			if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
			{
				//We are going to receive 9bit data in a frame

				//Now, check are we using USART_ParityControl control or not
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					//No parity is used , so all 9bits will be of user data

					//read only first 9 bits so mask the DR with 0x01FF
					*((uint16_t*) pUSARTHandle->pRxBuffer) = (uint16_t)(pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

					//Now increment the pRxBuffer two times
					pUSARTHandle->pRxBuffer++;
					pUSARTHandle->pRxBuffer++;
					pUSARTHandle->RxLen-=2;
				}
				else
				{
					//Parity is used, so 8bits will be of user data and 1 bit is parity
					 *pUSARTHandle->pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
					 pUSARTHandle->pRxBuffer++;
					 pUSARTHandle->RxLen-=1;
				}
			}
			else
			{
				//We are going to receive 8bit data in a frame

				//Now, check are we using USART_ParityControl control or not
				if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
				{
					//No parity is used , so all 8bits will be of user data

					//read 8 bits from DR
					 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);

				}

				else
				{
					//Parity is used, so , 7 bits will be of user data and 1 bit is parity

					//read only 7 bits , hence mask the DR with 0X7F
					 *pUSARTHandle->pRxBuffer = (uint8_t) (pUSARTHandle->pUSARTx->DR  & (uint8_t)0x7F);

				}

				//Now , increment the pRxBuffer
				pUSARTHandle->pRxBuffer++;
				pUSARTHandle->RxLen-=1;
			}


		}

		if(! pUSARTHandle->RxLen)
		{   // RxLen is zero
			USART_CloseReception(pUSARTHandle);
			USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_RX_CMPLT);
		}
	}
}

/**
 * @brief USART Clear to Send Interrupt Handle.
 *
 * This function handles the USART Clear to Send (CTS) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_CTS_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	//clear the CTS flag in SR
	USART_ClearFlag(pUSARTHandle->pUSARTx, USART_SR_CTS);

	//this interrupt is because of CTS
	USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_CTS);
}

/**
 * @brief USART Idle Line Detected Interrupt Handle.
 *
 * This function handles the USART Idle Line Detected (IDLE) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_IDLE_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	//clear the IDLE flag. Refer to the RM to understand the clear sequence
	USART_ClearEventErrFlag(pUSARTHandle->pUSARTx);

	//this interrupt is because of idle
	USART_ApplicationEventCallback(pUSARTHandle,USART_EVENT_IDLE);
}

/**
 * @brief USART Overrun Error Interrupt Handle (RXNEIE).
 *
 * This function handles the USART Overrun Error (ORE) interrupt event
 * caused by the RXNEIE bit in the control register.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_ORE_ERR_RXNEIE_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	//Need not to clear the ORE flag here, instead give an api for the application to clear the ORE flag .
	USART_ClearFlag(pUSARTHandle->pUSARTx, USART_SR_ORE);

	//this interrupt is because of Overrun error
	USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_ORE);
}

/**
 * @brief USART Framing Error Interrupt Handle.
 *
 * This function handles the USART Framing Error (FE) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_FE_ERR_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	// clear the FE flag. Refer to the RM to understand the clear sequence
	USART_ClearEventErrFlag(pUSARTHandle->pUSARTx);

	USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_FE);
}

/**
 * @brief USART Noise Error Interrupt Handle.
 *
 * This function handles the USART Noise Error (NE) interrupt event.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_NE_ERR_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	// clear the NF flag. Refer to the RM to understand the clear sequence
	USART_ClearEventErrFlag(pUSARTHandle->pUSARTx);

	USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_NE);
}

/**
 * @brief USART Overrun Error Interrupt Handle (EIE).
 *
 * This function handles the USART Overrun Error (ORE) interrupt event
 * caused by the EIE bit in the control register.
 *
 * @param pUSARTHandle Pointer to the USART handle structure.
 */
static void USART_ORE_ERR_EIE_Interrupt_Handle(USART_Handle_t *pUSARTHandle){

	// clear the ORE flag. Refer to the RM to understand the clear sequence
	USART_ClearEventErrFlag(pUSARTHandle->pUSARTx);

	USART_ApplicationEventCallback(pUSARTHandle,USART_ERR_ORE);
}

