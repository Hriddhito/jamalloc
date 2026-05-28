#include <stdio.h>
#include <string.h>
#include "jamalloc.h"

int main() {
    void* a = jamalloc(16);
    void* b = jamalloc(32);
    void* c = jamalloc(16);

    printf("a = %p\n", a);
    printf("b = %p\n", b);
    printf("c = %p\n", c);

    dump_heap();

    printf("\nFreeing b...\n");
    jamfree(b);

    dump_heap();

    printf("\nAllocating d...\n");

    void* d = jamalloc(24);

    printf("d = %p\n", d);

    dump_heap();

    return 0;
}