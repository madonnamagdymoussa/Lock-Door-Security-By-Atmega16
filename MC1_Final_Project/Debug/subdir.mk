################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART.c \
../UART_config.c \
../keypad.c \
../lcd.c \
../main.c \
../mdio.c \
../open_door.c \
../timer.c \
../timer_config.c 

OBJS += \
./UART.o \
./UART_config.o \
./keypad.o \
./lcd.o \
./main.o \
./mdio.o \
./open_door.o \
./timer.o \
./timer_config.o 

C_DEPS += \
./UART.d \
./UART_config.d \
./keypad.d \
./lcd.d \
./main.d \
./mdio.d \
./open_door.d \
./timer.d \
./timer_config.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


