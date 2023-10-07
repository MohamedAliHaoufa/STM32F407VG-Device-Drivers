################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsp/ds1307.c \
../bsp/keypad.c \
../bsp/lcd.c 

OBJS += \
./bsp/ds1307.o \
./bsp/keypad.o \
./bsp/lcd.o 

C_DEPS += \
./bsp/ds1307.d \
./bsp/keypad.d \
./bsp/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
bsp/%.o bsp/%.su bsp/%.cyclo: ../bsp/%.c bsp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -gdwarf-2 -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsp

clean-bsp:
	-$(RM) ./bsp/ds1307.cyclo ./bsp/ds1307.d ./bsp/ds1307.o ./bsp/ds1307.su ./bsp/keypad.cyclo ./bsp/keypad.d ./bsp/keypad.o ./bsp/keypad.su ./bsp/lcd.cyclo ./bsp/lcd.d ./bsp/lcd.o ./bsp/lcd.su

.PHONY: clean-bsp

