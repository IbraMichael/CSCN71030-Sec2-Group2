
#define _CRT_SECURE_NO_WARNINGS
#include"Prescription.h"



#define MAX_PRESCRIPTION 3000
Prescription prescriptions[MAX_PRESCRIPTION];
int prescriptionCount = 0;

// Helper functions
int compareMedsNames(const void* a, const void* b) {
    const Prescription* pa = (const Prescription*)a;
    const Prescription* pb = (const Prescription*)b;
    return strcmp(pa->medicationName, pb->medicationName);
}

void savePrescriptionToFile() {
    FILE* file = fopen("meds.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < prescriptionCount; ++i) {
        fprintf(file, "%s,%s,%s,%s\n",
            prescriptions[i].patientId, prescriptions[i].medicationName, prescriptions[i].dosage,
            prescriptions[i].frequency, prescriptions[i].quantity);
    }
    fclose(file);
}


void Loadprescription()
{
    FILE* file = fopen("meds.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    prescriptionCount = 0;

    while (fscanf(file,"%99[^,],%99[^,],%99[^,],%99[^\n]\n"
        ,
        prescriptions[prescriptionCount].patientId, prescriptions[prescriptionCount].medicationName,
        prescriptions[prescriptionCount].frequency, prescriptions[prescriptionCount].quantity) == 4)
    {
        prescriptionCount++;
        if (prescriptionCount >= MAX_PRESCRIPTION) 
        {
            printf("Reached max capacity. Some appointment may not be loaded.\n");
            break;
        }
    }
    fclose(file);

}
void addPrescriptionToFile(const Prescription prescription) {
    if (prescriptionCount >= MAX_PRESCRIPTION) {
        printf("Cannot add more prescriptions. Storage full.\n");
        return;
    }
    prescriptions[prescriptionCount++] = prescription; 
    savePrescriptionToFile();
}



void printPrescrptionSorted(const char* sortBy) {
    // Load labs from file
    Loadprescription();

    // Sort labs by name
    qsort(prescriptions, prescriptionCount, sizeof(Prescription), compareMedsNames);

    for (int i = 0; i < prescriptionCount; ++i) {
        printf("\---------------------------------------------------\n");
        printf("Patient Id: %s\n", prescriptions[i].patientId);
        printf("Medication Name: %s\n", prescriptions[i].medicationName);
        printf("Frequency: %s\n", prescriptions[i].frequency);
        printf("Quantity: %s\n", prescriptions[i].quantity);
        printf("---------------------------------------------------\n");
    }
}
