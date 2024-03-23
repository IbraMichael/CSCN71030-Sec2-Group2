#pragma once


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prescription
{
    int patientId [20];
    char medicationName[80];
    char dosage[60];
    char frequency[1000];
    char quantity[500];

} Prescription;

//void Prescription(int patientId, char medicationName[], char dosage[], char frquency[], char quantity[]);
void savePrescriptionToFile();
void LoadToSchedule();
