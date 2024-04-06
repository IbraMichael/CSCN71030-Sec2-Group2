// Implementation of patient diagnosis; results will be added, loaded and saved to patient file and history
//it will be stored with a unique Id from the medical provider

#define _CRT_SECURE_NO_WARNINGS
#include"Diagnosis.h"

// Define or declare the variables
#define MAX_DIAGNOSTIC 800
Diagnostic diagnostics[MAX_DIAGNOSTIC];
int diagnosticCount = 0;

// Helper functions to compare patient symptoms
int compareSymptoms(const void* a, const void* b) 
{
    const Diagnostic* pa = (const Diagnostic*)a;
    const Diagnostic* pb = (const Diagnostic*)b;
    return strcmp(pa->Symptoms, pb->Symptoms);
}

// Save the patient diagnosis to file
char* saveDiagnosticToFile()
{
    FILE* file = fopen("diagnostic.txt", "w");
    if (!file) 
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < diagnosticCount; ++i) 
    {
        fprintf(file, "%d,%s,%s,%s,%s\n",
            diagnostics[i].patientId, diagnostics[i].Symptoms, diagnostics[i].numSymptoms,
            diagnostics[i].diagnosis, diagnostics[i].numDiagnosis);
    }
    fclose(file);
}

// Load patient diagnosis to from the file
char* LoadDiagnostic()
{
    FILE* file = fopen("diagnostic.txt", "r");
    if (!file) 
    {
        printf("Error opening file for reading.\n");
        return;
    }
    diagnosticCount = 0;

    while (fscanf(file, "%.9[^,],%99[^,],%99[^,],%99[^,],%99[^\n]\n",
        diagnostics[diagnosticCount].patientId, diagnostics[diagnosticCount].Symptoms, diagnostics[diagnosticCount].numSymptoms,
        diagnostics[diagnosticCount].diagnosis, diagnostics[diagnosticCount].numDiagnosis) == 5) 
    {
        diagnosticCount++;
        if (diagnosticCount >= MAX_DIAGNOSTIC) 
        {
            printf("Reached max capacity. Some diagnostic may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}

// Add patient diagnosis to patient file or history
char* addDiagnostic(const Diagnostic diagnostic) {
    if (diagnosticCount >= MAX_DIAGNOSTIC) 
    {
        printf("Cannot add more diagnostics. Storage full.\n");
        return;
    }
    diagnostics[diagnosticCount++] = diagnostic;
    saveDiagnosticToFile();
}


// Print patient Diagnosis details
char* printDiagnosticSorted(const char* sortBy)
{
    // Load diagnostics from file
    LoadDiagnostic();

    // Assuming compareSymptoms is correctly implemented elsewhere.
    qsort(diagnostics, diagnosticCount, sizeof(Diagnostic), compareSymptoms);

    for (int i = 0; i < diagnosticCount; ++i) 
    {
        printf("---------------------------------------------------\n");
        printf("patientId: %d\n", diagnostics[i].patientId);
        printf("Symptoms: %s\n", diagnostics[i].Symptoms);
        printf("numSymptoms: %s\n", diagnostics[i].numSymptoms);
        printf("Diagnosis: %s\n", diagnostics[i].diagnosis);
        printf("numDiagnosis: %s\n", diagnostics[i].numDiagnosis);
        printf("---------------------------------------------------\n");
    }
}