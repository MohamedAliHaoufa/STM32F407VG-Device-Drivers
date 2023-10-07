/*
 * @file 19keypad_interfacing_LCD.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../drivers/Inc/stm32f407xx.h"
#include "../bsp/lcd.h"

#define SYSTICK_TIM_CLK		16000000UL // 16MHZ (Prescaler is 1 by default) = source clock

/* Enable this macro if you want to test RTC on LCD or comment it if you want to test with print-f */
#define PRINT_LCD

char* Keypad[4][4] = {
    {"Number: 1", "Number: 2", "Number: 3", "Character: A"},
    {"Number: 4", "Number: 5", "Number: 6", "Character: B"},
    {"Number: 7", "Number: 8", "Number: 9", "Character: C"},
    {"Character: *", "Number: 0", "Character: #", "Character: D"}
};

// global shared variables
GPIO_Handle_t Gpioled,GPIOABtn;

static void mdelay(uint32_t cnt){
	for(uint32_t i ; i < (cnt*1000); i++);
}

// Function to get the key at a specific row and column
char* getKey(uint8_t row, uint8_t col) {
    return Keypad[row][col];
}

void delay (void)
{
	// Processor running with 16MHZ of internal RC oscillator
	// let's assume 1 instruction takes 1 clock cycle
	// 1 ins = 0.0625 micro-seconds
	// the loop takes 7 ins = 7*0.0625 = 0.5 micro-seconds
	// 0.5 micro-seconds  ---> 1 iteration of the for loop
	// 1000 micro-seconds (1ms) --- > 2000 iterations
	// 150ms ---> 150 * 2000 = 300000
    for( uint32_t i = 0 ; i < 300000 ; i++);
}

void Keypad_GPIO_init(void){

    //this is the Keypad rows GPIO configuration *********************************************************************

    Gpioled.pGPIOx=GPIOB; //GPIO base address
    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&Gpioled);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&Gpioled);

    //this is The Keypad columns GPIO configuration ******************************************************************

    GPIOABtn.pGPIOx=GPIOB; //GPIO base address
    GPIOABtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIOABtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOABtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOABtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; //there is a pull down available in the shematic of the Button
    GPIO_Init(&GPIOABtn);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&GPIOABtn);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(&GPIOABtn);

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
    GPIO_Init(&GPIOABtn);

    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_SET);
}

//we write the application here
int main(void)
{
#ifndef PRINT_LCD
	printf("Keypad Test...\n");
#else
	lcd_init();

	lcd_print_string("Keypad Test...");

	mdelay(2000); // 2 seconds

	lcd_display_clear();
	lcd_display_return_home();
#endif

	// initialize the Keypad GPIO Pins for Interfacing
	Keypad_GPIO_init();

	while(1){

		lcd_display_clear();
		lcd_display_return_home();

		// Clear All the Rows
		for(uint16_t i=0 ;i<=3 ;i++){
		    GPIO_WriteToOutputPin(GPIOB,i,GPIO_PIN_SET);
		}

	    //**********************************************************************************
	    // make R1 LOW(PD0)
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_RESET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("1\n");
#else
	    	lcd_print_string(getKey(0,0));
#endif
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("2\n");
#else
	    	lcd_print_string(getKey(0,1));
#endif
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("3\n");
#else
	    	lcd_print_string(getKey(0,2));
#endif
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("A\n");
#else
	    	lcd_print_string(getKey(0,3));
#endif
	    }

	    //**********************************************************************************
		lcd_set_cursor(2, 1);

	    // make R2 LOW(PD1), and make R1(PD0) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("4\n");
#else
	    	lcd_print_string(getKey(1,0));
#endif
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("5\n");
#else
	    	lcd_print_string(getKey(1,1));
#endif
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("6\n");
#else
	    	lcd_print_string(getKey(1,2));
#endif
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("B\n");
#else
	    	lcd_print_string(getKey(1,3));
#endif
	    }

	    //**********************************************************************************
		lcd_display_clear();
		lcd_display_return_home();

	    // make R3 LOW(PD2), and make R2(PD1) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("7\n");
#else
	    	lcd_print_string(getKey(2,0));
#endif
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("8\n");
#else
	    	lcd_print_string(getKey(2,1));
#endif
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("9\n");
#else
	    	lcd_print_string(getKey(2,2));
#endif
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("C\n");
#else
	    	lcd_print_string(getKey(2,3));
#endif
	    }

	    //**********************************************************************************
		lcd_set_cursor(2, 1);

	    // make R4 LOW(PD3), and make R3(PD2) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("*\n");
#else
	    	lcd_print_string(getKey(3,0));
#endif
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("0\n");
#else
	    	lcd_print_string(getKey(3,1));
#endif
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("#\n");
#else
	    	lcd_print_string(getKey(3,2));
#endif
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
#ifndef PRINT_LCD
	    	printf("D\n");
#else
	    	lcd_print_string(getKey(3,3));
#endif
	    }

	    // make R4(PD3) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_SET);

	}

    return 0;
}


