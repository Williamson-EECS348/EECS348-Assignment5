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
 * ID: 3178213
 * Date Created: 10-21-25
 */
#include <stdio.h> // needed to print

#include <string.h> // needed for string manipulation
#include "maxHeap.h" // `MaxHeap` "class" definition

int main() { // required entry-point `main` for C programs
    /* load in emails from file */
    FILE* file = fopen("JackWilliamson_Assignment5/Assignment5_Test_File.txt", "r"); // open the file and store it in `file`
    if (!file) { // if `file` is null
        perror("Failed to open file"); // then tell the user
        return 1; // return 1 to the user to indicate an error
    }

    /* we want to count the number of emails for the for the `MaxHeap` */
    int emailCount = 0; // the count, init to `0`
    char buffer[256]; // the char buffer that we will read lines into; this allows for up to 256 chars
    while (fgets(buffer, sizeof(buffer), file)) { // loop through all all the lines and store them in the buffer
        // we use `strncmp` which compares a given length of string
        // in this case we only compare the first `6` characters of the `buffer` to "EMAIL "; if its equal to 0 then they are equivalent
        if (strncmp(buffer, "EMAIL ", 6) == 0) {
            emailCount++; // if they match then increment the `emailCount` because we found more emails
        }
    }

    /*
     * We have iterated through the file so we need to go back to the start of the file
     * src: https://stackoverflow.com/a/32366729/16902023
     *      sub-src: https://stackoverflow.com/questions/32366665/resetting-pointer-to-the-start-of-file#comment86257118_32366729
     */
    fseek(file, 0, SEEK_SET);
    MaxHeap* heap = MaxHeap_create(emailCount); // create max heap with capacity equal to emailCount
    /* read emails from file and insert into heap */
    // this does make the assumption that all emails are at the top of the text file
    for (int i = 0; i < emailCount; i++) { // iterate the number of emails we have to add
        if (fgets(buffer, sizeof(buffer), file) != NULL) { // read in a new line and if the new line is null then we dont add anything
            // create EmailNode from the rest of the line and add it to the heap
            MaxHeap_add(heap, EmailNode_createFromString(buffer + 6)); // we add 6 to the buffer pointer to start after the "EMAIL " at the start of the line
        }
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        /*
         * We need to strip the newline off of the end if there is any.
         * This gives back the index to the string "\r\n" and sets it so 0;
         *      i.e. it moves the null terminator earlier so as to delete the new lines
         * src: https://stackoverflow.com/a/28462221/16902023
         *      sub-src: https://man.freebsd.org/cgi/man.cgi?query=strcspn&sektion=3
         */
        buffer[strcspn(buffer, "\r\n")] = 0;

        // command read in is "NEXT"
        if (strcmp(buffer, "NEXT") == 0) { // `strcmp` (string compare) compares `str1` and `str2`; output is zero if they are equal
            printf("Next email:\n"); // print out the header for the NEXT command
            EmailNode_printNode(MaxHeap_peek(heap)); // print out the top email from the `MaxHeap`

        // command read in is "READ"
        } else if (strcmp(buffer, "READ") == 0) { // `strcmp` (string compare) compares `str1` and `str2`; output is zero if they are equal
            MaxHeap_pop(heap); // READ the email pop-ing it off the `MaxHeap`; this gets rid of it

        // command read in is "COUNT"
        } else if (strcmp(buffer, "COUNT") == 0) { // `strcmp` (string compare) compares `str1` and `str2`; output is zero if they are equal
            printf("There are %d emails to read.\n\n", MaxHeap_size(heap)); // print out the size of the heap when COUNT is called
        }
    }

    // we need to clean up our objects
    fclose(file); // close the file and clean up all the data for that
    MaxHeap_destroy(heap); // we need to destroy the heap and that will clean up all our data
}