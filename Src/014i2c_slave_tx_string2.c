/**
 * @file 014i2c_slave_tx_string2.c
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

static uint32_t data_len = 0;

// Tx buffer (very large message)
static uint8_t Tx_buf[] = "HiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHiHi...123";

static uint8_t CommandCode = 0 ;

static void delay (void)
{
    // this will introduce ~200ms  delay when SYSCLK is 16MHZ (RC internal for example)
    for( uint32_t i = 0 ; i < 500000/2 ; i++);

}

void I2C1_GPIOInits(void);
void I2C1_Inits (void);
void GPIO_ButtonInit(void);


static I2C_Handle_t I2C1Handle; // global variable

//rcv buffer
//static uint8_t rcv_buf[32];

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */
void I2C1_GPIOInits(void)
{
    GPIO_Handle_t I2CPins ;

    I2CPins.pGPIOx = GPIOB;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinPinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

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
    GPIO_Handle_t GPIOBtn;

    //this is Button gpio configuration

    GPIOBtn.pGPIOx=GPIOA; //GPIOA base address

    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;       //an external Button
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    GPIO_Init(&GPIOBtn);


}

int main(void) {

    //first:  go to the drivers = the target in keil (right click) ->  debug as -> debug configuration -> startup -> run commands -> write this = monitor arm semihosting enable
    //initialise_monitor_handles();
    printf("Application is running \n"); //the ( \n )  is must


    data_len = strlen((char*)Tx_buf); // store the length of Data

    //GPIO Button init
    GPIO_ButtonInit();

    //i2c pin inits
    I2C1_GPIOInits();

    // i2c peripheral configuration
    I2C1_Inits ();


    // enable the i2c peripheral
    I2C_PeripheralControl ( I2C1, ENABLE ) ;

    // ACK bit is made 1 after PE = 1
    I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

    // I2C IRQ configurations = required because the slave application always in interrupt mode in our design
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV,ENABLE);
    I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER,ENABLE);

    I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

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
    // the static variabale are kind of global variables .
    //the memory for these varibales will not be allocated in the stack but in the global space
    // so even if this fun exits . the memory for these variables will not be deallocated and we can access it from this fun
    // but you cannot access these variables from other fun even tho they are in global space cuz we used "static"

    // so static mean private to this function but memory is allocated in global space
    static uint32_t w_ptr = 0;

    static uint8_t Cnt = 0 ;

    if (AppEv == I2C_EV_DATA_REQ) {

        // Master is requesting for the data . slave has to send it
        if (CommandCode == 0x51 )
        {
            //Here we are sending 4 bytes = 32bit of length information
            I2C_SlaveSendData(pI2CHandle->pI2Cx,((data_len >> ((Cnt % 4) * 8)) & 0xFF)); // he send 1byte each shift
            Cnt++;

        }

        else if (CommandCode == 0x52 )
        {
            //sending Tx_buf contents indexed by w_ptr variable
            I2C_SlaveSendData(pI2CHandle->pI2Cx,Tx_buf[w_ptr++]);
        }
    }

    else if (AppEv == I2C_EV_DATA_RCV) {
        // Master has sent command code . read it
        CommandCode = I2C_SlaveReceiveData(pI2CHandle->pI2Cx) ;
    }

    else if (AppEv == I2C_ERROR_AF) {
        // This happens only during slave transmitting data to master (transmission)
        // Master has sent the NACK . so slave should understand that master doesn't need more data
        //slave concludes end of Tx

        //if the current active code is 0x52 then don't invalidate
        if(! (CommandCode == 0x52)){
            CommandCode = 0XFF;
        }

        //reset the Cnt variable because it's the end of transmission
        Cnt = 0;

        //Slave concludes, it sent all the bytes when w_ptr reaches data_len
        if(w_ptr >= (data_len))
        {
            w_ptr=0;
            CommandCode = 0xff;
        }
    }

    else if (AppEv == I2C_EV_STOP) {
        // This will happen only during slave Reception
        // Master has ended the I2C communication with the slave.
        // slave concludes end of Rx

        Cnt = 0;
    }

    (void) pI2CHandle ;
}
