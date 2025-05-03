################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dmm_Volt.c \
../FinalFullProject.c \
../adc.c \
../dmmAmmeter.c \
../dmm_Ohmmeter.c \
../gpio.c \
../keypad.c \
../lcd.c 

OBJS += \
./Dmm_Volt.o \
./FinalFullProject.o \
./adc.o \
./dmmAmmeter.o \
./dmm_Ohmmeter.o \
./gpio.o \
./keypad.o \
./lcd.o 

C_DEPS += \
./Dmm_Volt.d \
./FinalFullProject.d \
./adc.d \
./dmmAmmeter.d \
./dmm_Ohmmeter.d \
./gpio.d \
./keypad.d \
./lcd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


