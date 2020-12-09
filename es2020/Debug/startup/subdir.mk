################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32l073xx.s 

C_SRCS += \
../startup/system_stm32l0xx.c 

OBJS += \
./startup/startup_stm32l073xx.o \
./startup/system_stm32l0xx.o 

C_DEPS += \
./startup/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/Utilities" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/CMSIS/core" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/CMSIS/device" -I"C:/Users/braht/workspace/es2020/include" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/%.o: ../startup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -std=c99 -DSTM32 -DSTM32L0 -DSTM32L073RZTx -DNUCLEO_L073RZ -DDEBUG -DSTM32L073xx -DUSE_HAL_DRIVER -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/Utilities" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/HAL_Driver/Inc/Legacy" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/CMSIS/core" -I"C:/Users/braht/workspace/nucleo-l073rz_hal_lib/CMSIS/device" -I"C:/Users/braht/workspace/es2020/include" -Og -g3 -pedantic -Wall -Wextra -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


