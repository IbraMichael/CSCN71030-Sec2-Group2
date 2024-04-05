#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME "testdata.txt"

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

extern ENODE* createNode(char* username, char* password, char* name, int role);
extern void saveList(FILE* file, ENODE* head);
extern ENODE* loadList(FILE* file);
extern void deleteNode(ENODE** headPtr, char username[100]);
extern void deleteList(ENODE* head);
extern void printList(ENODE* head);
extern ENODE* searchNode(ENODE* head, char* username);
extern void insertNode(ENODE** head, ENODE* newNode);

int main(void) {
    printf("\nTEST-001 Creating Doctor\n");
    char name[100] = "name";
    char username[100] = "username";
    char password[100] = "password";
    ENODE* eD = createNode(username, password, name, DOCTOR_ROLE);
    if (strcmp(username, eD->username) == 0)
        printf("Username Correct, ");
    else
        printf("Username Incorrect, ");
    if (strcmp(password, eD->password) == 0)
        printf("Password Correct, ");
    else
        printf("Password Incorrect, ");
    if (strcmp(name, eD->name) == 0)
        printf("Name Correct, ");
    else
        printf("Name Incorrect, ");
    if(eD->r == DOCTOR_ROLE)
        printf("Role Correct\n");
    else
        printf("Role Incorrect\n");

    printf("\nTEST-002 Creating Nurse\n");
    ENODE* eN = createNode(username, password, name, NURSE_ROLE);
    if (strcmp(username, eN->username) == 0)
        printf("Username Correct, ");
    else
        printf("Username Incorrect, ");
    if (strcmp(password, eN->password) == 0)
        printf("Password Correct, ");
    else
        printf("Password Incorrect, ");
    if (strcmp(name, eN->name) == 0)
        printf("Name Correct, ");
    else
        printf("Name Incorrect\n");
    if (eN->r == NURSE_ROLE)
        printf("Role Correct\n");
    else
        printf("Role Incorrect\n");

    printf("\nTEST-003 Saving List To File\n");
    eD->next = eN;
    printf("Saving List: \n");
    printList(eD);
    FILE* file = fopen(FILENAME, "w");
    saveList(file, eD);
    fclose(file);
    deleteList(eD);
    printf("Check file called %s\n", FILENAME);

    printf("\nTEST-004 Loading List From File\n");
    file = fopen(FILENAME, "r");
    ENODE* head = loadList(file);
    printf("Loaded List: \n");
    printList(head);
    fclose(file);

    printf("\nTEST-005 Insert Node Function\n");
    printf("Before Inserting: \n");
    printList(head);
    insertNode(&head, createNode("bob123", "bobpass", "Bob", NURSE_ROLE));
    printf("After Inserting: \n");
    printList(head);

    printf("\nTEST-006 Delete Node Function\n");
    printf("Before Deleting bob123: \n");
    printList(head);
    deleteNode(&head, "bob123");
    printf("After Deleting bob123: \n");
    printList(head);

    deleteList(head);

    return 0;
}