#include "block.h"

void init_block(Block* block, size_t alsize, bool is_free) {
    block->size = alsize;
    block->free = is_free;
    block->next = NULL;
}

void reuse_block(Block* block, size_t alsize) {
    block->size = alsize;
    block->free = false;
}