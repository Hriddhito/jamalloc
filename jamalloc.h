#pragma once
#include <stdio.h>

void* jamalloc(size_t size);
void jamfree(void* ptr);
void dump_heap(void);
void print_blocks(void);