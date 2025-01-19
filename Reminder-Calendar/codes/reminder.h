#ifndef REMINDER_H
#define REMINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

#define FILENAME "reminders.txt"

//Month structure
struct Month {
    int startDay; //Day of the week the month starts on (0 = Sunday)
    int monthDays; //Total number of days in the month
    struct Node *reminders[31]; //Array of linked lists for reminders
};

//initializeMonth: Sets up the month structure
void initializeMonth(struct Month *month);

//insertToCalendar: Adds a reminder to the calendar
void insertToCalendar(struct Month *month, int day, const char *value);

//printCalendar: Displays the calendar with reminders
void printCalendar(const struct Month *month);

//freeAllReminders: Frees all reminders in the calendar
void freeAllReminders(struct Month *month);

#endif

