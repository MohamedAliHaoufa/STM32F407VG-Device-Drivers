/**
 * @file 001led_Toggle.c
 * @author Mohamed Ali Haoufa
 * @brief 
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../drivers/Inc/stm32f407xx.h"

/**
 * @brief 
 * 
 */
static void delay (void)
{

    for( uint32_t i = 0 ; i < 500000 ; i++);

}

/**
 * @brief 
 * 
 * @return int 
 */
//we write the application here
int main(void)
{
    GPIO_Handle_t Gpioled;

    Gpioled.pGPIOx=GPIOD; //GPIO base address

    //pin configuration
    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeripheralClockControl(GPIOD,ENABLE);

    GPIO_Init(&Gpioled);

    while (1)
    {
        GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12) ;
        delay();
    }


    return 0;
}
