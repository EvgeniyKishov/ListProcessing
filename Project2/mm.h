#ifndef MM_H
#define MM_H

#include <stdlib.h>
#include <Windows.h>

void *kcalloc(size_t n, size_t obj_size);
void kfree(void **p);

#endif
