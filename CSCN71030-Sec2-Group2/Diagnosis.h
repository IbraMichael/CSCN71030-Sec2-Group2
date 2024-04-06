#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining structures using typedef  struct data type
typedef struct diagnostic
{
    int patientId[20];
    char Symptoms[80];
    char numSymptoms[100];
    char diagnosis[500];
    char numDiagnosis[1000];
    

} Diagnostic;

// Functions for patient diagnosis
char* saveDiagnosticToFile();
char* LoadDiagnostic();
char* addDiagnostic(const Diagnostic diagnostic);
char* printDiagnosticSorted(const char* sortBy);