#pragma once


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define your data type using typedef sturct
typedef struct prescription
{
    char patientId[80];
    char medicationName[80];
    char dosage[60];
    char frequency[1000];
    char quantity[500];

} Prescription;

// Functions for medical prescription
void savePrescriptionToFile();
void addPrescriptionToFile(const Prescription prescription);
void LoadPrescription();
void printPrescrptionSorted(const char* sortBy);

