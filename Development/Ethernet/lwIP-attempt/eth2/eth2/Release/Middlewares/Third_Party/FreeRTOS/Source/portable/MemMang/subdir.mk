################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32H743xx -I"C:/Users/rober/STM32Cube/eth2/eth2/Inc" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/STM32H7xx_HAL_Driver/Inc" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/system" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/BSP/Components/lan8742" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/netif" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/posix" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/system/arch" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Drivers/CMSIS/Include" -I"C:/Users/rober/STM32Cube/eth2/eth2/Middlewares/Third_Party/LwIP/src/apps/httpd"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


