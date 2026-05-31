#pragma once

#include <stdbool.h>

typedef struct Block {
    size_t size;
    bool free;
    struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

void init_block(Block* block, size_t alsize, bool is_free);
void reuse_block(Block* block, size_t alsize);
void print_block(Block* block);