################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylib/Sensor_temperature/Lm75A.c 

OBJS += \
./mylib/Sensor_temperature/Lm75A.o 

C_DEPS += \
./mylib/Sensor_temperature/Lm75A.d 


# Each subdirectory must supply rules for building sources it contributes
mylib/Sensor_temperature/%.o mylib/Sensor_temperature/%.su mylib/Sensor_temperature/%.cyclo: ../mylib/Sensor_temperature/%.c mylib/Sensor_temperature/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/LCD1602" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/OLED_SH1106" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/Sensor_temperature" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/4 digit 7 segment" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/utils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-mylib-2f-Sensor_temperature

clean-mylib-2f-Sensor_temperature:
	-$(RM) ./mylib/Sensor_temperature/Lm75A.cyclo ./mylib/Sensor_temperature/Lm75A.d ./mylib/Sensor_temperature/Lm75A.o ./mylib/Sensor_temperature/Lm75A.su

.PHONY: clean-mylib-2f-Sensor_temperature

