#pragma once
#ifndef nurse_h
#define nurse_h

#include <stdio.h>
#include <time.h>
#include "Patients.h"
#include <stdbool.h>
#define MAXNAME 30
//nurse struct
typedef struct nurse {
	char name[MAXNAME];
	int id;
}NURSE;

void deleteNurse(NURSE* n);
NURSE* initNurse(char name[MAXNAME]);
int setID();
void setName(NURSE* n, char name[MAXNAME]);
void generateBill(PATIENT* p);
void clearBill(PATIENT* n, int amount, bool isTest);

#endif