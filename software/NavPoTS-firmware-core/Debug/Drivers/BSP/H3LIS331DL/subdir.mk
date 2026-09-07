################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/H3LIS331DL/H3LIS331DL.c 

OBJS += \
./Drivers/BSP/H3LIS331DL/H3LIS331DL.o 

C_DEPS += \
./Drivers/BSP/H3LIS331DL/H3LIS331DL.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/H3LIS331DL/%.o Drivers/BSP/H3LIS331DL/%.su Drivers/BSP/H3LIS331DL/%.cyclo: ../Drivers/BSP/H3LIS331DL/%.c Drivers/BSP/H3LIS331DL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/ASM330LHHXTR -I../Drivers/BSP/H3LIS331DL -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-H3LIS331DL

clean-Drivers-2f-BSP-2f-H3LIS331DL:
	-$(RM) ./Drivers/BSP/H3LIS331DL/H3LIS331DL.cyclo ./Drivers/BSP/H3LIS331DL/H3LIS331DL.d ./Drivers/BSP/H3LIS331DL/H3LIS331DL.o ./Drivers/BSP/H3LIS331DL/H3LIS331DL.su

.PHONY: clean-Drivers-2f-BSP-2f-H3LIS331DL

