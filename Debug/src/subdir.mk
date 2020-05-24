################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display.c \
../src/main.c \
../src/oled.c \
../src/syscalls.c \
../src/system_stm32f0xx.c 

OBJS += \
./src/display.o \
./src/main.o \
./src/oled.o \
./src/syscalls.o \
./src/system_stm32f0xx.o 

C_DEPS += \
./src/display.d \
./src/main.d \
./src/oled.d \
./src/syscalls.d \
./src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F0 -DSTM32F051R8Tx -DSTM32F0DISCOVERY -DDEBUG -DSTM32F051 -DUSE_STDPERIPH_DRIVER -I"C:/Users/mom75/Desktop/SystemWorkbenchProjects/PowerSupply/Utilities" -I"C:/Users/mom75/Desktop/SystemWorkbenchProjects/PowerSupply/StdPeriph_Driver/inc" -I"C:/Users/mom75/Desktop/SystemWorkbenchProjects/PowerSupply/inc" -I"C:/Users/mom75/Desktop/SystemWorkbenchProjects/PowerSupply/CMSIS/device" -I"C:/Users/mom75/Desktop/SystemWorkbenchProjects/PowerSupply/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


