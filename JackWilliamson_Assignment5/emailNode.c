#include "emailNode.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

EmailNode* EmailNode_create(const char* category, const char* subject, const char* date) {
    EmailNode* node = (EmailNode*)malloc(sizeof(EmailNode));

    node->category = strdup(category);
    node->subject = strdup(subject);
    node->date = strdup(date);

    return node;
}

void EmailNode_destroy(EmailNode* node) {
    free(node->category);
    free(node->subject);
    free(node->date);
    free(node);

}

void splitDate(const char* date, char** output) {
    // Splits date string "MM-DD-YYYY" into output[0] = MM, output[1] = DD, output[2] = YYYY
    char* token;
    char* dateCopy = strdup(date);
    int index = 0;
    token = strtok(dateCopy, "-");
    while (token != NULL) {
        output[index++] = strdup(token);
        token = strtok(NULL, "-");
    }
    free(dateCopy);
}

int checkDate(const EmailNode* a, const EmailNode* b) {
    char* aDateParts[3];
    char* bDateParts[3];
    splitDate(a->date, aDateParts);
    splitDate(b->date, bDateParts);

    // Convert years
    int yearA = atoi(aDateParts[2]);
    int yearB = atoi(bDateParts[2]);
    // Convert months
    int monthA = atoi(aDateParts[0]);
    int monthB = atoi(bDateParts[0]);
    // Convert days
    int dayA = atoi(aDateParts[1]);
    int dayB = atoi(bDateParts[1]);

    for (int i = 0; i < 3; i++) {
        free(aDateParts[i]);
        free(bDateParts[i]);
    }

    if (yearA == yearB) {
        if (monthA == monthB) {
            return dayA < dayB;
        }
        return monthA < monthB;
    }
    return yearA < yearB;
}

int checkCategory(const char* category) {
    if (strcmp(category, "Boss") == 0)
        return 1;
    else if (strcmp(category, "Subordinate") == 0)
        return 2;
    else if (strcmp(category, "Peer") == 0)
        return 3;
    else if (strcmp(category, "ImportantPerson") == 0)
        return 4;
    else if (strcmp(category, "OtherPerson") == 0)
        return 5;
    return 6; // Unknown category
}

int EmailNode_compare(const EmailNode* a, const EmailNode* b) {
    if (strcmp(a->category, b->category) == 0)
        return checkDate(a, b);

    return checkCategory(a->category) > checkCategory(b->category);
}

void EmailNode_printNode(const EmailNode* node) {
    printf("%s ", node->subject);
    //printf("Sender: %s\n\tSubject: %s\n\tDate: %s\n", node->category, node->subject, node->date);
}
