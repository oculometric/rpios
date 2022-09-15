#ifndef MAILBOX_H
#define MAIOLBOX_H

#include <stdint.h>
#include "gpio.h"
#include "mmio.h"

// Write to a mailbox. Channel supply the channel number (max 4 bits), data supply the data, 4-bit correction will be performed within function (max 28 bits data)
static inline void mailbox_write(uint8_t channel, uint32_t data) {
	while ((mmio_read(MBOX_STATUS) & MAIL_FULL) != 0) {}
    mmio_write(MBOX_WRITE, (channel & 0xF) | ((data & 0xFFFFFFF) << 4));
}

// Read from a mailbox. Result is formatted with first 4 bits representing channel and remaining 28 bits representing data
static inline uint32_t mailbox_read() {
	while ((mmio_read(MBOX_STATUS) & MAIL_EMPTY) != 0) {}
    return mmio_read(MBOX_READ);
}

static inline uint8_t mailbox_getchannel(uint32_t payload) {
    return (payload & 0xF);
}

static inline uint32_t mailbox_getdata(uint32_t payload) {
    return ((payload & 0xFFFFFFF0) >> 4);
}

#endif