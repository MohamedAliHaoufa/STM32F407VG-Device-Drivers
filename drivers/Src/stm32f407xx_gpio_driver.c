/**
 * @file stm32f407xx_gpio_driver.c
 * @author Mohamed Ali Haoufa
 * @brief This file contains the GPIO driver implementation
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// Include the header file for GPIO driver
#include "../drivers/Inc/stm32f407xx_gpio_driver.h"

/**
 * @brief This function enables or disables the peripheral clock for a given GPIO port
 * 
 * @param pGPIOx Pointer to GPIO port
 * @param EnorDi ENABLE or DISABLE macros
 */
void GPIO_PeripheralClockControl (GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();

        } else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();

        } else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();

        } else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();

        } else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();

        } else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();

        } else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();

        } else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();

        } else if(pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();

        }
    }
    else
    {
        if (EnorDi == DISABLE)
        {
            if (pGPIOx == GPIOA)
            {
                GPIOA_PCLK_DI();

            } else if(pGPIOx == GPIOB)
            {
                GPIOB_PCLK_DI();

            } else if(pGPIOx == GPIOC)
            {
                GPIOC_PCLK_DI();

            } else if(pGPIOx == GPIOD)
            {
                GPIOD_PCLK_DI();

            } else if(pGPIOx == GPIOE)
            {
                GPIOE_PCLK_DI();

            } else if(pGPIOx == GPIOF)
            {
                GPIOF_PCLK_DI();

            } else if(pGPIOx == GPIOG)
            {
                GPIOG_PCLK_DI();

            } else if(pGPIOx == GPIOH)
            {
                GPIOH_PCLK_DI();

            } else if(pGPIOx == GPIOI)
            {
                GPIOI_PCLK_DI();

            }
        }
    }
}

/*************************************************************************************************************************
 * Init and DeInit
 */

/**
 * @brief Initialize the GPIO port
 * 
 * @param pGPIOHandle Pointer to GPIO_Handle_t structure
 */
void GPIO_Init (GPIO_Handle_t *pGPIOHandle )
{
    uint32_t temp =0; // temp.register

    // enalbling the peripheral clock  (internally )
    GPIO_PeripheralClockControl ( pGPIOHandle ->pGPIOx, ENABLE );  // to avoid doing it in the code every time

    //1. configure the mode of gpio pin
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        //the non interrupt mode
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ;
        pGPIOHandle->pGPIOx->MODER &= ~ (uint32_t)(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)) ; //clearing
        pGPIOHandle->pGPIOx->MODER |= temp; //setting
        // we use " OU " to not affect the other bits of this register
    }
    else
    {
        //the interrupt mode of detection falling or raising or both triggers
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //1.configure the FTSR register
            EXTI->FTSR |=  (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //clear the corresponding RTSR bit
            EXTI->RTSR &= (uint32_t) ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

        } else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            //2.configure the RSTR register
            EXTI->RTSR |=  (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //clear the corresponding FTSR bit
            EXTI->FTSR &= (uint32_t) ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            //3.configure the FSTR and RSTR register
            EXTI->FTSR |=  (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR |=  (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        //2.configure the GPIO port selection from SYSCFG_EXTICR register (decide which GPIO port should take over this EXTI lines)
        uint32_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4 ;
        uint16_t temp2 = (uint16_t) ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4 ) ;
        uint16_t portcode = GPIO_BASEADDR_TO_CODE( pGPIOHandle->pGPIOx );
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[temp1] = (uint32_t) portcode << (4 * temp2) ;

        //3.enable the exti interrupt delivery from he peripheral to the processor using IMR
        EXTI->IMR |=  (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

    }

    temp = 0;
    //2. confiugure the speed
    temp = ( (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->OSPEEDR &= (uint32_t)~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)) ; //clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = 0;
    //3. configure the pupd settigs
    temp = ( (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->PUPDR &= (uint32_t)~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)) ; //clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = 0;
    //4. configure the optype
    temp = ( (uint32_t) pGPIOHandle->GPIO_PinConfig.GPIO_PinPinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->OTYPER &= (uint32_t)~(0x3 << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber )) ; //clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;
    //5. configure alt functionality
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {

        uint32_t temp1, temp2 ;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8 ; // temp1 = pinNumber(exp:9)/8 = 1
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;  // temp2 = pinNumber(exp:9)%8 = 1
        pGPIOHandle->pGPIOx->AFR[temp1] &= (uint32_t)~(0xF << (4 * temp2)); //clearing the bit positions of the Pin
        // AFR[temp1=1] =  value << (4 * temp2)
        pGPIOHandle->pGPIOx->AFR[temp1] |= ((uint32_t)pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));


    }
}

/**
 * @brief Deinitialize the GPIO port
 * 
 * @param pGPIOx Pointer to GPIO port
 */
void GPIO_DeInit (GPIO_RegDef_t *pGPIOx)
{

    if (pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();

    } else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();

    } else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();

    } else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();

    } else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();

    } else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();

    } else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();

    } else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();

    } else if(pGPIOx == GPIOI)
    {
        GPIOI_REG_RESET();

    }



} // RCC AHB1 peripheral reset register(p233 RF_M) will make all the reg of GPIO to reset value in one shot




