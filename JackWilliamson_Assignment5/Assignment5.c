#include <stdio.h>

#include <string.h>
#include "maxHeap.h"

int main() {
    // load in emails from file
    FILE* file = fopen("Assignment5_Test_File.txt", "r");
    if (file == NULL) {
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

    // loop for the rest of the file, each line is a query
    while (fgets(buffer, sizeof(buffer), file)) {
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