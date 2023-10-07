/**
 * @file lcd.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and function prototypes for interfacing with an LCD (Liquid Crystal Display).
 * @version 0.1
 * @date 2023-10-07
 *
 * This header file provides definitions for GPIO pins and LCD commands, as well as function prototypes for
 * initializing, controlling, and displaying text on an LCD. It serves as an interface to abstract the low-level
 * hardware interactions required for LCD operation, making it easier to integrate LCD functionality into
 * embedded applications.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LCD_H_
#define LCD_H_

#include "../drivers/Inc/stm32f407xx.h"

/**
 * @defgroup LCD LCD Driver
 * @brief LCD (Liquid Crystal Display) driver for STM32F4xx MCUs.
 * @{
 */

/**
 * @defgroup LCD_MACROS LCD Macros
 * @brief Macros for LCD configuration and settings.
 * @{
 */

/**
 * @defgroup LCD_CONFIGURABLE_ITEMS Application Configurable Items
 * @brief Macros for LCD configuration settings.
 * @{
 */
#define LCD_GPIO_PORT       GPIOD
#define LCD_GPIO_RS         GPIO_PIN_NO_0
#define LCD_GPIO_RW         GPIO_PIN_NO_1
#define LCD_GPIO_EN         GPIO_PIN_NO_2
#define LCD_GPIO_D4         GPIO_PIN_NO_3
#define LCD_GPIO_D5         GPIO_PIN_NO_4
#define LCD_GPIO_D6         GPIO_PIN_NO_5
#define LCD_GPIO_D7         GPIO_PIN_NO_6
/** @} */

/**
 * @defgroup LCD_COMMANDS LCD Commands
 * @brief Macros for LCD command codes.
 * @{
 */
#define LCD_CMD_4DL_2N_5X8F     0x28 // Used to activate 4-bit data length, 2 lines (rows), and 5x8 font size.
#define LCD_CMD_DON_CON         0x0E // Used for: Display ON and Cursor ON.
#define LCD_CMD_DIS_CLEAR       0x01 // Used for: Clearing the Display.
#define LCD_CMD_INCADD          0x06 // Used for the increment of DRAM Address, without shifting the display (0x07 for shift).
#define LCD_CMD_DIS_RETURN_HOME 0x02 // Used for: Cursor shifting back to its original position.
/** @} */

/** @} */ // End of LCD_MACROS group

/**
 * @defgroup LCD_APIS LCD APIs
 * @brief APIs for interfacing with an LCD (Liquid Crystal Display).
 * @{
 */

/**
 * @brief Initialize the LCD module.
 *
 * This function initializes the LCD module and prepares it for use.
 */
void lcd_init(void);

/**
 * @brief Send a command to the LCD.
 *
 * This function sends a command to the LCD module for various control operations.
 *
 * @param[in] cmd The command to be sent.
 */
void lcd_send_command(uint8_t cmd);

/**
 * @brief Print a character on the LCD.
 *
 * This function displays a single character on the LCD.
 *
 * @param[in] data The character to be displayed.
 */
void lcd_print_char(uint8_t data);

/**
 * @brief Print a string on the LCD.
 *
 * This function displays a null-terminated string on the LCD.
 *
 * @param[in] message Pointer to the null-terminated string to be displayed.
 */
void lcd_print_string(char* message);

/**
 * @brief Set the cursor position on the LCD.
 *
 * This function sets the cursor position on the LCD screen.
 *
 * @param[in] row The row (line) where the cursor should be placed (0 or 1).
 * @param[in] column The column where the cursor should be placed (0 to 15).
 */
void lcd_set_cursor(uint8_t row, uint8_t column);

/**
 * @brief Clear the LCD display.
 *
 * This function clears the entire content displayed on the LCD.
 */
void lcd_display_clear(void);

/**
 * @brief Return the cursor to the home position on the LCD.
 *
 * This function returns the cursor to the top-left (home) position on the LCD screen.
 */
void lcd_display_return_home(void);

/** @} */ // End of LCD_APIS group

/** @} */ // End of LCD group

#endif /* LCD_H_ */
