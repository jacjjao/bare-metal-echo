#include "ringbuf.h"

void ring_buf_init(ring_buf *buf) {
    buf->begin = buf->end = 0;
    buf->size = 0;
}

void ring_buf_push(ring_buf *buf, uint8_t byte) {
    buf->data[buf->end] = byte;
    buf->end = (buf->end + 1) % RING_BUF_MAX_SIZE;
    if (buf->size >= RING_BUF_MAX_SIZE) {
        buf->begin = (buf->begin + 1) % RING_BUF_MAX_SIZE;
    } else {
        buf->size += 1;
    }
}

void ring_buf_clear(ring_buf *buf) {
    buf->begin = buf->end = 0;
    buf->size = 0;
}