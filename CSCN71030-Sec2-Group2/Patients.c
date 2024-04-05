
#include "Patients.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

PATIENT patients[MAX_PATIENTS];

int patientCount = 0;


// Helper functions
int compareNames(const void* a, const void* b) {
    const PATIENT* pa = (const PATIENT*)a;
    const PATIENT* pb = (const PATIENT*)b;
    return strcmp(pa->lastName, pb->lastName);
}

void savePatientsToFile() {
    FILE* file = fopen("patients.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < patientCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            patients[i].firstName, patients[i].lastName, patients[i].dob,
            patients[i].medicalHistory, patients[i].contactInfo, patients[i].healthCardNumber,
            patients[i].familyDoctorName, patients[i].address, patients[i].gender);
    }
    fclose(file);
}

void loadPatientsFromFile() {
    FILE* file = fopen("patients.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    patientCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%10[^,],%1023[^,],%99[^,],%19[^,],%99[^,],%99[^,],%9[^\n]\n",
        patients[patientCount].firstName, patients[patientCount].lastName,
        patients[patientCount].dob, patients[patientCount].medicalHistory,
        patients[patientCount].contactInfo, patients[patientCount].healthCardNumber,
        patients[patientCount].familyDoctorName, patients[patientCount].address,
        patients[patientCount].gender) == 9) {
        patientCount++;
        if (patientCount >= MAX_PATIENTS) {
            printf("Reached max capacity. Some patients may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}
char* addPatient(const PATIENT patient) {
    if (patientCount >= MAX_PATIENTS) {
        return "Cannot add more patients. Storage full.";
    }
    patients[patientCount++] = patient;
    savePatientsToFile();
    return "Patient added";
}

int getPatientCount() {
    return patientCount;
}

void setPatientCount(int count) {
    patientCount = count;
}

char* deletePatient(const char* healthCardNumber) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].healthCardNumber, healthCardNumber) == 0) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            savePatientsToFile();
            return "Patient deleted";
        }
    }
    return "Patient not found";
}

bool findPatient(const char* searchCriteria) {
    bool found = false;
    for (int i = 0; i < patientCount; i++) {
        if (strstr(patients[i].firstName, searchCriteria) || strstr(patients[i].lastName, searchCriteria) ||
            strstr(patients[i].healthCardNumber, searchCriteria)) {
            printf("Patient found: %s %s, DOB: %s\n", patients[i].firstName, patients[i].lastName, patients[i].dob);
            found = true;
        }
    }
    if (!found) {
        printf("No patient found with the criteria: %s\n", searchCriteria);
    }
}

bool findAndEditPatient(const char* healthCardNumber, char* newFirst, char* newLast, char* newDob, char* newHistory, char* newContact, char* newHealthCard, char* newDoctor, char* newAddress, char* newGender) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].healthCardNumber, healthCardNumber) == 0) {
            if (newFirst[0] != '\0') strncpy(patients[i].firstName, newFirst, sizeof(patients[i].firstName) - 1);
            if (newLast[0] != '\0') strncpy(patients[i].lastName, newLast, sizeof(patients[i].lastName) - 1);
            if (newDob[0] != '\0') strncpy(patients[i].dob, newDob, sizeof(patients[i].dob) - 1);
            if (newHistory[0] != '\0') strncpy(patients[i].medicalHistory, newHistory, sizeof(patients[i].medicalHistory) - 1);
            if (newContact[0] != '\0') strncpy(patients[i].contactInfo, newContact, sizeof(patients[i].contactInfo) - 1);
            if (newHealthCard[0] != '\0') strncpy(patients[i].healthCardNumber, newHealthCard, sizeof(patients[i].healthCardNumber) - 1);
            if (newDoctor[0] != '\0') strncpy(patients[i].familyDoctorName, newDoctor, sizeof(patients[i].familyDoctorName) - 1);
            if (newAddress[0] != '\0') strncpy(patients[i].address, newAddress, sizeof(patients[i].address) - 1);
            if (newGender[0] != '\0') strncpy(patients[i].gender, newGender, sizeof(patients[i].gender) - 1);

            printf("\n Patient  %s %s has been updated.\n", patients[i].firstName, patients[i].lastName);
            savePatientsToFile(); // Save changes to the file
            return;
        }
    }
    printf("Patient with health card number %s not found.\n", healthCardNumber);
}

