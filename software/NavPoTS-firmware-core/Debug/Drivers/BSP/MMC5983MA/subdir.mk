################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/MMC5983MA/MMC5983MA.c 

OBJS += \
./Drivers/BSP/MMC5983MA/MMC5983MA.o 

C_DEPS += \
./Drivers/BSP/MMC5983MA/MMC5983MA.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/MMC5983MA/%.o Drivers/BSP/MMC5983MA/%.su Drivers/BSP/MMC5983MA/%.cyclo: ../Drivers/BSP/MMC5983MA/%.c Drivers/BSP/MMC5983MA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/ASM330LHHXTR -I../Drivers/BSP/H3LIS331DL -I../Drivers/BSP/MMC5983MA -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-MMC5983MA

clean-Drivers-2f-BSP-2f-MMC5983MA:
	-$(RM) ./Drivers/BSP/MMC5983MA/MMC5983MA.cyclo ./Drivers/BSP/MMC5983MA/MMC5983MA.d ./Drivers/BSP/MMC5983MA/MMC5983MA.o ./Drivers/BSP/MMC5983MA/MMC5983MA.su

.PHONY: clean-Drivers-2f-BSP-2f-MMC5983MA

