#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>

enum {
    MMIO_BASE = 0x3F000000 // For RPi 3
};
 
// Memory-Mapped I/O output
static inline void mmio_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t*)(MMIO_BASE + reg) = data;
}
 
// Memory-Mapped I/O input
static inline uint32_t mmio_read(uint32_t reg)
{
	return *(volatile uint32_t*)(MMIO_BASE + reg);
}

#endif