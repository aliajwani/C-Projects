#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interact.h"

//flushBuffer: Ensures the input buffer is cleared
void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//readFromFile: Reads reminders from a file into the month structure
void readFromFile(const char *fileName, struct Month *month) {
    FILE *file = fopen(fileName, "r");
    if (!file) return;

    int day;
    char text[MAX_STR_LEN];
    while (fscanf(file, "%d %[^\n]", &day, text) == 2) {
        insertToCalendar(month, day, text);
    }

    fclose(file);
}

//writeToFile: Writes reminders from the month structure to a file
void writeToFile(const char *fileName, const struct Month *month) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < month->monthDays; i++) {
        struct Node *current = month->reminders[i];
        while (current) {
            fprintf(file, "%d %s\n", i + 1, current->text);
            current = current->next;
        }
    }

    fclose(file);
}
