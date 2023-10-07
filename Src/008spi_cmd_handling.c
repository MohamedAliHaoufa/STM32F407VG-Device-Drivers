/**
 * @file 008spi_cmd_handling.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "../drivers/Inc/stm32f407xx.h"

#define CMD_LED_CTRL    0x50 /**< CMD to control an LED. */
#define CMD_SENSOR_READ 0x51 /**< CMD to read a sensor. */
#define CMD_LED_READ    0x52 /**< CMD to read the LED state. */
#define CMD_PRINT       0x53 /**< CMD to print data. */
#define CMD_ID_READ     0x54 /**< CMD to read an ID. */

#define LED_ON   1 /**< Represents the LED ON state. */
#define LED_OFF  0 /**< Represents the LED OFF state. */
#define LED_PIN  9 /**< connected the LED to the Arduino pin number 9. */

#define ANALOG_PIN0 0 /**< Represents analog pin 0. */
#define ANALOG_PIN1 1 /**< Represents analog pin 1. */
#define ANALOG_PIN2 2 /**< Represents analog pin 2. */
#define ANALOG_PIN3 3 /**< Represents analog pin 3. */
#define ANALOG_PIN4 4 /**< Represents analog pin 4. */

static void delay (void)
{

    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

/*
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * PB13 --> SPI2_SCLK
 * PB12 --> SPI2_NSS
 * ALT Function mode : 5
 */
void SPI2_GPIOInits(void){
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	// NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);
}

void SPI2_Inits(void){

	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx=SPI2;
	SPI2Handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FULL_DUPLEX;
	SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI2Handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_Config.SPI_SSM = SPI_SSM_DI; // Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2Handle);

}

void GPIO_ButtonInit(void){
    //this is Button gpio configuration
    GPIO_Handle_t GPIOABtn;

    GPIOABtn.pGPIOx=GPIOA; //GPIO base address

    GPIOABtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOABtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOABtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOABtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; //there is a pull down available in the shematic of the Button

    GPIO_Init(&GPIOABtn);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte){

	if(ackbyte == 0xF5){
		// it's is ACK
		return 1;
	}
	// it's NACK
	return 0;
}

int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	printf("Application is running\n");

	GPIO_ButtonInit();

	// This function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	// This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	printf("SPI Init done\n");

	/*
	 * making SSOE = 1 does NSS output enable
	 * The NSS pin is automatically managed by the hardware
	 * i.e when SPE=1, NSS will be pulled to low
	 * and NSS pin will be high when SPE=0
	 */
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1){

/**********************************************************************************************
  1. CMD_LED_CTRL		<pin no(1)>		<value(1)>
***********************************************************************************************/
		// wait till the button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );

		// to avoid de-bouncing related issues 200ms of delay
		delay();

		// Enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		uint8_t commmandcode = CMD_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];
		SPI_SendData(SPI2, &commmandcode, 1);
		// do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		// send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		// read the ACK byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		// Verify if the ACK byte is valid or not
		if ( SPI_VerifyResponse(ackbyte) ) {
			args[0]= LED_PIN;
			args[1]= LED_ON;
			// Send arguments
			SPI_SendData(SPI2, args, 2); // 2 bytes
			printf("COMMAND_LED_CTRL Executed \n");
		}

/**********************************************************************************************
  2. CMD_SENSOR_READ		<analog pin number(1)>
***********************************************************************************************/

		// wait till the button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		// to avoid de-bouncing related issues 200ms of delay
		delay();
		commmandcode = CMD_SENSOR_READ;
		SPI_SendData(SPI2, &commmandcode, 1);
		// do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		// send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		// read the ACK byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		// Verify if the ACK byte is valid or not
		if ( SPI_VerifyResponse(ackbyte) ) {
			args[0]= ANALOG_PIN0;
			// Send arguments
			SPI_SendData(SPI2, args, 1); // 1 bytes

			// do dummy read to clear off the RXNE
			SPI_ReceiveData(SPI2, &dummy_read, 1);
			// insert some delay till the slave become ready with data
			delay();
			// send some dummy bits (1byte) to fetch the response from the slave
			SPI_SendData(SPI2, &dummy_write, 1);
			// read the analog data from arduino
			uint8_t analog_read;
			SPI_ReceiveData(SPI2, &analog_read, 1);
			printf("CMD_SENSOR_READ : %d \n",analog_read);
		}

/**********************************************************************************************
  3. CMD_LED_READ		<pin no(1)>
***********************************************************************************************/

		// wait till the button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		// to avoid de-bouncing related issues 200ms of delay
		delay();
		commmandcode = CMD_LED_READ;
		SPI_SendData(SPI2, &commmandcode, 1);
		// do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		// send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		// read the ACK byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		// Verify if the ACK byte is valid or not
		if ( SPI_VerifyResponse(ackbyte) ) {
			args[0]= LED_PIN;
			// Send arguments
			SPI_SendData(SPI2, args, 1); // 1 bytes

			// do dummy read to clear off the RXNE
			SPI_ReceiveData(SPI2, &dummy_read, 1);
			// insert some delay till the slave become ready with data
			delay();
			// send some dummy bits (1byte) to fetch the response from the slave
			SPI_SendData(SPI2, &dummy_write, 1);
			// read the analog data from arduino
			uint8_t led_status;
			SPI_ReceiveData(SPI2, &led_status, 1);
			printf("CMD_LED_READ : %d \n",led_status);
		}

/**********************************************************************************************
  4. CMD_PRINT		<len>		<message>
***********************************************************************************************/

		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		// to avoid de-bouncing related issues 200ms of delay
		delay();
		commmandcode = CMD_PRINT;
		SPI_SendData(SPI2, &commmandcode, 1);
		// do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		// send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		// read the ACK byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);
		// Verify if the ACK byte is valid or not
		if ( SPI_VerifyResponse(ackbyte) ) {
			uint8_t message[] = "Hello ! How are you ??";
			args[0] = strlen((char*)message);
			// Send arguments
			SPI_SendData(SPI2, args, 1); //sending length

			//do dummy read to clear off the RXNE
			SPI_ReceiveData(SPI2,&dummy_read,1);

			delay();

			//send message
			for(int i = 0 ; i < args[0] ; i++){
				SPI_SendData(SPI2,&message[i],1);
				SPI_ReceiveData(SPI2,&dummy_read,1); // clear off the RXNE each time u send
			}

			printf("COMMAND_PRINT Executed \n");
		}


/**********************************************************************************************
  5. CMD_ID_READ	<no arguments>
***********************************************************************************************/

		// wait till the button is pressed
		while( ! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) );
		commmandcode = CMD_ID_READ;
		SPI_SendData(SPI2, &commmandcode, 1);
		// do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);
		// send some dummy bits (1byte) to fetch the response from the slave
		SPI_SendData(SPI2, &dummy_write, 1);
		// read the ACK byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		uint8_t id[11];
		uint32_t i = 0;
		if( SPI_VerifyResponse(ackbyte))
		{
			//read 10 bytes id from the slave
			for(  i = 0 ; i < 10 ; i++)
			{
				//send dummy byte to fetch data from slave
				SPI_SendData(SPI2,&dummy_write,1);
		        //receive the id data from arduino
				SPI_ReceiveData(SPI2,&id[i],1);
			}

			id[10] = '\0';

			printf("COMMAND_ID : %s \n",id); // expect the id : ARDUINOUNO

		}

		// let confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG) );

		// Disable the SPI2 peripheral after transmission ends
		SPI_PeripheralControl(SPI2, DISABLE);
		printf("SPI Communication Closed\n");
	}


    return 0;
}
