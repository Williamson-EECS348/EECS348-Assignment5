#pragma once // means that the header file will only be included once in the compiled program

/**
 * This is a "class" which holds all the data for one email.
 * This gets used heavily in `MaxHeap` (see `maxHeap.h` and `maxHeap.c`)
 */
// `typedef struct ...` so that I can call it just `EmailNode` instead of `struct EmailNode` in object declarations and function parameters
//  `typedef` works like `typedef [type] [type alias];` so here we have `typedef [nameless struct] [struct name]`
typedef struct {
    // these are all `char*` and not `const char*` because they need to be assigned
    char* category; // the sender string (e.g. "Boss", "Peer", etc.)
    char* subject; // the subject string (e.g. "Can you help me on this?", etc.)
    char* date; // the date string (e.g. "12-01-2024")
} EmailNode; // the name of the struct for the `EmailNode`

/**
 * creates an `EmailNode`
 * @param category const char*; the string of the email category
 * @param subject const char*; the string of the email subject
 * @param date const char* the string of the email date
 * @note Ownership of the `EmailNode` is given to the user; call `EmailNode_destroy` to free properly
 */
EmailNode* EmailNode_create(const char* category, const char* subject, const char* date);

/**
 * Creates an `EmailNode`
 * unfortunately C (unlike C++) doesn't allow for function overloading so this is
 * named differently but it basically does the same thing as `EmailNode_create`
 * @authors Github Copilot and Jack Williamson
 * @param emailLine const char*; a like that holds the information formatted like: `category,subject,date` (date is expected to be MM-DD-YYYY)
 * @note Ownership of the `EmailNode` is given to the user; call `EmailNode_destroy` to free properly
 */
EmailNode* EmailNode_createFromString(const char* emailLine);

/**
 * Frees all memory used by the `EmailNode`
 * if the object is used after being freed it will cause a null pointer exception
 * @note MUST BE CALLED WHEN DONE WITH THE OBJECT
 * @param node EmailNode*; the node the operation should be preformed to
 */
void EmailNode_destroy(EmailNode* node);

/**
 * compares if node `a` is 'less than' `b`
 * 'less than' means less priority
 * @param a const EmailNode*; the `EmailNode` to check if it is lower priority than `b`
 * @param b const EmailNode*; the `EmailNode` to check if it is higher priority than `a`
 * @return `1` if `a` is of less priority than `b` else `0`
 */
int EmailNode_compare(const EmailNode* a, const EmailNode* b);

/**
 * prints the `EmailNode` to the console to look nice
 * @param node const EmailNode*; the node to print 
 */
void EmailNode_printNode(const EmailNode* node);