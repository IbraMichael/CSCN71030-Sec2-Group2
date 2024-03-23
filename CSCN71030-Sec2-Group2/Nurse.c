#include "nurse.h"

//delete nurse function
void deleteNurse(NURSE* n) {
	free(n);
}
//initnurse function
NURSE initNurse(char name[MAXNAME]) {
	//allocate memory for the nurse
	NURSE* n = (NURSE*)malloc(sizeof(NURSE));
	//set the nurses id and name
	n->id = setID();
	setName(n, name);

}
//set id function
int setID() {
	//generate an 8-digit id
	int lower = 10000000;
	int upper = 99999999;
	int id = (rand() % (upper - lower + 1) + lower);
	return id;
}

//setname function
void setName(NURSE* n, char name[MAXNAME]) {
	strncpy(&(n->name), &name, MAXNAME);
}

void generateBill(PATIENT* p) {
	int lower = 50;
	int upper = 1000;
	int bill = (rand() % (upper - lower + 1) + lower);
	p->bills = bill + p->bills;
}

void clearBill(PATIENT* p, int amount) {
	if (amount > p->bills) {
		printf("The patient gave too much money.\n");
		return NULL;
	}
	else if (amount < 1) {
		printf("The patient used an invalid amount");
	}
	else {
		p->bills = p->bills - amount;
	}
}