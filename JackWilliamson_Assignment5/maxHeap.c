#include "maxHeap.h"

#include <malloc.h>
#include <stdio.h>

void upheap(MaxHeap* h, int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;

    if (EmailNode_compare(h->heap[parent], h->heap[index])) {
        EmailNode* temp = h->heap[parent];
        h->heap[parent] = h->heap[index];
        h->heap[index] = temp;

        upheap(h, parent);
    }
}

void downheap(MaxHeap* h, int index) {
    int left = (index * 2) + 1,
        right = (index * 2) + 2,
        max = index;

    if (left < h->size && EmailNode_compare(h->heap[max], h->heap[left]))
        max = left;
    if (right < h->size && EmailNode_compare(h->heap[max], h->heap[right]))
        max = right;

    if (max != index) {
        EmailNode* temp = h->heap[index];
        h->heap[index] = h->heap[max];
        h->heap[max] = temp;

        downheap(h, max);
    }
}

MaxHeap* MaxHeap_create(int capacity) {
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));

    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;

    h->heap = (EmailNode**)malloc(capacity * sizeof(EmailNode*));

    if (h->heap == NULL) {
        printf("Memory error");
        free(h);
        return NULL;
    }
    return h;
}

void MaxHeap_add(MaxHeap* h, EmailNode* value) {
    if (h->size < h->capacity) {
        h->heap[h->size] = value;
        upheap(h, h->size);
        h->size++;
    } else {
        printf("Heap at capacity; skipping.");
    }
}

EmailNode* MaxHeap_pop(MaxHeap* h) {
    if (h->size == 0) {
        printf("Heap is empty");
        return NULL; // return empty EmailNode
    }

    EmailNode* root = h->heap[0];
    h->heap[0] = h->heap[--h->size];
    downheap(h, 0);

    return root;
}

EmailNode* MaxHeap_peek(MaxHeap* h) {
    if (h->size == 0) {
        printf("Heap is empty");
        return NULL; // return empty EmailNode
    }
    return h->heap[0];
}

void MaxHeap_print(MaxHeap* h) {
    for (int i = 0; i < h->size; i++) {
        EmailNode_printNode(h->heap[i]);
    }
    printf("\n");
}

void MaxHeap_destroy(MaxHeap* h) {
    for (int i = 0; i < h->size; i++) {
        EmailNode_destroy(h->heap[i]);
    }
    free(h->heap);
    free(h);
}