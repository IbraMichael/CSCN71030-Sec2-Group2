#pragma once
#include "Employee.h"

typedef struct Enode {
	EMPLOYEE e;
	struct Enode* next;
}ENODE;

ENODE* createENode(EMPLOYEE e);
void insertENode(ENODE** head, ENODE* newNode);
void searchENode(ENODE* head, char* username);
void deleteENode(ENODE* toDelete, ENODE** head);
void saveListToFile(ENODE* head);
void loadListFromFile(ENODE* head);