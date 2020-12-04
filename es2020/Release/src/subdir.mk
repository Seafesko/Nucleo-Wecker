################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/clock.c \
../src/i2c.c \
../src/lcd.c \
../src/main.c \
../src/systick.c 

OBJS += \
./src/clock.o \
./src/i2c.o \
./src/lcd.o \
./src/main.o \
./src/systick.o 

C_DEPS += \
./src/clock.d \
./src/i2c.d \
./src/lcd.d \
./src/main.d \
./src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32 -DSTM32L0 -DSTM32L073RZTx -DNUCLEO_L073RZ -DSTM32L073xx -DUSE_HAL_DRIVER -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib" -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib/Utilities" -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc" -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc/Legacy" -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib/CMSIS/core" -I"/home/felix/Workbench/workspace/nucleo-l073rz_hal_lib/CMSIS/device" -I"/home/felix/Workbench/workspace/es2020/include" -Os -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


