#pragma once
#include "Doctor.h"

typedef enum role {
	DOCTOR, NURSE, ADMIN
}ROLE;

typedef union data {
	Doctor d;
	Nurse n;
}DATA;

typedef struct employee {
	ROLE role;
	DATA data;
	int id;
};