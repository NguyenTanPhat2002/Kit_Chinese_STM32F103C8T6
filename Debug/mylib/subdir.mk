################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mylib/TM1640.c 

OBJS += \
./mylib/TM1640.o 

C_DEPS += \
./mylib/TM1640.d 


# Each subdirectory must supply rules for building sources it contributes
mylib/%.o mylib/%.su mylib/%.cyclo: ../mylib/%.c mylib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/LCD1602" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/OLED_SH1106" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/Sensor_temperature" -I"D:/Embedded System/kit_chinese_stm32f103c8t6/mylib/untils" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-mylib

clean-mylib:
	-$(RM) ./mylib/TM1640.cyclo ./mylib/TM1640.d ./mylib/TM1640.o ./mylib/TM1640.su

.PHONY: clean-mylib

