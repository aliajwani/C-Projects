#ifndef INTERACT_H
#define INTERACT_H

#include "reminder.h"

#define MAX_STR_LEN 100

//flushBuffer: Ensures the input buffer is cleared
void flushBuffer();

//readFromFile: Reads reminders from a file into the month structure
void readFromFile(const char *fileName, struct Month *month);

//writeToFile: Writes reminders from the month structure to a file
void writeToFile(const char *fileName, const struct Month *month);

#endif

