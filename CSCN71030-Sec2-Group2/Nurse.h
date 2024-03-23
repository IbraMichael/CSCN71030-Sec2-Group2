#pragma once
#include <stdio.h>
#include <time.h>
#include "Patients.h"
#define MAXNAME 30

typedef struct nurse {
	char name[MAXNAME];
	int id;
	//patient list
}NURSE;

void deleteNurse(NURSE* n);
NURSE initNurse(char name[MAXNAME]);
int setID();
void setName(NURSE* n, char name[MAXNAME]);
void generateBill(PATIENT* p);
void clearBill(PATIENT* n);