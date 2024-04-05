#pragma once

typedef enum role {
    DOCTOR_ROLE,
    NURSE_ROLE
} ROLE;

typedef struct Enode {
    char username[100];
    char password[100];
    char name[100];
    ROLE r;
    struct Enode* next;
} ENODE;

ENODE* createNode(char* username, char* password, char* name, int role);
void saveList(FILE* file, ENODE* head);
ENODE* loadList(FILE* file);
void deleteNode(ENODE** headPtr, char username[100]);
void deleteList(ENODE* head);
void printList(ENODE* head);
ENODE* searchNode(ENODE* head, char* username);
void insertNode(ENODE** head, ENODE* newNode);