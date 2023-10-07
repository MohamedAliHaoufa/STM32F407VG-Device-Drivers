/**
 * @file keypad.c
 * @author Mohamed Ali Haoufa
 * @brief Source file containing functions for interfacing with a keypad.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */


#include"keypad.h"

/**
 * @brief Get the key at a specific row and column.
 *
 * This static function retrieves the key at a specified row and column position from the keypad's key mappings.
 *
 * @param[in] row The row index (0 to 3) of the desired key.
 * @param[in] col The column index (0 to 3) of the desired key.
 * @return A pointer to the string representing the key.
 */
static char* getKey(uint8_t row, uint8_t col);

/**
 * @brief Static function to introduce a delay.
 *
 * This function introduces a delay to handle key debounce.
 */
static void delay (void)
{
	// Processor running with 16MHZ of internal RC oscillator
	// let's assume 1 instruction takes 1 clock cycle
	// 1 instruction = 0.0625 micro-seconds
	// the loop takes 7 instruction = 7*0.0625 = 0.5 micro-seconds
	// 0.5 micro-seconds  ---> 1 iteration of the for loop
	// 1000 micro-seconds (1ms) --- > 2000 iterations
	// 150ms ---> 150 * 2000 = 300000
    for( uint32_t i = 0 ; i < 300000 ; i++);
}


/**
 * @brief Keypad key mappings.
 *
 * This 4x4 array defines the key mappings of the keypad.
 */
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
/**
 * @brief Get the key at a specific row and column.
 *
 * This static function retrieves the key at a specified row and column position from the keypad's key mappings.
 *
 * @param[in] row The row index (0 to 3) of the desired key.
 * @param[in] col The column index (0 to 3) of the desired key.
 * @return A pointer to the string representing the key.
 */
static char* getKey(uint8_t row, uint8_t col) {
    return Keypad[row][col];
}

/**
 * @brief Scan and print the pressed key on the keypad.
 *
 * This function scans a specific row of the keypad for keypress and prints the pressed key on an LCD.
 *
 * @param[in] row_number The row number to scan (0 to 3 for a 4x4 keypad).
 * @param[in] row_pin The GPIO pin number connected to the row.
 * @param[in] column_pin The GPIO port connected to the column.
 * @param[in] InputOutput_port Pointer to the GPIO peripheral associated with the keypad.
 */
void Keypad_ScanAndPrint(uint8_t row_number, uint8_t row_pin, uint8_t column_pin, GPIO_RegDef_t* InputOutput_port){

    if(row_number >= 0 || row_number <= 3){

        if( row_number > 0){
        	// make Rrow LOW(PDrow)
            GPIO_WriteToOutputPin(InputOutput_port,row_pin-1,GPIO_PIN_SET);
            GPIO_WriteToOutputPin(InputOutput_port,row_pin,GPIO_PIN_RESET);
        } else {
            GPIO_WriteToOutputPin(InputOutput_port,row_pin,GPIO_PIN_RESET);
        }

        // scan the columns
        // check C1(PD8) low or high, if low means key is pressed
        if( ! GPIO_ReadFromInputPin(InputOutput_port, column_pin++) ){
        	// key is pressed
        	delay();

        	lcd_print_string(getKey(row_number,0));
        }

        // check C2(PD9) low or high, if low means key is pressed
        if( ! GPIO_ReadFromInputPin(InputOutput_port, column_pin++) ){
        	// key is pressed
        	delay();

        	lcd_print_string(getKey(row_number,1));

        }

        // check C3(PD10) low or high, if low means key is pressed
        if( ! GPIO_ReadFromInputPin(InputOutput_port, column_pin++) ){
        	// key is pressed
        	delay();

        	lcd_print_string(getKey(row_number,2));

        }

        // check C4(PD11) low or high, if low means key is pressed
        if( ! GPIO_ReadFromInputPin(InputOutput_port, column_pin) ){
        	// key is pressed
        	delay();
        	lcd_print_string(getKey(row_number,3));

        }
    }
}
