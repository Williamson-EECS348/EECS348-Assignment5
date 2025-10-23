/**
 * Assignment Name: EECS 348 Assignment 5
 * Description: CEO Email prioritization program (written in C this time)
 * Inputs: test file labeled Assignment5_Test_File.txt
 * Output: Next email and number of unread emails
 * Collaborators:
 *      Professor Gibbons (last year's class)
 *      geeksforgeeks.org
 *      stackoverflow.com
 *      (in limited usage) Github Copilot
 * Name: John ("Jack") Scott Williamson IV
 *   ID: 3178213
 * Date Created: 10-21-25
 */
#include <stdio.h>

#include <string.h>
#include "maxHeap.h"

int main() {
    // load in emails from file
    FILE* file = fopen("JackWilliamson_Assignment5/Assignment5_Test_File.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    // count the number of emails, each one is prefixed with "EMAIL " in the file
    int emailCount = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "EMAIL ", 6) == 0) {
            emailCount++;
        }
    }
    // reset file pointer to beginning
    fseek(file, 0, SEEK_SET);
    // create max heap with capacity equal to emailCount
    MaxHeap* heap = MaxHeap_create(emailCount);
    // read emails from file and insert into heap
    for (int i = 0; i < emailCount; i++) {
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            // create EmailNode from the rest of the line and add it to the heap
            MaxHeap_add(heap, EmailNode_createFromString(buffer + 6));
        }
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        // https://stackoverflow.com/a/28462221/16902023
        // https://man.freebsd.org/cgi/man.cgi?query=strcspn&sektion=3
        buffer[strcspn(buffer, "\r\n")] = 0;
        if (strcmp(buffer, "NEXT") == 0) {
            printf("Next email:\n");
            EmailNode_printNode(MaxHeap_peek(heap));

        } else if (strcmp(buffer, "READ") == 0) {
            MaxHeap_pop(heap);

        } else if (strcmp(buffer, "COUNT") == 0) {
            printf("There are %d emails to read.\n\n", MaxHeap_size(heap));
        }
    }

    // clean up objects
    fclose(file);
    MaxHeap_destroy(heap);
}