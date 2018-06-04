################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MainApp.c \
../src/cr_startup_lpc17.c \
../src/helper.c 

OBJS += \
./src/MainApp.o \
./src/cr_startup_lpc17.o \
./src/helper.o 

C_DEPS += \
./src/MainApp.d \
./src/cr_startup_lpc17.d \
./src/helper.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\FreeRTOS_Library" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Lib_EaBaseBoard\inc" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Lib_MCU\inc" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\FreeRTOS_Library\demo_code" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\CMSISv2p00_LPC17xx\inc" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\FreeRTOS_Library\include" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\FreeRTOS_Library\portable" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Example01\src\Services" -I"C:\Users\samuelpereira\Repos\Aviao_Cajada\EC020\firmware_src\Example01\src\Services\HTTP" -O1 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


