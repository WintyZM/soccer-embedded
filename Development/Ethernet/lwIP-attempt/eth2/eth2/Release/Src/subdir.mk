################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/ethernetif.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/lwip.c \
../Src/main.c \
../Src/stm32h7xx_hal_msp.c \
../Src/stm32h7xx_hal_timebase_TIM.c \
../Src/stm32h7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32h7xx.c \
../Src/usart.c \
../Src/usb_otg.c 

OBJS += \
./Src/dma.o \
./Src/ethernetif.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/lwip.o \
./Src/main.o \
./Src/stm32h7xx_hal_msp.o \
./Src/stm32h7xx_hal_timebase_TIM.o \
./Src/stm32h7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32h7xx.o \
./Src/usart.o \
./Src/usb_otg.o 

C_DEPS += \
./Src/dma.d \
./Src/ethernetif.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/lwip.d \
./Src/main.d \
./Src/stm32h7xx_hal_msp.d \
./Src/stm32h7xx_hal_timebase_TIM.d \
./Src/stm32h7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32h7xx.d \
./Src/usart.d \
./Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32H743xx -I"C:/Users/rober/STM32Cube/eth2/eth2/Inc" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/system" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/BSP/Components/lan8742" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/posix" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/apps/httpd"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


