#ifndef RING_BUF_H
#define RING_BUF_H

#include <stddef.h>
#include <stdint.h>

#define RING_BUF_MAX_SIZE 64

typedef struct ring_buf {
    uint8_t data[RING_BUF_MAX_SIZE];
    size_t begin, end;
    size_t size;
} ring_buf;

void ring_buf_init(ring_buf *buf);

void ring_buf_push(ring_buf *buf, uint8_t byte);

void ring_buf_clear(ring_buf *buf);

#endif // RING_BUF_H