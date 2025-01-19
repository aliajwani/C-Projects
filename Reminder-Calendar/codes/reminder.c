#include "reminder.h"
#include <signal.h>

//Initialize the month structure
void initializeMonth(struct Month *month) {
    time_t now = time(NULL);
    if (now == -1) {
        perror("Failed to get current time");
        exit(EXIT_FAILURE);
    }

    struct tm *t = localtime(&now);
    if (!t) {
        perror("Failed to convert time");
        exit(EXIT_FAILURE);
    }

    t->tm_mday = 1;
    mktime(t);
    month->startDay = t->tm_wday;

    int monthIndex = t->tm_mon;
    int year = t->tm_year + 1900;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (monthIndex == 1 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }

    month->monthDays = daysInMonth[monthIndex];
    for (int i = 0; i < 31; i++) {
        month->reminders[i] = NULL;
    }
}

//Insert a reminder into the calendar
void insertToCalendar(struct Month *month, int day, const char *value) {
    month->reminders[day - 1] = addNode(month->reminders[day - 1], value);
}

//Print the calendar
void printCalendar(const struct Month *month) {
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");

    for (int i = 0; i < month->startDay; i++) {
        printf("    ");
    }

    for (int day = 1; day <= month->monthDays; day++) {
        if (month->reminders[day - 1]) {
            printf("(%2d)", day);
        } 
	else {
            printf(" %2d ", day);
        }

        if ((day + month->startDay) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

//Free all reminders
void freeAllReminders(struct Month *month) {
    for (int i = 0; i < month->monthDays; i++) {
        freeAll(&(month->reminders[i]));
    }
}

//Remove a reminder by its index for a given day
void removeReminder(struct Month *month, int day, int index) {
    struct Node *current = month->reminders[day - 1];
    struct Node *prev = NULL;
    int count = 1;

    while (current) {
        if (count == index) {
            if (prev) {
                prev->next = current->next;  //Bypass the node
            }
	    else {
                month->reminders[day - 1] = current->next;  //Remove from the head
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
        count++;
    }
    printf("Reminder %d not found on day %d.\n", index, day);
}

//Print reminders for today
void printTodayReminders(const struct Month *month) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int today = t->tm_mday;
    
    struct Node *current = month->reminders[today - 1];
    if (current) {
        printf("Today's reminders:\n");
        int count = 1;
        while (current) {
            printf(" (%d) %s\n", count++, current->text);
            current = current->next;
        }
    } 
    else {
        printf("No reminders for today.\n");
    }
}

