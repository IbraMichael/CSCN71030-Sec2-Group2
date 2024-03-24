#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct diagnosis
{
    int patientId[20];
    char symptoms[80];
    char numSymptoms[100];
    char diagnosis[500];
    char numDiagnosis[1000];
    char treatment[2000];
    char numTreatment[1500];

} Diagnosis;

// void patientDiagnosis(int patientId, char symptoms, int numSymptoms, char diagnosis, int numDiagnosis, char treatment, int numTreatment);
void saveDiagnosisToFile();
void LoadToSchedule();