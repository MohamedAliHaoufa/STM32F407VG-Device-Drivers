/*
 * @file 20keypad_interfacing_LCD.c
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
#include "../bsp/keypad.h"


// global shared variables
GPIO_Handle_t GPIORow,GPIOColumn;

static void mdelay(uint32_t cnt){
	for(uint32_t i ; i < (cnt*1000); i++);
}

void Keypad_GPIO_init(void){

    //this is the Keypad rows GPIO configuration *********************************************************************

	GPIORow.pGPIOx=GPIOB; //GPIO base address
	GPIORow.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIORow.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIORow.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
	GPIORow.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GPIORow.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GPIORow);

    GPIORow.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    GPIO_Init(&GPIORow);

    GPIORow.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&GPIORow);

    GPIORow.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&GPIORow);

    //this is The Keypad columns GPIO configuration ******************************************************************

    GPIOColumn.pGPIOx=GPIOB; //GPIO base address
    GPIOColumn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIOColumn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOColumn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOColumn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; //there is a pull down available in the shematic of the Button
    GPIO_Init(&GPIOColumn);

    GPIOColumn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&GPIOColumn);

    GPIOColumn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
    GPIO_Init(&GPIOColumn);

    GPIOColumn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
    GPIO_Init(&GPIOColumn);

    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_0,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_1,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_2,GPIO_PIN_SET);
    GPIO_WriteToOutputPin(GPIOB,GPIO_PIN_NO_3,GPIO_PIN_SET);
}

//we write the application here
int main(void)
{

	lcd_init();

	lcd_print_string("Keypad Test...");

	mdelay(2000); // 2 seconds

	lcd_display_clear();
	lcd_display_return_home();

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
		Keypad_ScanAndPrint(0, GPIO_PIN_NO_0, GPIO_PIN_NO_8, GPIOB);

	    //**********************************************************************************
		lcd_set_cursor(2, 1);

	    // make R2 LOW(PD1), and make R1(PD0) High again
		Keypad_ScanAndPrint(1, GPIO_PIN_NO_1, GPIO_PIN_NO_8, GPIOB);

	    //**********************************************************************************
		lcd_display_clear();
		lcd_display_return_home();

	    // make R3 LOW(PD2), and make R2(PD1) High again
		Keypad_ScanAndPrint(2, GPIO_PIN_NO_2, GPIO_PIN_NO_8, GPIOB);

	    //**********************************************************************************
		lcd_set_cursor(2, 1);

	    // make R4 LOW(PD3), and make R3(PD2) High again
		Keypad_ScanAndPrint(3, GPIO_PIN_NO_3, GPIO_PIN_NO_8, GPIOB);

	}
    return 0;
}



