################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2_main.c \
../Timer0.c \
../buzzer.c \
../dcmotor.c \
../external_eeprom.c \
../gpio.c \
../twi.c \
../uart.c 

OBJS += \
./MC2_main.o \
./Timer0.o \
./buzzer.o \
./dcmotor.o \
./external_eeprom.o \
./gpio.o \
./twi.o \
./uart.o 

C_DEPS += \
./MC2_main.d \
./Timer0.d \
./buzzer.d \
./dcmotor.d \
./external_eeprom.d \
./gpio.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


