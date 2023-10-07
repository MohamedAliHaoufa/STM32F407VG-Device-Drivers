/**
 * @file 005Button_interrupt.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "../drivers/Inc/stm32f407xx.h"
#include<string.h> //for memset API

#define HIGH         1
#define LOW          0
#define Btn_pressed  LOW

void EXTI0_IRQHandler(void); // !! prototype maybe not nedded since NVIC table maybe prototyped the func somewhere else and call this one since the other one is weak in the start up file

// global shared variable between code and ISR
uint8_t volatile g_button_pressed = 0;
uint32_t g_button_pressed_count = 0;

static void delay (void)
{
    // this will introduce ~200ms  delay when SYSCLK is 16MHZ (RC internal for example)
    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

static void Led_Delay(void) {
	int i;
    for (i = 0; i < 100000; i++);
}

//we write the application here
int main(void)
{

    GPIO_Handle_t Gpioled,GPIOBtn;

   // memset is a standard library function or API in order to intialize every member element of structure to 0
	 // memset(address of the local variable, set the memory to (0 or 1 or whatever) , sizeof (local variable);
	  memset(&Gpioled,0,sizeof(Gpioled));
	  memset(&GPIOBtn,0,sizeof(GPIOBtn));

    //this is led gpio configuration

    Gpioled.pGPIOx=GPIOD; //GPIO base address

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; // wa can't use the debugging pins (p269 in RF_M) as GPIO
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

    GPIOBtn.pGPIOx=GPIOA; //GPIO base address

    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;       //an external Button
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; //we can use PU if we want , or put a external pull up 22k
    GPIO_Init(&GPIOBtn);

    GPIO_WriteToOutputPin(GPIOD,GPIO_PIN_NO_12,GPIO_PIN_RESET);

    //IRQ configuration
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0,ENABLE);
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0,NVIC_IRQ_PRI15);

	printf("\n Waiting for Button to be pressed !\n");

    while(1);

    return 0;
}

//we can get the ISR name from the startup file in the Vector Table
 void EXTI0_IRQHandler(void)
{
    // wait until the debouncing of button over cuz this ISR will excute few times before getting stable
	delay(); //200ms

	// Make this flag SET . if button pressed
	g_button_pressed = 1;

	if(g_button_pressed){

		g_button_pressed_count++;
		printf("\n The Button is pressed : %lu !!\n",g_button_pressed_count);
		g_button_pressed = 0;

		for(int i=12 ;i<=15 ;i++){
			Led_Delay();
			GPIO_ToggleOutputPin(GPIOD, i);
			Led_Delay();
		}
	}

	static int counter = 1;
	printf("\n The EXTI0 Interrupt has been executed : %d !!\n", counter);
	counter++;

    //call the driver supplied GPIO interrupt handling API to clear PR register of EXTI0
    GPIO_IRQHandling(GPIO_PIN_NO_0);
}


