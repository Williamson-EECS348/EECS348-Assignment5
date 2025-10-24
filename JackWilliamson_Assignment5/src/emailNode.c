#include "emailNode.h" // `EmailNode` "class" definition

#include <stdio.h> // needed to print
#include <string.h> // needed for string manipulation
#include <stdlib.h> // needed for `malloc` and `free`

// `splitDate`, `checkDate`, and `checkCategory` are defined here (the source file) which effectively makes them private

EmailNode* EmailNode_create(const char* category, const char* subject, const char* date) {  // find comment explaining function purpose and parameters in `emailNode.h`
    // need to allocate enough memory in the memory heap for an `EmailNode`
    //  allocate the number of bytes of one `EmailNode` which can be found using `sizeof(EmailNode)`
    //  `malloc` returns a `void*` so we cast it to `EmailNode*` which points to the place in the memory heap where the `EmailNode` is
    EmailNode* node = (EmailNode*)malloc(sizeof(EmailNode));

    if (!node) { // if the node fails to create and malloc returns null then we
        fprintf(stderr, "Failed to create EmailNode - %s-%s: %s\n", category, subject, date); // print out to the user what failed
        return NULL; // return null
    }

    // initalize all the member variables; `strdup` is used because:
    //      1. the parameters are `const char*` and we need them to be `char*`
    //      2. we want `EmailNode` to take ownership of them but if the strings are rvalues they cannot since they will go out of scope
    node->category = strdup(category); // assign category string
    node->subject = strdup(subject); // assign subject string
    node->date = strdup(date); // assign date string

    // return node to caller; caller takes ownership of the node
    return node;
}

EmailNode* EmailNode_createFromString(const char* emailLine) { // find comment explaining function purpose and parameters in `emailNode.h`
    // this is my Github Copilot function; I wasn't sure how to split the string on a delimiter so I asked
    // Expected format for `emailLine`: "Category,Subject,Date"
    char* token; // token string in which the part up to (but not including) the delimiter is
    // a copy of the `const char*` so that it can be modified
    //  we need `emailLine` to be a `const char*` so that it can be an rvalue but that means we need to copy it here
    char* strCopy = strdup(emailLine);
    // the strings which will be passed into `EmailNode_create` function
    char* category; // the catagory string of the email
    char* subject; // the subject string of the email
    char* date; // the date string of the email

    // we make the assumption that `emailLine` always only will have 3 sections so we just call it three times
    token = strtok(strCopy, ","); // get the string up to (but not including) the ',' in `strCopy`
    category = strdup(token); // this token is the category string so we store it there for later

    token = strtok(NULL, ","); // we use `NULL` for the string because we are still using the same string as last time
    subject = strdup(token); // this token is the subject string so we store it there for later

    token = strtok(NULL, ","); // we use `NULL` for the string because we are still using the same string as last time
    date = strdup(token); // this token is the subject string so we store it there for later

    // because `strdup` allocates on the memory heap we need to free the memory that got created
    free(strCopy); // frees the allocated memory heap memory 

    // create the node with the normal `EmailNode_create` function
    EmailNode* node = EmailNode_create(category, subject, date); // we get ownership of the node but we will pass it up in a moment

    // because `strdup` allocates on the memory heap we need to free the memory that got created
    free(category); // frees the allocated memory heap memory
    free(subject); // frees the allocated memory heap memory
    free(date); // frees the allocated memory heap memory

    // return the node to the caller; this passes ownership to the caller as well
    return node;
}

void EmailNode_destroy(EmailNode* node) { // find comment explaining function purpose and parameters in `emailNode.h`
    // we `strdup` to assign all the strings so we need to free them
    free(node->category); // frees the allocated memory heap memory
    free(node->subject); // frees the allocated memory heap memory
    free(node->date); // frees the allocated memory heap memory
    free(node); // free the node itself
    node = NULL; // set the node to null so that there is an error if it should be used again; that is better than the undefined behavior that could happen

}

/**
 * Splits a date string and returns an array with the split parts
 * @param date const char*; date string fromatted like "MM-DD-YYYY"
 * @param output char**; output array of strings, the caller needs to pass a `char*` array which will be used<br>
 * output[0] = "MM", output[1] = "DD", output[2] = "YYYY"
 * @note caller retains ownership of output
 */
