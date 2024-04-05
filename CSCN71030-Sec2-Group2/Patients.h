#ifdef __cplusplus
extern "C" {
#endif

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#define MAX_PATIENTS 100

    extern int patientCount;


    typedef struct patient {
        char firstName[100];
        char lastName[100];
        char dob[11]; // Format: YYYY-MM-DD
        char medicalHistory[1024];
        char contactInfo[100];
        char healthCardNumber[20];
        char familyDoctorName[100];
        char address[100];
        char gender[10];
        int bills;
    } PATIENT;

    extern PATIENT patients[MAX_PATIENTS];
    // Function prototypes

    void savePatientsToFile();
    int getPatientCount();
    void setPatientCount(int count);
    void loadPatientsFromFile();
    char* addPatient(const PATIENT patient);
    char* deletePatient(const char* healthCardNumber);
    bool findPatient(const char* searchCriteria);
    bool findAndEditPatient(const char* healthCardNumber, char* newFirst, char* newLast, char* newDob, char* newHistory, char* newContact, char* newHealthCard, char* newDoctor, char* newAddress, char* newGender);
    bool printPatientsSorted(const char* sortBy);
    void displayEditMenu(const char* healthCardNumber);


#ifdef __cplusplus
}
#endif