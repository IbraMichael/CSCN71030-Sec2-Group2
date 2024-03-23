#pragma once
#include "Patients.h"

typedef struct pnode {
	PATIENT p;
	struct pnode* next;
}PNODE;

PNODE* createPatientNode(PATIENT p);
void insertPatientNode(PNODE** head);
void deletePatientNode(PNODE* p, PNODE** head);
PNODE* searchPatientByFirstName(PNODE* head, char* first);
PNODE* searchPatientByLastName(PNODE* head, char* last);
PNODE* searchPatientByFullName(PNODE* head, char* first, char* last);
void printPatientList(PNODE* head);
