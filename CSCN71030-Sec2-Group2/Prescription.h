#pragma once


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prescription
{
    char patientId[80];
    char medicationName[80];
    char dosage[60];
    char frequency[1000];
    char quantity[500];

} Prescription;

//void Prescription(int patientId, char medicationName[], char dosage[], char frquency[], char quantity[]);
void savePrescriptionToFile();
void addPrescriptionToFile(const Prescription prescription);
void Loadprescription();
void printPrescrptionSorted(const char* sortBy);

