################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mylib/utils/subdir.mk
-include mylib/Sensor_temperature/subdir.mk
-include mylib/OLED_SH1106/subdir.mk
-include mylib/LCD1602/subdir.mk
-include mylib/4\ digit\ 7\ segment/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := kit_chinese_stm32f103c8t6
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
kit_chinese_stm32f103c8t6.elf \

MAP_FILES += \
kit_chinese_stm32f103c8t6.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
kit_chinese_stm32f103c8t6.list \

OBJCOPY_HEX += \
kit_chinese_stm32f103c8t6.hex \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: kit_chinese_stm32f103c8t6.elf secondary-outputs

# Tool invocations
kit_chinese_stm32f103c8t6.elf kit_chinese_stm32f103c8t6.map: $(OBJS) $(USER_OBJS) D:\Embedded\ System\kit_chinese_stm32f103c8t6\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "kit_chinese_stm32f103c8t6.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Embedded System\kit_chinese_stm32f103c8t6\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="kit_chinese_stm32f103c8t6.map" -Wl,--gc-sections -static -L"D:\Embedded System\kit_chinese_stm32f103c8t6\mylib" -L"D:\Embedded System\kit_chinese_stm32f103c8t6\mylib\LCD1602" -L"D:\Embedded System\kit_chinese_stm32f103c8t6\mylib\OLED_SH1106" -L"D:\Embedded System\kit_chinese_stm32f103c8t6\mylib\Sensor_temperature" --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

kit_chinese_stm32f103c8t6.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "kit_chinese_stm32f103c8t6.list"
	@echo 'Finished building: $@'
	@echo ' '

kit_chinese_stm32f103c8t6.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "kit_chinese_stm32f103c8t6.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout kit_chinese_stm32f103c8t6.elf kit_chinese_stm32f103c8t6.hex kit_chinese_stm32f103c8t6.list kit_chinese_stm32f103c8t6.map
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex kit_chinese_stm32f103c8t6.elf kit_chinese_stm32f103c8t6.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
