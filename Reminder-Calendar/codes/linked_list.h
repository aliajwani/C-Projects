#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define MAX_STR_LEN 100

//Node structure for linked list
struct Node {
    char text[MAX_STR_LEN];
    struct Node *next;
};

//addNode: Adds a new node with the given text to the linked list
struct Node* addNode(struct Node *head, const char *text);

//deleteNode: Deletes a node containing the specified text
struct Node* deleteNode(struct Node *head, const char *text);

//freeAll: Frees all nodes in the linked list
void freeAll(struct Node **head);

//printList: Prints all the nodes in the linked list
void printList(const struct Node *head);

#endif

