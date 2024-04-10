#include "nurse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//delete nurse function
void deleteNurse(NURSE* n) {
	free(n);
}
//initnurse function
NURSE* initNurse(char name[MAXNAME]) {
	//allocate memory for the nurse
	NURSE* n = malloc(sizeof(NURSE));
	//set the nurses id and name
	n->id = setID();
	setName(n, name);

	return n;
}

//set id function
int setID() {
	//generate an 8-digit id
	int lower = 10000000;
	int upper = 99999999;
	int id = (rand() % (upper - lower) + lower);
	return id;
}

//setname function
void setName(NURSE* n, char name[MAXNAME]) {
	strncpy_s(n->name, MAXNAME, name, MAXNAME);
}
//gnerate bill function
void generateBill(PATIENT* p) {
	int lower = 50;
	int upper = 1000;
	//generates a bill within the range and adds it to the patients bills
	int bill = (rand() % (upper - lower + 1) + lower);
	p->bills = bill + p->bills;
}

//clear bill function
void clearBill(PATIENT* p, int amount, bool isTest) {
	//When this function is called in the main
	if (isTest == false) {
		//if the user enters more then the amount the user owes
		if (amount > p->bills) {
			printf("The patient gave too much money.\n");
			return;
		}
		else if (amount < 1) {
			printf("The patient used an invalid amount");
			return;
		}
		//subtract the amount from the users bills
		p->bills = p->bills - amount;
	}
	//When this function is called in the tests
	else {
		if (amount > p->bills || amount < 1) {
			return;
		}

		//subtract the amount from the users bills
		p->bills = p->bills - amount;

	}
}