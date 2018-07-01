# Getting Ethernet working on STM32H743ZITx NUCLEO-H743ZI

These are some rough notes I took while working on this, may serve as a reminder of what config settings to use. No longer maintaining these notes unless trying lwIP again.

## Hardware requirements

### To program over USB
- pins bridged as follows:
[picture]
- USB cable

### To enable Ethernet
- pins bridged as follows:
- Ethernet cable

## Pin configuration (CubeMX)

### Board selection
- ...
- default settings

### USART
- switch pins (acc. to manual)
- NVIC, DMA
- 8 bits, 11520

### Ethernet
- check pins (pg. 28 and 29 of board datasheet) https://www.st.com/content/ccc/resource/technical/document/user_manual/group0/26/49/90/2e/33/0d/4a/da/DM00244518/files/DM00244518.pdf/jcr:content/translations/en.DM00244518.pdf

### Interrupts
- I like to generate an IRQ handler for everything so it doesn't put everything in a generic handler

### FreeRTOS
- static alloc, 512

### lwIP
- enable
- disable DHCP. Use hardwire ip addr http://www.openstm32.org/dl410

### ARM
- enable I/D cache

### Generation
- backup files

## Observations
- MX_LWIP_Init() call is generated in startDefaultTask() with FreeRTOS enabled
- MX_LWIP_Process() is not generated in lwip.c if FreeRTOS is enabled; otherwise it is