#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interact.h"
#include "reminder.h"
#include <signal.h>

#define FILENAME "reminders.txt"

//Function prototypes
void removeReminder(struct Month *month, int day, int index);  // Add this declaration
void printTodayReminders(const struct Month *month);  // Declare the function here

//Global variable for handling reminders
struct Month globalMonth;

const char *DAYS_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char *MONTHS[] = {"January", "February", "March", "April", "May", "June",
                        "July", "August", "September", "October", "November", "December"};

//Signal handler to save reminders on program exit
void handleSignal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        printf("\nProgram terminated...\nWriting to file...\n");
        writeToFile(FILENAME, &globalMonth);
        freeAllReminders(&globalMonth);
        exit(0);
    }
}

//Function to display reminders for the current month
void printAllReminders(const struct Month *month) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    printf("\n%s reminders:\n", MONTHS[t->tm_mon]);

    for (int day = 0; day < month->monthDays; day++) {
        struct Node *current = month->reminders[day];
        if (current) {
            int weekday = (month->startDay + day) % 7;
            printf("%s %2d::\n", DAYS_OF_WEEK[weekday], day + 1);

            //Print the reminders in the order they were added, starting from the head of the list
            int count = 1;
            while (current) {
                printf(" (%d) %s\n", count++, current->text);  //Numbering reminders correctly
                current = current->next;  //Move to the next reminder
            }
        }
    }
}


int main(int argc, char *argv[]) {
    //Register signal handlers
    signal(SIGINT, handleSignal);
    signal(SIGTERM, handleSignal);

    //Initialize month and load reminders from file
    initializeMonth(&globalMonth);
    readFromFile(FILENAME, &globalMonth);

    //Check if there are enough arguments
    if (argc < 2) {
        printf("Invalid arguments\n");
        printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
        return 1;
    }

    //Command handling based on user input
    if (strcmp(argv[1], "add") == 0) {
        if (argc < 4) {
            printf("Invalid arguments\n");
            printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
            return 1;
        }

        //Get the day and validate it
        int day = atoi(argv[2]);
        if (day < 1 || day > 31) {
            printf("Invalid day: Day must be between 1 and 31.\n");
            return 1;
        }

        //Concatenate the reminder text from the remaining arguments
        char reminder[MAX_STR_LEN] = "";
        for (int i = 3; i < argc; i++) {
            strcat(reminder, argv[i]);
            if (i < argc - 1) {
                strcat(reminder, " ");  //Add a space between words
            }
        }

        //Add the reminder
        insertToCalendar(&globalMonth, day, reminder);
        printCalendar(&globalMonth);
        printAllReminders(&globalMonth);
    } 
    else if (strcmp(argv[1], "remove") == 0) {
        if (argc < 4) {
            printf("Invalid arguments\n");
            printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
            return 1;
        }
        int day = atoi(argv[2]);
        int index = atoi(argv[3]);
        
        //Validate the day before proceeding
        if (day < 1 || day > 31) {
            printf("Invalid day: Day must be between 1 and 31.\n");
            return 1;
        }

        removeReminder(&globalMonth, day, index);
        printCalendar(&globalMonth);
        printAllReminders(&globalMonth);
    } 
    else if (strcmp(argv[1], "view") == 0) {
        printCalendar(&globalMonth);
        printAllReminders(&globalMonth);
    } 
    else if (strcmp(argv[1], "today") == 0) {
        printTodayReminders(&globalMonth);
    } 
    else {
        printf("Invalid arguments\n");
        printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
        return 1;
    }

    //Save the reminders and free memory
    writeToFile(FILENAME, &globalMonth);
    freeAllReminders(&globalMonth);

    return 0;
}

