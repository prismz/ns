#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

void* smalloc(size_t size);
void* srealloc(void* ptr, size_t size);
char* get_mem(void);

#endif
