#include "mem.h"
#include "uart.h"

void fill_mem (void *start, size_t len, char value) {
    for (size_t i = 0; i < len; i++) {
        ((char *)start)[i] = value;
    }
}

void dump_mem (void *start, size_t len) {
    print("MEMORY DUMP STARTING AT "); printhex ((uint32_t) start); newln();
    for (size_t i = 0; i < len; i++) {    
        printhex(((char *)start)[i]);
        if ((i+1) % 4 == 0) newln();
        else print ("   ");
    }
}

void copy_mem (void *origin, void *destination, size_t len) {
    for (size_t i = 0; i < len; i++) {
        ((char *)destination)[i] = ((char *)origin)[i];
    }
}