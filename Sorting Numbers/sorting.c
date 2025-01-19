/* 
* sorting.c
* Ali Ajwani
* This code allows the user to input numbers or generate random ones for an array, and then 
* it sorts the numbers in a 2D array 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> 

// Initalizes functions
void get_values(int *n, int *m);
void handle_arr(int arr[], int aux[], int start, int length, int action);
void sort_arr(int arr[], int low, int high, int choice);
void initialize_and_sort(int matrix[2][100], int n, int m, int new_input);
int divide(int arr[], int start, int end);

/*
 * This function prompts the user to enter two values that meet the given criteria.
 * One value is the number of elements the user will input, and one value is the size of the array
 * 
 * int *n: The pointer variable for the number of elements the user will input
 * int *m: The pointer variable for the size of the array
 */
void get_values(int *n, int *m) {
    // Makes user input n and makes user redo input if the input is not valid
    do {
        printf("Enter the number of elements you would like to enter (n). n must be an even number: ");
        scanf("%d", n);

        // Checks if n is even and continues if it is
        if (*n % 2 != 0) {
            continue;
        }

        // Makes user input m and makes user redo the input if the input is not valid
        do {
            printf("Enter the length of the array (m). m must be an even number and >= n: ");
            scanf("%d", m);
            
            // Checks if m is even and smaller or equal to n and leaves the loop if it is
            if (*m % 2 == 0 && *m >= *n) {
                break;
            }
        } while (1); // Continues inner loop until m is valid
        break;
    } while (1); // Continues outer loop until n and m are both valid
}

/*
 * This function performs an action on the array based on the requested action.
 * 
 * int arr[]: The array to operate on
 * int aux[]: An auxiliary array that is used for cloning if required in the action
 * int start: The starting index 
 * int length: The size of the array
 * int action: The number which specifies the action to perform
 */
void handle_arr(int arr[], int aux[], int start, int length, int action) {

    switch (action) {
        // If action is 0, it fills the array with random numbers from the start to the length
        case 0:
            for (int i = start; i < length; i++) {
                arr[i] = rand() % 10001;
            }
            break;
        
        // If action is 1, it displays the array
        case 1:
            for (int i = 0; i < length; i++) {
                printf("%6d ", arr[i]);
            }
            printf("\n");
            break;

        // If action is 2, it duplicates the array in an alternate array
        case 2:
            for (int i = 0; i < length; i++) {
                aux[i] = arr[i];
            }
            break;

        // If the action is anything else, it prints out an error message
        default:
            printf("Invalid action.");
            break;
    }
}

/*
 * This function sets up the array and then uses sort_arr to sort the array
 * 
 * int matrix: A 2D array to store the original and the sorted arrays
 * int n: The number of elements the user should input
 * int m: The total size of the array
 * int new_input: A flag to indicate if a new input is needed
 */
void initialize_and_sort(int matrix[2][100], int n, int m, int new_input) {
    int i = 0;

    // Collects the user input for values in the first row of the array
    if (new_input) {
        printf("Enter n elements: ");
        for (i = 0; i < n; i++) {
            if (scanf("%d", &matrix[0][i]) != 1) {
                printf("Invalid input detected. Filling remaining slots with random numbers.\n");
                break;
            }
        }
        // Displays the number of inputted numbers and random numbers that will be generated
        printf("You entered %d numbers, %d random numbers will be generated.\n", i, m - i);
        handle_arr(matrix[0], NULL, i, m, 0);
    } else {
        printf("You entered %d numbers, %d random numbers will be generated.\n", n, m - n);
        handle_arr(matrix[0], NULL, n, m, 0);  
    }

    // Initializes the variable for the sorting algorith choice
    int choice;

    // Prompts the user to choose a sorting algorithm
    do {
        printf("::Choose a sorting algorithm::\n|| (0) Quick sort || (1) Bubble sort ||\n");
        if (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1)) {
            printf("Invalid choice, try again!\n");
            while (getchar() != '\n'); // clear input buffer
        } else {
            break;
        }
    } while (1);

    // Clones the array to the second row for sorting
    handle_arr(matrix[0], matrix[1], 0, m, 2);

    // Sorts and times how long the sort takes
    time_t start_time = time(NULL);
    sort_arr(matrix[1], 0, m - 1, choice);
    time_t end_time = time(NULL);

    // Displays the original and sorted arrays, and how long the sort took
    printf("Raw array\n");
    handle_arr(matrix[0], NULL, 0, m, 1);

    printf("Sorted array\n");
    handle_arr(matrix[1], NULL, 0, m, 1);

    printf("Sorting duration (Sec): %ld\n", (end_time - start_time));
    }



/**
 * This function sorts the array using the chosen sorting method.
 *
 * int arr: The array to be sorted
 * int low: The starting index of the sort 
 * int high: The ending index of the sort 
 * int choice: The index for which sorting method to use
 */
void sort_arr(int arr[], int low, int high, int choice) {
    // If the choice is 0, then quick sort the array
    if (choice == 0) {
        if (low < high) {
            int pi = divide(arr, low, high);
            sort_arr(arr, low, pi - 1, choice);
            sort_arr(arr, pi + 1, high, choice);
        }
    } 
    // If the choice is 1, then bubble sort the array
    else if (choice == 1) {
        for (int pass = high; pass > 0; pass--) {
            for (int j = 0; j < pass; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}


/*
 * This function divides the array for the Quick Sort algorithm
 * 
 * int arr[]: The array to be divided
 * int start: The starting index for the divide
 * int end: The ending index for the divide
 * 
 * Return: The index of the divide
 */
int divide(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
    int j = start;

    while (j < end) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        j++;
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = temp;

    return i + 1;
}


// The main function that executes the code.
int main() {

    // Initializes the variables
    int n, m;
    int matrix[2][100] = {0};  
    char command;

    // Gets the valid inputs for n and m
    get_values(&n, &m);

    // Sets up and sorts the array based on the users inputs
    initialize_and_sort(matrix, n, m, 1);

    // The main loop for the user inputs
    while (command != 'q' && command != 'Q') {
        printf("\nEnter a command from the following list:\n");
        printf("(R) Re-generate random numbers and choose a different sorting algorithm\n");
        printf("(N) Enter another value for n and m, and enter new n numbers\n");
        printf("(S) Use a different sorting algorithm\n");
        printf("(Q) Quit\n");
        printf("Enter command: ");
        scanf(" %c", &command);

        // Handles the users inputs accordingly
        if (command == 'r' || command == 'R') {
            initialize_and_sort(matrix, n, m, 0);
        } else if (command == 'n' || command == 'N') {
            get_values(&n, &m);
            initialize_and_sort(matrix, n, m, 1);
        } else if (command == 's' || command == 'S') {
            initialize_and_sort(matrix, n, m, 0);
        } else if (command == 'q' || command == 'Q') {
            printf("Exiting the program.\n");
        } else {
            printf("Invalid command.\n");
        }
    }

    return 0;
}