void displayEditMenu(const char* healthCardNumber) {
    char newFirst[100] = "", newLast[100] = "", newDob[11] = "", newHistory[1024] = "", newContact[100] = "", newHealthCard[20] = "", newDoctor[100] = "", newAddress[100] = "", newGender[10] = "";
    int choice;
    bool patientFound = false;

    // First, find the patient to display their name
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].healthCardNumber, healthCardNumber) == 0) {
            printf("Editing information for: %s %s\n", patients[i].firstName, patients[i].lastName);
            patientFound = true;
            break;
        }
    }

    if (!patientFound) {
        printf("Patient with health card number %s not found.\n", healthCardNumber);
        return;
    }

    printf("Select the information you want to edit:\n");
    printf("1. First Name\n2. Last Name\n3. Date of Birth\n4. Medical History\n5. Contact Information\n6. Health Card Number\n7. Family Doctor Name\n8. Address\n9. Gender\n0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // Consume the newline character after scanf

    switch (choice) {
    case 1:
        printf("Enter new first name: ");
        fgets(newFirst, sizeof(newFirst), stdin);
        newFirst[strcspn(newFirst, "\n")] = 0;
        break;
    case 2:
        printf("Enter new last name: ");
        fgets(newLast, sizeof(newLast), stdin);
        newLast[strcspn(newLast, "\n")] = 0;
        break;
    case 3:
        printf("Enter new date of birth (YYYY-MM-DD): ");
        fgets(newDob, sizeof(newDob), stdin);
        newDob[strcspn(newDob, "\n")] = 0;
        break;
    case 4:
        printf("Enter new medical history: ");
        fgets(newHistory, sizeof(newHistory), stdin);
        newHistory[strcspn(newHistory, "\n")] = 0;
        break;
    case 5:
        printf("Enter new contact information: ");
        fgets(newContact, sizeof(newContact), stdin);
        newContact[strcspn(newContact, "\n")] = 0;
        break;
    case 6:
        printf("Enter new health card number: ");
        fgets(newHealthCard, sizeof(newHealthCard), stdin);
        newHealthCard[strcspn(newHealthCard, "\n")] = 0;
        break;
    case 7:
        printf("Enter new family doctor name: ");
        fgets(newDoctor, sizeof(newDoctor), stdin);
        newDoctor[strcspn(newDoctor, "\n")] = 0;
        break;
    case 8:
        printf("Enter new address: ");
        fgets(newAddress, sizeof(newAddress), stdin);
        newAddress[strcspn(newAddress, "\n")] = 0;
        break;
    case 9:
        printf("Enter new gender: ");
        fgets(newGender, sizeof(newGender), stdin);
        newGender[strcspn(newGender, "\n")] = 0;
        break;
    case 0:
        printf("Exiting edit menu.\n");
        return;
    default:
        printf("Invalid choice. Please try again.\n");
        return;
    }

    findAndEditPatient(healthCardNumber, newFirst, newLast, newDob, newHistory, newContact, newHealthCard, newDoctor, newAddress, newGender);
}




bool printPatientsSorted(const char* sortBy) {
    // Load patients from file
    loadPatientsFromFile();

    // Sort patients by last name
    qsort(patients, patientCount, sizeof(PATIENT), compareNames);

    // Print sorted patients
    for (int i = 0; i < patientCount; ++i) {
        printf("\---------------------------------------------------\n");
        printf("Name: %s %s\n", patients[i].firstName, patients[i].lastName);
        printf("DOB: %s\n", patients[i].dob);
        printf("Medical History: %s\n", patients[i].medicalHistory);
        printf("Contact Info: %s\n", patients[i].contactInfo);
        printf("Health Card Number: %s\n", patients[i].healthCardNumber);
        printf("Family Doctor: %s, Address: %s\n", patients[i].familyDoctorName, patients[i].address);
        printf("Address: %s\n", patients[i].address);
        printf("Gender: %s\n", patients[i].gender);
        printf("---------------------------------------------------\n");
    }
}
