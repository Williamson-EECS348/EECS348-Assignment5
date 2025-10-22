#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int checkDate(const char* a, const char* b) {
    char* aDateParts[3];
    char* bDateParts[3];
    splitDate(a, aDateParts);
    splitDate(b, bDateParts);

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

int main() {
    const char* date1 = "12-25-2020";
    const char* date2 = "01-01-2021";

    if (checkDate(date1, date2)) {
        printf("%s is not more recent than %s\n", date1, date2);
    } else {
        printf("%s is more recent than %s\n", date1, date2);
    }
}