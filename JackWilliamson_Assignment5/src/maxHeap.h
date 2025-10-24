#pragma once // means that the header file will only be included once in the compiled program
#include "emailNode.h" // `EmailNode` "class" definition

/**
 * This 'class' is heavily based on a geeksforgeeks.org article
 *      https://www.geeksforgeeks.org/c/c-program-to-implement-max-heap/#
 * It shows a way of implementing a max heap in C for `int`s so some modification
 * was needed to make it for the `EmailNode`. I would have preferred to not have
 * tied it to only `EmailNode` (maybe with some `void*`) but that was far too much
 * work so I just opted to make it reliant.
 * This is designed to be as object oriented as I could make it be because that is
 * just a better way to do this (plus it makes the UML diagram easier to make ;) )
 */
// `typedef struct` so that I can call it just `MaxHeap` instead of `struct MaxHeap` in object declarations and function parameters
typedef struct {
    EmailNode** heap; // double pointer because I want an array of (heap allocated) `EmailNode`s
    int size; // the number of nodes allocated in the heap
    int capacity; // the total number of nodes that can be allocated in the heap (i.e. the length of the `heap` array)
} MaxHeap; // the name of the struct for the `MaxHeap`

// forward declarations for the `MaxHeap`; if I implemented them here the program would have a 'multiple definition' error
//      each one is prefixed with `MaxHeap_` and is being used like a namespace;
//      These are equivelant to the public methods in the `MaxHeap` "class"
/**
 * Creates a `MaxHeap`
 * @param capacity int; the number of nodes that the `MaxHeap` can take on
 * @return MaxHeap* that was contructed in
 * @note ownership is given back to the caller; call `MaxHeap_destroy` to free properly
 */
MaxHeap* MaxHeap_create(int capacity); // acts as the class constructor

/**
 * adds a new `EmailNode` to a given MaxHeap
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @param value EmailNode*; the `EmailNode` that you want added to the `MaxHeap`
 * @note gives ownership of the `EmailNode` to the passed in `MaxHeap`
 */
void MaxHeap_add(MaxHeap* h, EmailNode* value);

/**
 * pops the `EmailNode` from the `MaxHeap` and returns the popped value to the user
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @return the a copy of the `EmailNode` that was popped
 * Node was freed by the pop function
 */
EmailNode MaxHeap_pop(MaxHeap* h);

/**
 * lets user see the top node of the heap
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @return `EmailNode*` to the top node of the `MaxHeap`
 * @note Ownership of the returned `EmailNode*` is retained by the passed `MaxHeap*`
 */
const EmailNode* MaxHeap_peek(MaxHeap* h);

/**
 * Prints out the entire `MaxHeap`
 * @param h MaxHeap*; the heap the operation should be preformed to
 */
void MaxHeap_print(MaxHeap* h);

/**
 * Frees all memory used by the `MaxHeap`
 * if the object is used after being freed it will cause a null pointer exception
 * @note MUST BE CALLED WHEN DONE WITH THE OBJECT
 * @param h MaxHeap*; the heap the operation should be preformed to
 */
void MaxHeap_destroy(MaxHeap* h); // acts as class destructor

// these are technically not needed because struct members are all public 
/**
 * get the size of the `MaxHeap`
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @return the `int` size of the heap
 */
int MaxHeap_size(MaxHeap* h);

/**
 * get the capacity of the `MaxHeap`
 * @param h MaxHeap*; the heap the operation should be preformed to
 * @return the `int` capacity of the heap
 */
int MaxHeap_capacity(MaxHeap* h);
