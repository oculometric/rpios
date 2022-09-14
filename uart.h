#ifndef UART_H
#define UART_H

#include "gpio.h"

void uart_init(int);
void uart_putc(unsigned char);
unsigned char uart_getc();
void uart_puts(const char*);

void println(char*);
void newln();
void print(char*);
void printhex(unsigned int);
void printbin(unsigned int);
void printint(int);

#endif