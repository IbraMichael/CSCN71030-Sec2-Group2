#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>

typedef struct patient {
    char firstName[100];
    char lastName[100];
    char dob[11]; // Format: YYYY-MM-DD
    char medicalHistory[1024];
    char contactInfo[100];
    char healthCardNumber[20];
    char familyDoctorName[100];
    char address[100];
    char gender[10];
} PATIENT;

// Function prototypes
void loadPatientsFromFile();
void addPatient(const PATIENT patient);
bool deletePatient(const char* healthCardNumber);
void findPatient(const char* searchCriteria);
void findAndEditPatient(const char* healthCardNumber, char* newFirst, char* newLast, char* newDob, char* newHistory, char* newContact, char* newHealthCard, char* newDoctor, char* newAddress, char* newGender);
void printPatientsSorted(const char* sortBy);
void displayEditMenu(const char* healthCardNumber);
