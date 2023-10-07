/**
 * @file 012i2c_master_rx_testingIT.c
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

// use the semihosting since you don't have the logic-Analyzer
// to enable and implement the semi-hosting to print the data in the consol ( in eclipse only )
//extern void initialise_monitor_handles();

// a Global Flag variables
static uint8_t rxComplt = RESET;
static uint8_t AckFailure = RESET;

void I2C1_EV_IRQHandler(void); // !! prototype maybe not nedded since NVIC table maybe prototyped the func somewhere else and call this one since the other one is weak in the start up file
void I2C1_ER_IRQHandler(void); // !! prototype maybe not nedded since NVIC table maybe prototyped the func somewhere else and call this one since the other one is weak in the start up file

#define MY_ADDR     0x61
#define SLAVE_ADDR  0x68 // change it to 0x66 to make the ACK feilure interrupt and test 

void I2C1_GPIOInits(void);
void I2C1_Inits (void);
void GPIO_ButtonInit(void);

static void delay (void)
{
    // this will introduce ~200ms  delay when SYSCLK is 16MHZ (RC internal for example)
    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

static I2C_Handle_t I2C1Handle; // global variable

// rcv buffer
static uint8_t rcv_buf[32]; // the size of the received data is 32 bytes

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

    uint8_t commandcode ;
    uint8_t len ;

    //GPIO Button init
    GPIO_ButtonInit();

    //i2c pin inits
    I2C1_GPIOInits();

    // i2c peripheral configuration
    I2C1_Inits ();

    // I2C IRQ configurations
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV,ENABLE);
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER,ENABLE);

    // enable the i2c peripheral
    I2C_PeripheralControl ( I2C1, ENABLE ) ;

    // ack bit is made 1 after PE = 1
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);


    while(1) {

        // wait till button is pressed
        while (! GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));

        // to avoid button de-bouncing related issues 200ms of delay
        delay();

        commandcode = 0x51 ;
        while(I2C_MasterSendDataIT( &I2C1Handle, &commandcode, 1, SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY ) ;
        while(I2C_MasterReceiveDataIT( &I2C1Handle, &len, 1, SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY ) ;

        commandcode = 0x52 ;
        while(I2C_MasterSendDataIT( &I2C1Handle, &commandcode, 1, SLAVE_ADDR,I2C_ENABLE_SR) != I2C_READY ) ;
        while(I2C_MasterReceiveDataIT( &I2C1Handle, rcv_buf, len, SLAVE_ADDR,I2C_DISABLE_SR) != I2C_READY ) ;   // we disable the repeated start only in the last Read transaction to end the I2C transaction


        rxComplt = RESET; // for the first I2C_MasterReceiveDataIT function that make rx-complet to 1 so we need to reset it

        // wait till rx-completes
        while(rxComplt != SET)
        {

        }

        // in the transmission we don't receive the null character but since we used %s we need to add the null char
        rcv_buf[len+1] = '\0';
        printf( "Data : %s\n", rcv_buf ) ; // to print the received data by semi-hosting in the console
        rxComplt = RESET;
    }


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
    if ( AppEv == I2C_EV_TX_CMPLT) {

        printf(" Tx is completed \n");

    }
    else if (AppEv == I2C_EV_RX_CMPLT) {

        printf(" Rx is completed \n");
        rxComplt = SET ;
    }

    else if (AppEv == I2C_ERROR_AF) {

        printf("ERROR : ACK Failure! \n");
        AckFailure = SET;

        // in master ACK failure happens when slave fails to send ACK for the byte sent from the master
        // ( of course in case our device is in master mode )
        // we can conclude from it : the slave device might have removed from the bus / or gone bad / or not want more data

        I2C_CloseSendData(pI2CHandle); // to stop sending data

        // generate the stop condition to release the bus
        I2C_GenerateStopCondition(I2C1);

        // hang in infinite loop
        while(1); // to prevent the upcoming codes from executing

    }
    /*
    else if (AppEv == I2C_ERROR_ARLO) {
    }
    else if (AppEv == I2C_ERROR_BERR) {
    }
    else if (AppEv == I2C_ERROR_OVR) {
    }
    else if (AppEv == I2C_ERROR_TIMEOUT) {
    }
    */

}

