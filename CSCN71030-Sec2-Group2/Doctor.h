#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX_NAME 30
#define MAX_ID 20
#define MAX_SPECIALIZATION_LENGTH 60
#define MAX_DEPARTMENT 100

// Defining the doctor structure
typedef struct doctor{
	char doctorId;
	char Name[MAX_NAME];
	char Specialization[MAX_SPECIALIZATION_LENGTH];
	int Contact;
	
} Doctor;

// functions for 
char* AddDoctor(const Doctor doctor);
char* SaveDoctorToFile();
void LoadDoctor();
char* PrintDoctorSorted(const char* sortBy);
char* SearchDoctorByName(char* Name);
char* SearchDoctorBySpecialization(char* specialization);





