#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "block.h"
#include "heap.h"

void* jamalloc(size_t size);
void jamfree(void* ptr);
void dump_heap(void);
void print_blocks(void);