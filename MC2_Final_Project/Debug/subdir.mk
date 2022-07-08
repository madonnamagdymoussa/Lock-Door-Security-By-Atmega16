################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART.c \
../UART_config.c \
../buzzer.c \
../external_eeprom.c \
../i2c.c \
../main.c \
../mdio.c \
../motors.c \
../timer.c \
../timer_config.c 

OBJS += \
./UART.o \
./UART_config.o \
./buzzer.o \
./external_eeprom.o \
./i2c.o \
./main.o \
./mdio.o \
./motors.o \
./timer.o \
./timer_config.o 

C_DEPS += \
./UART.d \
./UART_config.d \
./buzzer.d \
./external_eeprom.d \
./i2c.d \
./main.d \
./mdio.d \
./motors.d \
./timer.d \
./timer_config.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


