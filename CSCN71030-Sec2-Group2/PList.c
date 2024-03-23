#include "PList.h"
#include <stdlib.h>

PNODE* createPatientNode(PATIENT p) {
	PNODE* p1 = (PNODE*)malloc(sizeof(PNODE));
	p1->p = p;
	p1->next = NULL;
	return p1;
}
void insertPatientNode(PNODE** head, PNODE newNode) {
	newNode.next = head;
	head = newNode;
}
void deletePatientNode(PNODE* p, PNODE** head) {

}
PNODE* searchPatientByFirstName(PNODE* head, char* first) {

}
PNODE* searchPatientByLastName(PNODE* head, char* last) {

}
PNODE* searchPatientByFullName(PNODE* head, char* first, char* last) {

}
void printPatientList(PNODE* head) {

}