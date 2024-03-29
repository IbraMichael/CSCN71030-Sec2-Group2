#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include <string.h>


#define MAX_NAME 30
#define MAX_ID 20
#define MAX_SPECIALIZATION_LENGTH 60
#define MAX_DEPARTMENT 100

// Defining the doctor structure
typedef struct doctor{
	int Id;
	char Name[MAX_NAME];
	char Specialization[MAX_SPECIALIZATION_LENGTH];
	
} Doctor;

// functions for 
void AddDoctor(const Doctor doctor);
void saveDoctorToFile();
void LoadDoctor();
void printDoctorSorted(const char* sortBy);
void SearchDoctorByName(char* Name);
void SearchDoctorBySpecialization(char* specialization);





