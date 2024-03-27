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
    char diagnostic[500];
    char numDiagnostic[1000];
    

} Diagnostic;

// Functions for patient diagnosis
void saveDiagnosticToFile();
void LoadDiagnostic();
void addDiagnostic(const Diagnostic diagnostic);
void printDiagnosticSorted(const char* sortBy);