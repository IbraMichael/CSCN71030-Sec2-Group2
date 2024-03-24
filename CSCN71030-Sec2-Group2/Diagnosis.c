// Implementation of patient diagnosis
//

#define _CRT_SECURE_NO_WARNINGS
#include"Diagnosis.h"

#define MAX_DIAGNOSIS 5000
Diagnosis diagnosis[MAX_DIAGNOSIS];
int diagnosisCount = 0;

void saveDiagnosisToFile() {
    FILE* file = fopen("diagnosis.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < diagnosisCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            diagnosis[i].patientId, diagnosis[i].symptoms, diagnosis[i].numSymptoms,
            diagnosis[i].diagnosis, diagnosis[i].numDiagnosis);
    }
    fclose(file);
}


void LoadToSchedule()
{
    FILE* file = fopen("diagnosis.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    diagnosisCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%10[^,],%1023[^,],%99[^,],%19[^,],%99[^,],%99[^,],%9[^\n]\n",
        diagnosis[diagnosisCount].patientId, diagnosis[diagnosisCount].symptoms,
        diagnosis[diagnosisCount].numSymptoms, diagnosis[diagnosisCount].diagnosis,
        diagnosis[diagnosisCount].numDiagnosis) == 0) {
        diagnosisCount++;
        if (diagnosisCount >= MAX_DIAGNOSIS) {
            printf("Reached max capacity. Some diagnosis may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}

void addDiagnosis(const Diagnosis diagnosis) {
    if (diagnosisCount >= MAX_DIAGNOSIS) {
        printf("Cannot add more diagnosis. Storage full.\n");
        return;
    }
    diagnosis[diagnosisCount++] = diagnosis;
    saveDiagnosisToFile();
}



void printDiagnosisSorted(const char* sortBy) {
    // Load diagnosis from file
    LoadToSchedule();

    // Assuming compareDiagnosis is correctly implemented elsewhere.
    qsort(diagnosis, diagnosisCount, sizeof(diagnosis), compareDiagnosis);

    for (int i = 0; i < diagnosisCount; ++i) {
        printf("---------------------------------------------------\n");
        printf("Name: %s %s\n", diagnosis[i].patientId);
        printf("Time: %s\n", diagnosis[i].symptoms);
        printf("Description: %s\n", diagnosis[i].numSymptoms);
        printf("Location: %s\n", diagnosis[i].diagnosis);
        printf("Category: %s\n", diagnosis[i].numDiagnosis);
        printf("---------------------------------------------------\n");
    }
}