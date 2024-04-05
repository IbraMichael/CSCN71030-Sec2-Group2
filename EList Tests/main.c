#include <stdio.h>
#include <string.h>

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

    return 0;
}