void splitDate(const char* date, char** output) {
    // Splits date string "MM-DD-YYYY" into output[0] = "MM", output[1] = "DD", output[2] = "YYYY"
    /**
     * After Github Copilot-ing `EmailNode_createFromString` I found this article:
     *      https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/#
     * and so this function is written with examples from the article
     */
    char* token; // token string in which the part up to (but not including) the delimiter is
    // a copy of the `const char*` so that it can be modified
    //  we need `date` to be a `const char*` so that it can be an rvalue but that means we need to copy it here
    char* dateCopy = strdup(date);
    int index = 0; // index of the the output array; see comment at the top of function
    token = strtok(dateCopy, "-"); // get the string up to (but not including) the '-' in `strCopy`
    while (token != NULL) { // continue looping while there is still string left, i.e. as long as the token is not null
        output[index++] = strdup(token); // append the token (the string up to '-' the delim) to the output
        token = strtok(NULL, "-"); // we use `NULL` for the string because we are still using the same string as last time
    }

    // `strdup` allocates heap memory so we need to free it
    free(dateCopy);
    // we don't free the output since the caller retains ownership
}

/**
 * given two dates this finds which one date comes first
 * @param a const char*; the date to compare (<) to `b`
 * @param b const char*; the date to compare (>) to `a`
 * @return `0` if email `a` comes before email `b`; `1` otherwise
 */
int checkDate(const char* a, const char* b) {
    // enum that gives names to the indexes for the array; I think this makes it a bit more readable
    enum date {
        MONTH, DAY, YEAR,   // 0, 1, 2
        TOTAL_PARTS         // 3
    };

    // create two arrays to hold the date strings from splitDate
    char* aDateParts[TOTAL_PARTS]; // array that will hold `date` split
    char* bDateParts[TOTAL_PARTS]; // array that will hold `date` split
    splitDate(a, aDateParts); // split `date` and store the output in the aDateParts array
    splitDate(b, bDateParts); // split `date` and store the output in the bDateParts array

    // Convert years to ints
    int yearA = atoi(aDateParts[YEAR]); // `atoi` takes a string and makes it an int
    int yearB = atoi(bDateParts[YEAR]);
    // Convert months to ints
    int monthA = atoi(aDateParts[MONTH]);
    int monthB = atoi(bDateParts[MONTH]);
    // Convert days to ints
    int dayA = atoi(aDateParts[DAY]);
    int dayB = atoi(bDateParts[DAY]);

    // we need to free all the strings inside of the arrays
    //  we dont need to free the arrays since they are on the stack
    for (int i = 0; i < 3; i++) {
        free(aDateParts[i]); // free strings created by `splitDate`
        free(bDateParts[i]); // free strings created by `splitDate`
    }

    /*
     * we need to figure out which date comes first so. The logic is as follows:
     * if one year is larger/smaller than another we don't need to check anything else
     * the only situation where one is not larger/smaller is if they are equal
     * 
     * then if one month is larger/smaller than another we don't need to check anything else
     * the only situation where one is not larger/smaller is if they are equal
     * 
     * then if one year is larger/smaller than another we don't need to check anything else
     * the only situation where one is not larger/smaller is if they are equal but this means the dates are exactly equal so we dont really care about the order
     */
    if (yearA == yearB) {
        if (monthA == monthB) {
            return dayA < dayB;
        }
        return monthA < monthB;
    }
    return yearA < yearB;
}

/**
 * Compares the category string to the categories it can be
 * @param category const char*; the category from the email
 * @return `[1-5]` based on the category priority, the lower the number the higher the priority; error value of `6`
 */
int checkCategory(const char* category) { // compares the `category` string to the possible categories
    // `strcmp` (string compare) compares `str1` and `str2`; output is zero if they are equal
    if (strcmp(category, "Boss") == 0) // compare the `category` to "Boss"
        return 1; // highest priority so `return 1`
    else if (strcmp(category, "Subordinate") == 0) // compare the `category` to "Subordinate"
        return 2; // second highest priority so `return 2`
    else if (strcmp(category, "Peer") == 0) // compare the `category` to "Peer"
        return 3; // third highest priority so `return 3`
    else if (strcmp(category, "ImportantPerson") == 0) // compare the `category` to "ImportantPerson"
        return 4; // fourth highest priority so `return 4`
    else if (strcmp(category, "OtherPerson") == 0) // compare the `category` to "OtherPerson"
        return 5; // lowest priority so `return 5`
    return 6; // Unknown category
}

int EmailNode_compare(const EmailNode* a, const EmailNode* b) { // find comment explaining function purpose and parameters in `emailNode.h`
    // `strcmp` (string compare) compares `str1` and `str2`; output is zero if they are equal
    if (strcmp(a->category, b->category) == 0) // if the categories are equal then we want to compare by dates
        return checkDate(a->date, b->date); // compare the dates to each other (is date `a` before date `b`)

    // if a->category is lower priority a->category return `1` else return `0`
    return checkCategory(a->category) > checkCategory(b->category);
}

void EmailNode_printNode(const EmailNode* node) { // find comment explaining function purpose and parameters in `emailNode.h`
    // print node and formats the email like:
    //      Sender: [node->category]z
    //      Subject: [node->subject]
    //      Date: [node->date]
    printf("\tSender: %s\n\tSubject: %s\n\tDate: %s\n", node->category, node->subject, node->date);
}
