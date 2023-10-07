/**
 * @file lcd.c
 * @author Mohamed Ali Haoufa
 * @brief This file contains the driver implementation for controlling an LCD (Liquid Crystal Display).
 * @version 0.1
 * @date 2023-10-07
 *
 * This driver provides functions to initialize, control, and display text on an LCD using a 4-bit parallel
 * data transmission method. It includes functions for sending commands, printing characters and strings,
 * and clearing the display. The driver abstracts the hardware interactions, making it easy to interface
 * with an LCD in embedded applications.
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "lcd.h"

// LCD Helper Functions :
static void write_4_bits(uint8_t value);
static void mdelay(uint32_t value);
static void udelay(uint32_t value);
static void lcd_enable(void);

/**
 * @brief Send a command to the LCD.
 *
 * This function sends a command to the LCD module for various control operations.
 *
 * @param[in] cmd The command to be sent.
 */
void lcd_send_command (uint8_t cmd){

	/* RS = 0 , For LCD command */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	/* R/nW = 0 , Writing to the LCD */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write_4_bits(cmd >> 4);
	write_4_bits(cmd & 0x0F);
}


/**
 * @brief Print a character on the LCD.
 *
 * This function displays a single character on the LCD.
 * Here we used 4 bit parallel data transmission.
 * First higher nibble of the data will be sent on to the data lines D4, D5, D6, D7
 * Then lower nibble of the data will be set on to the data lines D4, D5, D6, D7
 *
 * @param[in] data The character to be displayed.
 */
void lcd_print_char(uint8_t data){

	/* RS = 1 , For LCD user data */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_SET);

	/* R/nW = 0 , Writing to the LCD */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write_4_bits(data >> 4); /* send the Higher nibble */
	write_4_bits(data & 0x0F); /* send the Lower nibble */
}

/**
 * @brief Print a string on the LCD.
 *
 * This function displays a null-terminated string on the LCD.
 *
 * @param[in] message Pointer to the null-terminated string to be displayed.
 */
void lcd_print_string(char* message){
	do {
		lcd_print_char((uint8_t)*message++);
	}
	while(*message != '\0');
}

/**
 * @brief Initialize the LCD module.
 *
 * This function initializes the LCD module and prepares it for use.
 */
void lcd_init(void){

	// Configure the GPIO pins which are used for LCD connections
	GPIO_Handle_t lcd_signal;
	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
	lcd_signal.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);

	// the LCD initialization (refer to "initializing by instruction" section in Data-sheet)

	mdelay(40); // 40 milliseconds delay

	/* RS = 0 , For LCD command */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	/* R/nW = 0 , Writing to the LCD */
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	write_4_bits(0x3); // 0 0 1 1

	mdelay(5); // 5 milliseconds delay

	write_4_bits(0x3); // 0 0 1 1

	udelay(150); // 150 microseconds delay

	write_4_bits(0x3); // 0 0 1 1

	write_4_bits(0x2); // 0 0 1 0

	// refer to p.24 in Data-sheet for command codes

	// function set command
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);

	// Display ON and Cursor ON
	lcd_send_command(LCD_CMD_DON_CON);

	// Display clear
	lcd_display_clear();

	// entry mode set
	lcd_send_command(LCD_CMD_INCADD);


}

/**
 * @brief Writes a 4-bit value to the LCD data pins.
 *
 * This function sets the values of the 4 data pins (D4 to D7) based on the bits of the input value.
 * writes 4 bits of data /command on to D4, D5, D6, D7 lines
 *
 * @param[in] value The 4-bit value to be written to the data pins.
 */
static void write_4_bits(uint8_t value){

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, ((value >> 0) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, ((value >> 1) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, ((value >> 2) & 0x1) );
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, ((value >> 3) & 0x1) );

	lcd_enable();
}

/**
 * @brief Delays the program execution by a specified number of milliseconds (ms).
 *
 * This function provides a millisecond delay using a busy-wait loop.
 *
 * @param[in] cnt The number of milliseconds to delay.
 */
static void mdelay(uint32_t cnt){
	for(uint32_t i ; i < (cnt*1000); i++);
}

/**
 * @brief Delays the program execution by a specified number of microseconds (us).
 *
 * This function provides a microsecond delay using a busy-wait loop.
 *
 * @param[in] cnt The number of microseconds to delay.
 */
static void udelay(uint32_t cnt){
	for(uint32_t i ; i < (cnt*1); i++);
}

/**
 * @brief Enables the LCD display by toggling the enable (EN) pin.
 *
 * This function activates the LCD display by setting the EN (enable) pin high for a brief duration and then
 * lowering it. It introduces a delay to ensure proper execution.
 */
static void lcd_enable(void){

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100); // execution time > 37 micro seconds
}


/**
 * @brief Set the cursor position on the LCD.
 *
 * This function sets the cursor position on the LCD screen.
 * Set Lcd to a specified location given by row and column information (page 11 in data-sheet)
 * Row Number (1 to 2)
 * Column Number (1 to 16) Assuming a 2 X 16 characters display
 *
 * @param[in] row The row (line) where the cursor should be placed (0 or 1).
 * @param[in] column The column where the cursor should be placed (0 to 15).
 */
void lcd_set_cursor(uint8_t row, uint8_t column)
{
/**

 */
  column--;
  switch (row)
  {
    case 1:
      /* Set cursor to 1st row address and add index*/
      lcd_send_command((column |= 0x80));
      break;
    case 2:
      /* Set cursor to 2nd row address and add index*/
        lcd_send_command((column |= 0xC0));
      break;
    default:
      break;
  }
}

/**
 * @brief Clear the LCD display.
 *
 * This function clears the entire content displayed on the LCD.
 */
void lcd_display_clear(void){

	// Display clear
	lcd_send_command(LCD_CMD_DIS_CLEAR);

	// wait 2 milliseconds delay. check the page 24 of data-sheet, display clear command execution wait time is around 2ms
	mdelay(2);
}

/**
 * @brief Return the cursor to the home position on the LCD.
 *
 * This function returns the cursor to the top-left (home) position on the LCD screen.
 */
void lcd_display_return_home(void){

	/* Cursor returns to home position */
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);

	// wait 2 milliseconds delay. check the page 24 of data-sheet, return home command execution wait time is around 2ms
	mdelay(2);
}


