#include "block.h"
#include <stdbool.h>

void init_block(Block* block, size_t alsize, bool is_free) {
    block->size = alsize;
    block->free = is_free;
    block->next = NULL;
}

void reuse_block(Block* block, size_t alsize) {
    block->size = alsize;
    block->free = false;
}

void print_block(Block* block) {
    printf("block=%p payload=%p end=%p size=%zu free=%d\n",
    (void*)block,
    (void*)block + 1,
    (void*)((char*)(block + 1) + block->size),
    block->size,
    block->free ? 1:0
    );
}