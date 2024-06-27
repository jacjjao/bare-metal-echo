#ifndef MAIN_H
#define MAIN_H

#include "ringbuf.h"

extern ring_buf cmd_buf;
extern uint8_t echo_buf[RING_BUF_MAX_SIZE + 1];
extern volatile size_t echo_size;
extern volatile int dma_busy;

#endif // MAIN_H