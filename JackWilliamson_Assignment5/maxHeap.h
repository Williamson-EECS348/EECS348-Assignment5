#pragma once
#include "emailNode.h"
// https://www.geeksforgeeks.org/c/c-program-to-implement-max-heap/#

typedef struct {
    EmailNode** heap;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* MaxHeap_create(int capacity);
void MaxHeap_add(MaxHeap* h, EmailNode* value);
EmailNode MaxHeap_pop(MaxHeap* h);
EmailNode* MaxHeap_peek(MaxHeap* h);
void MaxHeap_print(MaxHeap* h);
void MaxHeap_destroy(MaxHeap* h);
