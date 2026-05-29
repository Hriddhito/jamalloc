#include "jamalloc.h"
#include <stdio.h>

static char heap[HEAP_SIZE];
static size_t heap_ptr = 0;

static Block* head=NULL;
static Block* tail=NULL;

static void reshape_free_mem(Block* start, Block* end, size_t cum_size, size_t alsize) {
    start->next = end->next;
    /*
    if (cum_size > alsize) {
        Block* temp = (Block*)((char*)start+alsize+BLOCK_SIZE);
        init_block(start, alsize, true);
        temp->next = end->next;
        end->next = temp;
    }
        */
}

static Block* create_new_block(size_t *heap_ptr, size_t alsize) {
    
    size_t total_size = BLOCK_SIZE + alsize;

    if (*heap_ptr + total_size > HEAP_SIZE)
        return NULL;

    Block* new_block;
    
    if (!head) {
        new_block = (Block*)heap;
        head = tail = new_block;
    } else {
        new_block = (Block*)((char*)tail + BLOCK_SIZE + tail->size);
        tail->next = new_block;
        tail = new_block;
    }
    init_block(new_block, alsize, false);
    *heap_ptr += total_size;

    return new_block;
}

static Block* get_free_block(size_t alsize) {
    Block* block = head;
    Block* counter = head;
    size_t cum_size = 0;

    while (counter) {
        if (counter->free) {
            cum_size += counter->size;
            if (cum_size >= alsize) {
                reshape_free_mem(block, counter, cum_size, alsize);
                return block;
            }
        } else {
            cum_size = 0;
            block = counter->next;
        }
        counter = counter->next;
    }

    return NULL;
}

void* jamalloc(size_t size) {
    size_t alsize = (size + 15) & ~15;

    Block* new_block=NULL;

    new_block = get_free_block(alsize);
    if (!new_block) {
        new_block = create_new_block(&heap_ptr, alsize);
    } else {
        reuse_block(new_block, alsize);
    }

    if (!new_block) return NULL;

    return (void*)(new_block+1);
}

void jamfree(void* ptr) {
    if (!ptr) return;
    
    Block* curr_block = (Block*)ptr-1;
    if (curr_block->free) printf("Pointer already free\n");
    curr_block->free = true;
}

void dump_heap() {
    printf("\nHeap dump:\n");

    for (int i = 0; i < HEAP_SIZE; i++) {
        printf("%02X ", (unsigned char)heap[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}

void print_blocks() {
    Block* curr_block = head;
    while(curr_block) {
        print_block(curr_block);
        curr_block = curr_block->next;
    }
}

void verify_heap() {
    if (!head) {
        printf("Empty head\n");
        return;
    }

    Block* curr_block = head;
    int overlap_counter = 0;

    while (curr_block->next) {
        if ((char*)curr_block+BLOCK_SIZE+curr_block->size > (char*)(curr_block->next)) {
            printf("Overlap of blocks at %p with %p\n", (void*)curr_block, (void*)(curr_block->next));
            overlap_counter++;
        }
        curr_block = curr_block->next;
    }

    if (!overlap_counter) {
        printf("No overlaps\n");
    } else {
        printf("%d overlaps\n",overlap_counter);
    }
}