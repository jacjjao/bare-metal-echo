# Bare Metal STM32 Project-Echo

## Summary
peripheral used: UART(115200 baud), DMA, SysTick, GPIO<br>
<br>
1. User send a string to the board with serial terminal.<br>
2. A interrupt is trigger by UART-rx and in the irq handler the board will read the input string into a ring buffer<br>
3. When it encounter the terminal character '\r', it will copy the content into another buffer and set the flag to indicate the data is ready to be sent back.
4. When the super loop discovered the flag is set, UART-tx will initiate a dma transfer to the user.
5. When the transfer is complete or an error occurred it triggers an interrupt.
6. In DMA interrupt handler the flags is clear and if an error occurred an error message is sended via UART-tx.
7. The LED on the board is turn on-off every second because it looks cool👍

## Required tools to build this project
- CMake
- Makefile
- arm-none-eabi toolchains
- CMSIS and HAL/LL driver for STM32L053R8T6
