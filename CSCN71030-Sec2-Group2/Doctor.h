#pragma once
#include"Doctor.c"

// Define a struct for a doctor

typedef struct {
	char Name[50];
	int age;
	char gender;
	int diagnosis[100];

} Doctor;

// Function prototypes
void addDoctor(Doctor *doctors, int* numDoctors);
void displayDoctors(Doctor* doctors, int numDoctors);

