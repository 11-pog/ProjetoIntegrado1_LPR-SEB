################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.c 

OBJS += \
./Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.o 

C_DEPS += \
./Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.o: ../Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/StarCode_O_despertarDaFuncao/FuncoeszinhasDoSirAndery.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

