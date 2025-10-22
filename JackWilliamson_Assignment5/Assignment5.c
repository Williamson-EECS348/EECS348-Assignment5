#include <stdio.h>

#include "emailNode.h"
#include "maxHeap.h"

int main() {
    MaxHeap* heap = MaxHeap_create(10);
    MaxHeap_add(heap, EmailNode_create("", "3", "03-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "8", "08-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "2", "02-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "6", "06-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "4", "04-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "9", "09-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "1", "01-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "7", "07-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "10", "10-01-1960"));
    MaxHeap_add(heap, EmailNode_create("", "5", "05-01-1960"));

    for (int i = 0; i < 10; i++) {
        MaxHeap_print(heap);
        MaxHeap_pop(heap);
        printf("-----------------\n");
    }


    MaxHeap_destroy(heap);
}