################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylib/LCD1602/LCD1602.c 

OBJS += \
./mylib/LCD1602/LCD1602.o 

C_DEPS += \
./mylib/LCD1602/LCD1602.d 


# Each subdirectory must supply rules for building sources it contributes
mylib/LCD1602/%.o mylib/LCD1602/%.su mylib/LCD1602/%.cyclo: ../mylib/LCD1602/%.c mylib/LCD1602/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/LCD1602" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/OLED_SH1106" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/Sensor_temperature" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/4 digit 7 segment" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-mylib-2f-LCD1602

clean-mylib-2f-LCD1602:
	-$(RM) ./mylib/LCD1602/LCD1602.cyclo ./mylib/LCD1602/LCD1602.d ./mylib/LCD1602/LCD1602.o ./mylib/LCD1602/LCD1602.su

.PHONY: clean-mylib-2f-LCD1602

