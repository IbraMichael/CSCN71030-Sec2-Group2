#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define FILENAME "testdata.txt"
#define MAXNAME 30
void initNurseTest_01();
void setIDTest_01();
void setIDTest_02();
void clearBillTest_01();
void clearBillTest_02();
void clearBillTest_03();
void generateBillTest_01();

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

typedef struct nurse {
    char name[MAXNAME];
    int id;
}NURSE;

typedef struct patient {
    char firstName[100];
    char lastName[100];
    char dob[11]; // Format: YYYY-MM-DD
    char medicalHistory[1024];
    char contactInfo[100];
    char healthCardNumber[20];
    char familyDoctorName[100];
    char address[100];
    char gender[10];
    int bills;
} PATIENT;

extern ENODE* createNode(char* username, char* password, char* name, int role);
extern void saveList(FILE* file, ENODE* head);
extern ENODE* loadList(FILE* file);
extern void deleteNode(ENODE** headPtr, char username[100]);
extern void deleteList(ENODE* head);
extern void printList(ENODE* head);
extern ENODE* searchNode(ENODE* head, char* username);
extern void insertNode(ENODE** head, ENODE* newNode);

extern void deleteNurse(NURSE* n);
extern NURSE* initNurse(char name[MAXNAME]);
extern int setID();
extern void setName(NURSE* n, char name[MAXNAME]);
extern void generateBill(PATIENT* p);
extern void clearBill(PATIENT* n, int amount);

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
    if (eD->r == DOCTOR_ROLE)
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

    //David's Tests
    printf("\nDavid's Tests\n");
    initNurseTest_01();
    setIDTest_01();
    setIDTest_02();
    clearBillTest_01();
    clearBillTest_02();
    clearBillTest_03();
    generateBillTest_01();

    return 0;
}
//Test for checking if two chars are the same
void assert_AreEqualChar(char* c1, char* c2, char* messege) {
    int result = strcmp(c1, c2);
    if (result == 0) {
        printf("Test Passed\n");
    }
    else {
        printf("Test Failed, Expected %s, Actual %s. Error: %s\n", c1, c2, messege);
    }
}
//Test for checking if two ints are the same
void assert_AreEqualInt(int a, int b, char* messege) {

    if (a == b) {
        printf("Test Passed\n");
    }
    else {
        printf("Test Failed, Expected %d, Actual %d. Error: %s\n", a, b, messege);
    }
}
//Test for checking if a statement is true
void assert_IsTrue(bool b, char* messege) {
    if (b == true) {
        printf("Test Passed\n");
    }
    else {
        printf("Test Failed, Expected True, Actual False. Error: %s\n", messege);
    }
}
//Initializing nurse test
void initNurseTest_01() {
    {
        printf("\ninitNurseTest_01 ");
        NURSE* n = initNurse("John");

        assert_AreEqualChar("John", n->name, "Nurse initialized failed");
    }
}
//Set ID test The ID is less more required
void setIDTest_01() {
    {
        printf("\nsetIDTest_01 ");
        int ID = setID();

        assert_IsTrue(ID <= 99999999, "ID was too high");
    }
}
//Set ID test for when The ID is less then required
void setIDTest_02() {
    {
        printf("\nsetIDTest_02 ");
        int ID = setID();

        assert_IsTrue(ID >= 10000000, "ID was too low");
    }
}
//Set name test
void SetNameTest_01() {
    printf("\nSetNameTest_01 ");
    NURSE* n = initNurse("John");
    setName(n, "Joe");

    assert_AreEqualChar("Joe", n->name, "Name was not set");
}
//Clear bill test for when the user enters a number less than 1
void clearBillTest_01()
{
    printf("\nclearBillTest_01 ");
    PATIENT p;
    memcpy(p.address, "h", 2);
    memcpy(p.contactInfo, "h", 2);
    memcpy(p.dob, "h", 2);
    memcpy(p.familyDoctorName, "h", 2);
    memcpy(p.firstName, "h", 2);
    memcpy(p.lastName, "h", 2);
    memcpy(p.gender, "h", 2);
    memcpy(p.healthCardNumber, "h", 2);
    memcpy(p.medicalHistory, "h", 2);
    p.bills = 100;

    clearBill(&p, 0, true);
    assert_AreEqualInt(100, p.bills, "Money was incorrectly cleared");
}
//Clear bill test for when the user enters a number more than the amount the user owes
void clearBillTest_02()
{
    printf("\nclearBillTest_02 ");
    PATIENT p;
    memcpy(p.address, "h", 2);
    memcpy(p.contactInfo, "h", 2);
    memcpy(p.dob, "h", 2);
    memcpy(p.familyDoctorName, "h", 2);
    memcpy(p.firstName, "h", 2);
    memcpy(p.lastName, "h", 2);
    memcpy(p.gender, "h", 2);
    memcpy(p.healthCardNumber, "h", 2);
    memcpy(p.medicalHistory, "h", 2);
    p.bills = 100;

    clearBill(&p, 101, true);
    assert_AreEqualInt(100, p.bills, "Bills were incorrectly cleared");

}
//Clear bill test for when the user enters correct amount
void clearBillTest_03()
{
    printf("\nclearBillTest_03 ");
    PATIENT p;
    memcpy(p.address, "h", 2);
    memcpy(p.contactInfo, "h", 2);
    memcpy(p.dob, "h", 2);
    memcpy(p.familyDoctorName, "h", 2);
    memcpy(p.firstName, "h", 2);
    memcpy(p.lastName, "h", 2);
    memcpy(p.gender, "h", 2);
    memcpy(p.healthCardNumber, "h", 2);
    memcpy(p.medicalHistory, "h", 2);
    p.bills = 100;

    clearBill(&p, 10, true);
    assert_AreEqualInt(90, p.bills, "Bills were incorrectly cleared");
}
//generate bill test 
void generateBillTest_01()
{
    printf("\ngenerateBillTest_01 ");
    PATIENT p;
    memcpy(p.address, "h", 2);
    memcpy(p.contactInfo, "h", 2);
    memcpy(p.dob, "h", 2);
    memcpy(p.familyDoctorName, "h", 2);
    memcpy(p.firstName, "h", 2);
    memcpy(p.lastName, "h", 2);
    memcpy(p.gender, "h", 2);
    memcpy(p.healthCardNumber, "h", 2);
    memcpy(p.medicalHistory, "h", 2);
    p.bills = 0;

    generateBill(&p);
    assert_IsTrue(p.bills > 0, "A bill was incorrectly generated");
}