/***********************************************************************************************************************
 * Data read and write
 */

/**
 * @brief Read from a specific GPIO pin
 * 
 * @param pGPIOx Pointer to GPIO port
 * @param PinNumber GPIO pin number
 * @return uint8_t Value of the pin (0 or 1)
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) // return the content of input data regiser
{
    //read the corresponding bit position of that pin in the input data register
    uint8_t value;

    //the IDR value shifted by the amount of PinNumber to get that bit position to LSB position of the IDR register
    value = (uint8_t) (( (pGPIOx->IDR) >> PinNumber) & 0x00000001 );

    return value; // 0 or 1
}

/**
 * @brief Read from all pins of a GPIO port
 * 
 * @param pGPIOx Pointer to GPIO port
 * @return uint16_t Value of the GPIO port
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;

    value = (uint16_t) ( pGPIOx->IDR );

    return value;
}

/**
 * @brief Write to a specific GPIO pin
 * 
 * @param pGPIOx Pointer to GPIO port
 * @param PinNumber GPIO pin number
 * @param value Value to be written (SET or RESET)
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber, uint8_t value ) // value = set 1 or reset 0
{
    if (value == GPIO_PIN_SET)
    {
        //write 1 to the output data register at the bit position (field) corresponding to the pin number
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        //write 0
        pGPIOx->ODR &= ~ (uint32_t) ( 1 << PinNumber);
    }
}

/**
 * @brief Write to all pins of a GPIO port
 * 
 * @param pGPIOx Pointer to GPIO port
 * @param value Value to be written to the GPIO port
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
    pGPIOx->ODR = value; // writing to the whole port to the given GPIO
}

/**
 * @brief Toggle a specific GPIO pin
 * 
 * @param pGPIOx Pointer to GPIO port
 * @param PinNumber GPIO pin number
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint16_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber) ;

}

/************************************************************************************************************************
 * IRQ configuration and ISR handling
 */

//all this configuration is processor specific or side

/**
 * @brief Configure the interrupt for a specific GPIO pin
 * 
 * @param IRQNumber IRQ number
 * @param EnorDi ENABLE or DISABLE macros
 */
void GPIO_IRQInterruptConfig (uint8_t IRQNumber, uint8_t EnorDi )  // to configure the IRQ number of GPIO pin enable/setting up priority...etc
{
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
 * @brief Configure the priority of a specific IRQ
 * 
 * @param IRQNumber IRQ number
 * @param IRQpriority Priority of the IRQ
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
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
 * @brief Handle the interrupt for a specific GPIO pin
 * 
 * @param PinNumber GPIO pin number
 */
void GPIO_IRQHandling (uint16_t PinNumber)
{
    // clear the exti pr register corresponding to the pin number
    if ( EXTI->PR & (1 << PinNumber)) // if the value is set then the interrupt is pended
    {
        //clear that pending register bit with 1
        EXTI->PR |= (1 << PinNumber);

    }
}	 //whenever interrupt occurs the userApp call this fonc to process that interrupt

