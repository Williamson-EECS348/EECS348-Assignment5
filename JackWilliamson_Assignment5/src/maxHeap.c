#include "maxHeap.h" // the maxHeap header; this is the implementation for the that "class"

#include <malloc.h> // needed to define on the heap
#include <stdio.h> // needed to print output

// `upheap` and `downheap` are defined here (the source file) which effectively makes them private

/**
 * Move a newly added node to its spot in the heap
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @param index int; the index of the node to do the comparisons to upheap it
 */
void upheap(MaxHeap* h, int index) {
    if (index == 0) return; // if we have reached the top of the heap then we dont need to upheap anymore

    // calculate the parent of the current node index
    int parent = (index - 1) / 2;

    // compare the nodes
    if (EmailNode_compare(h->heap[parent], h->heap[index])) { // if the parent node is less than the current node
        /* then we swap the two nodes */
        EmailNode* temp = h->heap[parent];
        h->heap[parent] = h->heap[index];
        h->heap[index] = temp;

        /*
         * recursively continuing upheaping until there is no need to do so anymore i.e.:
         *      we find our current node is less than the parent
         *          *or*
         *      we reach the root (which means we have found the max of the heap)
         */ 
        upheap(h, parent);
    }
}

/**
 * Move a node down in the heap to put it in its proper place
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @param index int; the index of the node to do the comparisons to downheap it
 *
 * Based on Professor Gibbons's downheap-ing code from EECS268
 */
void downheap(MaxHeap* h, int index) {
    // calcuate the left and right child nodes of some index & initially set the max node to be the current one
    int left = (index * 2) + 1, // formula given to calculate a left child
        right = (index * 2) + 2, // formula given to calculate a right child
        max = index;    // initialize the max to be the current index

    // see if the left child or the right child is larger; if neither are it stays the current index
    // we also make sure that the child we are about to check isn't outside the bounds of the heap
    if (left < h->size && EmailNode_compare(h->heap[max], h->heap[left])) // if the current max is less than the left child
        max = left; // we now know that at least the left child is larger than the max so update the current max accordingly
    if (right < h->size && EmailNode_compare(h->heap[max], h->heap[right])) // if the current max is less than the left child
        max = right; // we know that the right is larger than the current max (which could be the right's parent or the left node)

    if (max != index) { // if the current node isn't aready the max
        /* swap the current index and the new found max */
        EmailNode* temp = h->heap[index];
        h->heap[index] = h->heap[max];
        h->heap[max] = temp;

        /*
         * continue recursivly downheaping until there is no need to do so anymore; i.e.:
         *      we find that the current node is larger than both the children
         */
        downheap(h, max);
    }
}

MaxHeap* MaxHeap_create(int capacity) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // 
    // we need to allocated enough memory (in bytes) for the MaxHeap which the built-in `sizeof` function handles
    // `malloc` returns a void pointer to where in the 'memory heap' (i call it this as to not confuse it with a `MaxHeap`)
    //      so we cast it to a `MaxHeap*` so that the computer isn't confused when we access the member variables of the `MaxHeap` struct
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));

    // if `malloc` fails to allocate memory it returns a null pointer
    if (h == NULL) { // check if the allocated `MaxHeap` is null
        perror("Memory error"); // tell the user there is an issue
        return NULL; // and return null
    }

    h->size = 0; // the current size is 0 since nothing has been added to the max heap
    // we will allocate enough memory for the capacity so we store that for later;
    //  it would be nice to make this const so the user cant change it but oh well
    h->capacity = capacity;

    /*
     * allocate memory on the 'memory heap' for the max heap of `EmailNode`s;
     *  this is done for two reasons:
     *      1. a `MaxHeap` could be quite large and the memory heap is a much larger pool
     *      2. we need to allow the max heap to be sizable at runtime not just compile time which you cant do in C with standard (stack) arrays
     */
    // we allocate enough memory for however much capacity is requested in the max heap;
    //      for example, if if `capacity = 5` we know we will need to allow for 5 `EmailNode*` in the array
    // `malloc` returns a `void*` so we cast it to `EmailNode**` which is an array of `EmailNode` pointers
    h->heap = (EmailNode**)malloc(capacity * sizeof(EmailNode*));

    // same as before `malloc` returns null if the allocation failed so we check for that
    if (h->heap == NULL) { // check if the allocation failed
        perror("Memory error"); // inform the user of the error
        // at this point the `MaxHeap h` is in the memory heap so we need to
        //  free that before we go any further otherwise we would have a memory leak
        //  as the MaxHeap class still has ownership of the pointer and we cant trust the user to handle it yet
        free(h);
        return NULL; // return null to the user
    }
    return h; // if we have reached here we know all the memory is allocated and so we give ownership to the caller
}

