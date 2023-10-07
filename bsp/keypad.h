/**
 * @file keypad.h
 * @brief Header file containing definitions and function prototypes for interfacing with a keypad.
 * @version 0.1
 * @date 2023-10-07
 * @author Mohamed Ali Haoufa
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../drivers/Inc/stm32f407xx.h"
#include "lcd.h"

/**
 * @defgroup KEYPAD KEYPAD Driver
 * @brief Driver for interfacing with a keypad.
 * @{
 */

/**
 * @brief Scan and print the pressed key on the keypad.
 *
 * This function scans a specific row of the keypad for keypress and prints the pressed key on an LCD.
 *
 * @param[in] row_number The row number to scan (0 to 3 for a 4x4 keypad).
 * @param[in] row_pin The GPIO pin number connected to the row.
 * @param[in] column_pin The GPIO port connected to the column.
 * @param[in] pGPIOx Pointer to the GPIO peripheral associated with the keypad.
 */
void Keypad_ScanAndPrint(uint8_t row_number, uint8_t row_pin, uint8_t column_pin, GPIO_RegDef_t *pGPIOx);

/** @} */ // End of KEYPAD group

#endif /* KEYPAD_H_ */
