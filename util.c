#include <stdint.h>
#include <stddef.h>
#include "util.h"

size_t strlen (char* a) {
    size_t i = 0;
    while (a[i] != 0x0) i++;
    return i;
}

uint8_t strcmp (char* a, char* b) {
    size_t i = 0;
    while (a[i] == b[i]) {
        if (a[i] == 0x0) return 1;
        i++;
    }
    return 0;
}

uint8_t inttostr (char* out, int i, unsigned int base) {
    size_t blen = strlen (out);
    if (blen < 2) return 1;
    size_t digit = 0;
    int working_copy = i;
    if (working_copy < 0) working_copy = -working_copy;
    if (i == 0) {
        out[0] = '0';
        out[1] = 0x0;
        return 0;
    }
    while (working_copy > 0 && digit < blen-1) {
        unsigned int d = working_copy % base;
        out[digit] = "0123456789ABCDEF"[d];
        working_copy /= base;
        digit++;
    }

    if (i < 0) {
        for (size_t i = 0; i < (digit+1)/2; i++) {
            size_t j = digit-i;
            char x = out[i];
            out[i] = out[j];
            out[j] = x;
        }
        out[0] = '-';
        out[digit+1] = 0x0;
    } else { 
        for (size_t i = 0; i < digit/2; i++) {
            size_t j = (digit-1)-i;
            char x = out[i];
            out[i] = out[j];
            out[j] = x;
        }
        out[digit] = 0x0;
    }

    if (digit == blen) return 1;
    return 0;
}

void fill (char* p, size_t s, char v) {
    for (size_t i = 0; i < s; i++) {
        p[i] = v;
    }
}