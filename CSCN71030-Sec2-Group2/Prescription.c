//
//

#define _CRT_SECURE_NO_WARNINGS
#include"Prescription.h"

#define MAX_PRESCRIPTION 3000
Prescription prescription[MAX_PRESCRIPTION];
int prescriptionCount = 0;

void savePrescriptionToFile() {
    FILE* file = fopen("prescription.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < prescriptionCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            prescription[i].patientId, prescription[i].medicationName, prescription[i].dosage,
            prescription[i].frequency, prescription[i].quantity);
    }
    fclose(file);
}


void LoadToSchedule()
{
    FILE* file = fopen("prescription.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    prescriptionCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%10[^,],%1023[^,],%99[^,],%19[^,],%99[^,],%99[^,],%9[^\n]\n",
        prescription[prescriptionCount].patientId, prescription[prescriptionCount].medicationName,
        prescription[prescriptionCount].frequency, [prescriptionCount].quantity) == 9) {
        prescriptionCount++;
        if (prescriptionCount >= MAX_PRESCRIPTION) {
            printf("Reached max capacity. Some appointment may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}