#pragma once
#include "Doctor.h"
#include "Nurse.h"
#include "PList.h"

typedef enum role {
	DOCTOR_ROLE, NURSE_ROLE, ADMIN
}ROLE;

typedef union data {
	Doctor d;
	NURSE n;
}DATA;

typedef struct employee {
	ROLE role;
	DATA data;
	char* username;
	char* password;
	PNODE* Patients;
}EMPLOYEE;

EMPLOYEE createNurseEmployee(NURSE n, char* username, char* password);
EMPLOYEE createDoctorEmployee(Doctor d, char* username, char* password);
void printEmployee(EMPLOYEE e);
