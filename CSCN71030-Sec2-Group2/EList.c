#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EList.h"

// Function to create a new node
ENODE* createNode(char* username, char* password, char* name, int role) {
    ENODE* newNode = (ENODE*)malloc(sizeof(ENODE));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    // Copy strings to the struct fields
    strncpy(newNode->username, username, sizeof(newNode->username) - 1);
    newNode->username[sizeof(newNode->username) - 1] = '\0'; // Ensure null-termination
    strncpy(newNode->password, password, sizeof(newNode->password) - 1);
    newNode->password[sizeof(newNode->password) - 1] = '\0'; // Ensure null-termination
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null-termination
    newNode->r = role;
    newNode->next = NULL;
    return newNode;
}


// Function to save list to a text file
void saveList(FILE* file, ENODE* head) {
    ENODE* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %s %d\n", current->username, current->password, current->name, current->r);
        current = current->next;
    }
}

// Function to load list from a text file
ENODE* loadList(FILE* file) {
    ENODE* head = NULL;
    ENODE* current = NULL;
    char username[100], password[100], name[100];
    int role;

    while (fscanf(file, "%s %s %s %d", username, password, name, &role) == 4) {
        ROLE r = (ROLE)role;
        ENODE* newNode = createNode(username, password, name, r);
        if (head == NULL) {
            head = newNode;
            current = newNode;
        }
        else {
            current->next = newNode;
            current = current->next;
        }
    }
    return head;
}








// Function to delete a node
void deleteNode(ENODE** headPtr, char* username) {
    ENODE* current = *headPtr;
    ENODE* prev = NULL;

    while (current != NULL) {
        if (strncmp(current->username, username, sizeof(current->username)) == 0) {
            // Node found, delete it
            if (prev == NULL) {
                // If the node to be deleted is the head
                *headPtr = current->next;
            }
            else {
                // If the node to be deleted is not the head
                prev->next = current->next;
            }
            free(current); // Free memory for the node
            return;
        }
        prev = current;
        current = current->next;
    }
}


// Function to delete the entire list
void deleteList(ENODE* head) {
    ENODE* current = head;
    while (current != NULL) {
        ENODE* temp = current;
        current = current->next;
        free(temp); // Free memory for the node
    }
}

// Function to print the list
void printList(ENODE* head) {
    ENODE* current = head;
    while (current != NULL) {
        printf("Username: %s, Password: %s, Name: %s, Role: %d\n", current->username, current->password, current->name, current->r);
        current = current->next;
    }
}

// Function to search a node
ENODE* searchNode(ENODE* head, char* username) {
    ENODE* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Node not found
}

void insertNode(ENODE** head, ENODE* newNode) {
    if (*head == NULL)
        *head = newNode;
    else {
        newNode->next = *head;
        *head = newNode;
    }
}