void MaxHeap_add(MaxHeap* h, EmailNode* value) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // we dont want to (attempt to) add more nodes than we have capacity for so we need to check for that
    if (h->size < h->capacity) { // if the size is current less than the capacity we know we have room for at least one more node
        h->heap[h->size] = value; // add the new node at the end of the array; since `h->size` counts from 1 the current size is equal to the next blank node's index
        upheap(h, h->size); // now we want to upheap the newly added node so it gets put in the correct place in the max heap
        h->size++; // increase the size count by one since we have one more value
    } else { // if the size is at capacity
        printf("Heap at capacity; skipping."); // alert user that value wasn't added
    }
}

EmailNode MaxHeap_pop(MaxHeap* h) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // we can only pop as many nodes as are avaliable so:
    if (h->size == 0) { // if the size is zero we dont pop any
        printf("Heap is empty"); // inform the user that no nodes were popped
        EmailNode empty = {NULL, NULL, NULL}; // create an empty `EmailNode` to give back to the user
        return empty; // return empty `EmailNode`
    }

    // we want to keep the root to give it back to the user;
    //  we dont want the user to have the pointer since we are about to free it
    //  so we only make a copy of the root
    EmailNode root = *h->heap[0]; // derefrence the root node so it makes a copy
    EmailNode_destroy(h->heap[0]); // destroy the `EmailNode` to prevent memory leaks
    h->size--; // make size one smaller since we popped an element from the max heap
    h->heap[0] = h->heap[h->size]; // replace the node we just popped
    downheap(h, 0); // downheap the node we just moved to the root so it goes to its proper place

    // return the root copy to the user so they can use it (if needed)
    return root;
}

const EmailNode* MaxHeap_peek(MaxHeap* h) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // we can only view the top of the max heap if it exists so
    if (h->size == 0) { // we check to see if it does
        printf("Heap is empty"); // tell the user that the heap is empty
        return NULL; // return empty EmailNode
    }

    // return the root to the user; we return the pointer however ownership is maintained by the max heap
    return h->heap[0];
}

void MaxHeap_print(MaxHeap* h) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // print every element of the `MaxHeap h`
    // we only loop to the size and not capacity since there could be elements not yet assigned
    //  but everything from index [0] to [size - 1] is
    for (int i = 0; i < h->size; i++) {
        EmailNode_printNode(h->heap[i]); // we call `EmailNode_printNode` so that we have proper formatting
    }
    printf("\n"); // print a new line at the end so it looks better
}

void MaxHeap_destroy(MaxHeap* h) { // find comment explaining function purpose and parameters in `maxHeap.h`
    // destroy every `EmailNode` max heap contains
    // we only loop to the size and not capacity since there could be elements not yet assigned
    //  but everything from index [0] to [size - 1] is
    for (int i = 0; i < h->size; i++) {
        EmailNode_destroy(h->heap[i]); // function that properly frees all data in an `EmailNode`
    }

    // we dont need to free the other member variables in the `MaxHeap` struct since they were not allocated in the memory heap
    free(h->heap); // then we free the heap array
    free(h); // then we free the entire max heap

    h = NULL; // set the `MaxHeap*` to null so that if it gets used after being destoryed it causes an error, better than having the undefined behavior
}

int MaxHeap_size(MaxHeap* h) { return h->size; } // find comment explaining function purpose and parameters in `maxHeap.h`
int MaxHeap_capacity(MaxHeap* h) { return h->capacity; } // find comment explaining function purpose and parameters in `maxHeap.h`