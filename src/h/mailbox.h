#ifndef MAILBOX_H
#define MAIOLBOX_H

#include <stdint.h>
#include "gpio.h"
#include "mmio.h"

enum {
    MBOX_CH_POWER_MANAGEMENT = 0,
    MBOX_CH_FRAMEBUFFER = 1,
    MBOX_CH_VIRTUAL_UART = 2,
    MBOX_CH_VCHIQ = 3,
    MBOX_CH_LED = 4,
    MBOX_CH_BUTTONS = 5,
    MBOX_CH_TOUCHSCREEN = 6,
    MBOX_CH_PROPERTY_TAGS_TO_VC = 8,
    MBOX_CH_PROPERTY_TAGS_FROM_VC = 9
};

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