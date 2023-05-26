#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include <stddef.h>

void dump_mem (void *, size_t);
//void* malloc (size_t bytes) {assert (0);}; // TODO: Implement memory management
void fill_mem (void *, size_t, char);
void copy_mem (void *, void *, size_t);

#endif