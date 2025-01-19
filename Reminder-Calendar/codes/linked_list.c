#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

//addNode: Adds a new node with the given text to the end of the linked list
struct Node* addNode(struct Node *head, const char *text) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (!newNode) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->text, text, MAX_STR_LEN);
    newNode->text[MAX_STR_LEN - 1] = '\0';
    newNode->next = NULL;

    if (!head) {
        return newNode;  //If the list is empty, return the new node
    }

    //Traverse to the last node
    struct Node *current = head;
    while (current->next) {
        current = current->next;
    }

    //Add the new node at the end of the list
    current->next = newNode;

    return head;
}

//deleteNode: Deletes a node containing the specified text
struct Node* deleteNode(struct Node *head, const char *text) {
    struct Node *current = head, *prev = NULL;

    while (current) {
        if (strcmp(current->text, text) == 0) {
            if (prev) {
                prev->next = current->next;
            } 
	    else {
                head = current->next;
            }
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }

    return head;
}

//freeAll: Frees all nodes in the linked list
void freeAll(struct Node **head) {
    struct Node *current = *head;
    while (current) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

//printList: Prints all the nodes in the linked list
void printList(const struct Node *head) {
    const struct Node *current = head;
    while (current) {
        printf(" %s\n", current->text);
        current = current->next;
    }
}

