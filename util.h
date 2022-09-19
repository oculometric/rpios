#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

// Loop <delay> times in a way that the compiler won't optimize away
static inline void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

uint8_t strcmp (char*, char*);
size_t strlen (char*);
uint8_t inttostr (char*, int, unsigned int); // Returns 0 on success, 1 if buffer overflowed

#endif