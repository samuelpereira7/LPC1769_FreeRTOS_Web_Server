################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Services/HTTP/subdir.mk
-include src/Services/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Example01.axf

dependents:
	-cd C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/CMSISv2p00_LPC17xx/Debug && $(MAKE) all
	-cd C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/FreeRTOS_Library/Debug && $(MAKE) all
	-cd C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_EaBaseBoard/Debug && $(MAKE) all
	-cd C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_MCU/Debug && $(MAKE) all

# Tool invocations
Example01.axf: $(OBJS) $(USER_OBJS) C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/CMSISv2p00_LPC17xx/Debug/libCMSISv2p00_LPC17xx.a C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/FreeRTOS_Library/Debug/libFreeRTOS_Library.a C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_EaBaseBoard/Debug/libLib_EaBaseBoard.a C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_MCU/Debug/libLib_MCU.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\CMSISv2p00_LPC17xx\Debug" -L"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Lib_MCU\Debug" -L"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Lib_EaBaseBoard\Debug" -L"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\FreeRTOS_Library\Debug" -Xlinker --gc-sections -Xlinker -Map=Example01.map -mcpu=cortex-m3 -mthumb -T "Example01_Debug.ld" -o "Example01.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Example01.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size Example01.axf; # arm-none-eabi-objcopy -O ihex Example01.axf Example01.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/CMSISv2p00_LPC17xx/Debug/libCMSISv2p00_LPC17xx.a:
C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/FreeRTOS_Library/Debug/libFreeRTOS_Library.a:
C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_EaBaseBoard/Debug/libLib_EaBaseBoard.a:
C:/Users/samuelpereira/Repos/Aviao_Cajada/EC020/firmware_src/Lib_MCU/Debug/libLib_MCU.a:

-include ../makefile.targets
