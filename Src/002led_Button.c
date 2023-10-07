/**
 * @file 003led_Button_ext.c
 * @author Mohamed Ali Haoufa
 * @brief 
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "../drivers/Inc/stm32f407xx.h"

#define HIGH         0x1
#define BTN_PRESSED  HIGH

// global shared variable between code and ISR
uint8_t volatile g_button_pressed = 0;

void delay (void)
{

    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

static void Led_Delay(void) {
	int i;
    for (i = 0; i < 100000; i++);
}

//we write the application here
int main(void)
{
    GPIO_Handle_t Gpioled,GPIOABtn;

    //this is led gpio configuration

    Gpioled.pGPIOx=GPIOD; //GPIO base address

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&Gpioled);

    //this is Button gpio configuration

    GPIOABtn.pGPIOx=GPIOA; //GPIO base address

    GPIOABtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOABtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOABtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOABtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; //there is a pull down available in the shematic of the Button
    GPIO_Init(&GPIOABtn);

    GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_13,GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_14,GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_15,GPIO_PIN_RESET);

    while(1){

    	//printf("waiting for the button press\n");

    	while( GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0) != 0){
            {
                // wait until the debouncing of button over cuz this ISR will excute few times before getting stable
            	delay(); //200ms

            	// Make this flag SET . if button pressed
            	g_button_pressed = 1;

            	if(g_button_pressed){
            		//printf("\n The Button is pressed : %lu !!\n",g_button_pressed_count);
            		g_button_pressed = 0;

            		for(int i=12 ;i<=15 ;i++){
            			Led_Delay();
            			GPIO_ToggleOutputPin(GPIOD, i);
            			Led_Delay();
            		}
            	}

            }
          }
    }
        return 0;
}



