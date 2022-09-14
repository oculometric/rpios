#include <stddef.h>
#include <stdint.h>
#include <float.h>

#include "uart.h"
#include "util.h"

#define AARCH64
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
 
void execute_cmd (unsigned char* buf) {
    if (strcmp(buf, "help")) {
        println ("There's no help out here");
    } else if (strcmp(buf, "count")) {
        for (int i = 0; i < 100; i++) {
            print ("Number: ");
            printint (i);
            newln();
        }
    }  else {
        println ("Unrecognised");
    }
}

void clear_buf (unsigned char* buf, size_t n) {
    for (size_t i = 0; i <= n; i++) buf[i] = 0x0;
}

#ifdef AARCH64
// arguments for AArch64
void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
#else
// arguments for AArch32
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
#endif
{
	// initialize UART for Raspi3
	uart_init(3);
	uart_puts("Hello, kernel World!\r\n");
    if (strcmp ("abcde", "abcde")) uart_puts ("test1\r\n");
    if (strcmp ("abcde", "abc")) uart_puts ("test2\r\n");
    if (strcmp ("abcde", "edcba")) uart_puts ("test3\r\n");
 
    unsigned char cmd_buf[65];
    for (uint8_t i = 0; i < 65; i++) {
        cmd_buf[i] = 0x0;
    }
    size_t cmd_buf_p = 0;

	while (1) {
        unsigned char c = uart_getc();
        if (c == '\r') {
            uart_putc('\n');
            execute_cmd (cmd_buf);
            clear_buf (cmd_buf, cmd_buf_p);
            cmd_buf_p = 0;
        } else if (c == '\b' && cmd_buf_p > 0) {
            cmd_buf_p--;
            cmd_buf[cmd_buf_p] = 0x0;
        } else if (cmd_buf_p < 65) {
            cmd_buf[cmd_buf_p] = c;
            cmd_buf_p++;
        }

		uart_putc(c);
    }

}