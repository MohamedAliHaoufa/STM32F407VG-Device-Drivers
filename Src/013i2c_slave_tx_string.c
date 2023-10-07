/**
 * @file 013i2c_slave_tx_string.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include<stdio.h>
#include<string.h>
#include "../drivers/Inc/stm32f407xx.h"


void I2C1_EV_IRQHandler(void); // !! prototype maybe not nedded since NVIC table maybe prototyped the func somewhere else and call this one since the other one is weak in the start up file
void I2C1_ER_IRQHandler(void); // !! prototype maybe not nedded since NVIC table maybe prototyped the func somewhere else and call this one since the other one is weak in the start up file

#define SLAVE_ADDR  0x68       // change it to 0x66 to make the ACK feilure interrupt and test 
#define MY_ADDR     SLAVE_ADDR // the address of the STM32 slave device 

void I2C1_GPIOInits(void);
void I2C1_Inits (void);
void GPIO_ButtonInit(void);

static void delay (void)
{
    // this will introduce ~200ms  delay when SYSCLK is 16MHZ (RC internal for example)
    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

static I2C_Handle_t I2C1Handle; // global variable

// Tx buffer
static uint8_t Tx_buf[32]  = "STM32 Slave mode testing..";  /*  arduino sketch written by the wire library
		                                                             which has limitaion transfered or received in
		                                                             single transaction and the limit is 32bytes   */
/*
 * PB6 -> SCL
 * PB7 -> SDA
 */
void I2C1_GPIOInits(void)
{
    GPIO_Handle_t I2CPins ;

    I2CPins.pGPIOx = GPIOB ;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN ;
    I2CPins.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_OD ;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU ;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST ;

    //SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6 ;
    GPIO_Init(&I2CPins);

    //SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7 ; /* don't use GPIO_PIN_NO_9 cuz it gives some glitches after every byte will
                                                              be transmit caused by the swim(single wired interface module)onboard circuitry */
    GPIO_Init(&I2CPins);


}

void I2C1_Inits (void)
{

    I2C1Handle.pI2Cx = I2C1 ;
    I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE ;
    I2C1Handle.I2C_Config.I2C_DeviceAdress = MY_ADDR; 	    // in UM10204 file page 17 there is some reserved addresses
    I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2 ; //  Fm mode tlow/thigh = 2
    I2C1Handle.I2C_Config.I2C_SCLspeed = I2C_SC_SPEED_SM ;  // standard mode of serial clock speed up to 100KHZ

    I2C_Init(&I2C1Handle) ;

}

void GPIO_ButtonInit(void)
{
    GPIO_Handle_t Gpioled,GPIOBtn;

    //this is Button gpio configuration

    GPIOBtn.pGPIOx=GPIOA; //GPIOA base address

    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;       //an external Button
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GPIOBtn);



    //this is led gpio configuration

    Gpioled.pGPIOx=GPIOD; //GPIOD base address

    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; // wa can't use the debugging pins (p269 in RF_M) as GPIO
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_PP;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&Gpioled);

}
int main(void) {


    //first:  go to the drivers = the target in keil (right click) ->  debug as -> debug configuration -> startup -> run commands -> write this = monitor arm semihosting enable
    //initialise_monitor_handles();
    printf("Application is running \n"); //the ( \n )  is must


    //GPIO Button init
    GPIO_ButtonInit();

    //i2c pin inits
    I2C1_GPIOInits();

    // i2c peripheral configuration
    I2C1_Inits ();

    // I2C IRQ configurations = required cuz the slave application always in interrupt mode in our design
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV,ENABLE);
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER,ENABLE);

    I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE );

    // enable the i2c peripheral
    I2C_PeripheralControl ( I2C1, ENABLE ) ;

    // ack bit is made 1 after PE = 1
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    while (1) ; 

}

void I2C1_EV_IRQHandler(void) {

    I2C_EV_IRQHandling(&I2C1Handle);
    /*so whenever event happen during the I2C communication the I2C1_EV_IRQHandler will be called and
      there we are actually calling our API in order to decode that event and take the appropriate action */

}

void I2C1_ER_IRQHandler(void) {

    I2C_ER_IRQHandling(&I2C1Handle);
    /*so whenever error event happen during the I2C communication the I2C1_ER_IRQHandler will be called and
    there we are actually calling our API in order to decode that event and take the appropriate action */
}


/*
 * Application callback
 */
void I2C_ApplicationEventCallback( I2C_Handle_t *pI2CHandle, uint8_t AppEv )
{
	// the static variables are kind of global variables .
	// the memory for these variables will not be allocated in the stack but in the global space
	// so even if this fun exits . the memory for these variables will not be deallocated and we can access it from this fun
    // but you cannot access these variables from other fun even though they are in global space because we used "static"
    
	// so static mean private to this function but memory is allocated in global space
	static uint8_t commandcode = 0 ;
    static uint8_t Cnt = 0 ;
	
    if (AppEv == I2C_EV_DATA_REQ) {

        // Master wants some data . slave has to send it
        if (commandcode == 0x51 )
        {
        	// send the length information to the master
        	I2C_SlaveSendData(pI2CHandle->pI2Cx, strlen((char*) Tx_buf) );
        }

        else if (commandcode == 0x52 )
        {
        	// send the data (contents of the Tx_buffer)
        	I2C_SlaveSendData(pI2CHandle->pI2Cx, Tx_buf[Cnt++]) ;
        }

    }

    else if (AppEv == I2C_EV_DATA_RCV) {
        // Master's Data is waiting for the slave to read . slave has to read it
        commandcode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx) ;
    }

    else if (AppEv == I2C_ERROR_AF) {
        // this happens only during slave Txing (transmission)
        // Master has sent the NACK . so slave should understand that master doesn't need more data
		commandcode = 0xFF;   // 0xFF means invalidating the command-code
		Cnt = 0;
    }

    else if (AppEv == I2C_EV_STOP) {
        // this happens only during slave Reception
        // Master has ended the I2C communication with the slave.
    }
}

