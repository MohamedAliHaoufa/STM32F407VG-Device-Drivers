/*
 * @file 018keypad_interfacing.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../drivers/Inc/stm32f407xx.h"

// global shared variables
GPIO_Handle_t Gpioled,GPIOABtn;

char* Keypad[4][4] = {
    {"Number: 1", "Number: 2", "Number: 3", "Character: A"},
    {"Number: 4", "Number: 5", "Number: 6", "Character: B"},
    {"Number: 7", "Number: 8", "Number: 9", "Character: C"},
    {"Character: *", "Number: 0", "Character: #", "Character: D"}
};
/*
char* Keypad[4][4] = {
    {"1", "2", "3", "A"},
    {"4", "5", "6", "B"},
    {"7", "8", "9", "C"},
    {"*", "0", "#", "D"}
};
*/

// Function to get the key at a specific row and column
char* getKey(int row, int col) {
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
	// initialize the Keypad GPIO Pins for Interfacing
	Keypad_GPIO_init();

	while(1){
	    //**********************************************************************************
		for(int i=0 ;i<=3 ;i++){
		    GPIO_WriteToOutputPin(GPIOB,i,GPIO_PIN_SET);
		}

	    // make R1 LOW(PD0)
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_RESET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
	    	printf("1\n");
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
	    	printf("2\n");
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
	    	printf("3\n");
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
	    	printf("A\n");
	    }

	    //**********************************************************************************

	    // make R2 LOW(PD1), and make R1(PD0) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
	    	printf("4\n");
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
	    	printf("5\n");
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
	    	printf("6\n");
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
	    	printf("B\n");
	    }

	    //**********************************************************************************

	    // make R3 LOW(PD2), and make R2(PD1) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
	    	printf("7\n");
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
	    	printf("8\n");
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
	    	printf("9\n");
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
	    	printf("C\n");
	    }

	    //**********************************************************************************

	    // make R4 LOW(PD3), and make R3(PD2) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_RESET);
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_SET);
	    // scan the columns
	    // check C1(PD8) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_8) ){
	    	// key is pressed
	    	delay();
	    	printf("*\n");
	    }

	    // check C2(PD9) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_9) ){
	    	// key is pressed
	    	delay();
	    	printf("0\n");
	    }

	    // check C3(PD10) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_10) ){
	    	// key is pressed
	    	delay();
	    	printf("#\n");
	    }

	    // check C4(PD11) low or high, if low means key is pressed
	    if( ! GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_11) ){
	    	// key is pressed
	    	delay();
	    	printf("D\n");
	    }

	    // make R4(PD3) High again
	    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_SET);

	}

    return 0;
}

