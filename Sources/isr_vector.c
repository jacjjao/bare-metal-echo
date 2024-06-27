#include "main.h"
#include <stdio.h>
#include <stm32l0xx_hal.h>
#include <stm32l0xx_ll_dma.h>
#include <stm32l0xx_ll_usart.h>
#include <string.h>

void SysTick_Handler() { HAL_IncTick(); }

static void serialize_ring(ring_buf *buf, uint8_t *out) {
    if (buf->begin > buf->end) {
        size_t p = 0;
        for (int i = buf->begin; i < RING_BUF_MAX_SIZE; ++i) {
            out[p++] = buf->data[i];
        }
        for (int i = 0; i < buf->end; ++i) {
            out[p++] = buf->data[i];
        }
    } else {
        memcpy(out, buf->data + buf->begin, buf->size);
    }
}

void USART2_IRQHandler(void) {
    while (LL_USART_IsActiveFlag_RXNE(USART2)) {
        uint8_t byte = USART2->RDR;
        if (byte != '\r') {
            ring_buf_push(&cmd_buf, byte);
            continue;
        }
        if (echo_size > 0) { // dma is busy
            continue;
        }
        ring_buf_push(&cmd_buf, byte);
        serialize_ring(&cmd_buf, echo_buf);
        echo_size = cmd_buf.size;
        echo_buf[echo_size++] = '\n';
        ring_buf_clear(&cmd_buf);
    }
}

void DMA1_Channel4_7_IRQHandler(void) {
    if (LL_DMA_IsActiveFlag_TE4(DMA1)) {
        printf("Transfer error\r\n");
    }
    LL_DMA_ClearFlag_TE4(DMA1);
    LL_DMA_ClearFlag_TC4(DMA1);
    LL_DMA_ClearFlag_HT4(DMA1);
    LL_DMA_ClearFlag_GI4(DMA1);

    LL_USART_DisableDMAReq_TX(USART2);

    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);

    echo_size = 0;
    dma_busy = 0;
}