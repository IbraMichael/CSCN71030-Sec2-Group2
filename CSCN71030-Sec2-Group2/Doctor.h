#pragma once
#include"Doctor.c"
#define _CRT_SECURE_NO_WARNINGS


#define MAX_PATIENTS 500
#define MAX_HISTORY 200

typedef struct {
	int Id;
	char Name[40];
	char address[100];
	char symptoms[MAX_HISTORY];
	int numSynptoms;
	char diagnosis[MAX_HISTORY];
	int numDiagnosis;
	char prescriptions[MAX_HISTORY];
	int numPrescriptions;
	char testName[100];
	int testDate[30];
	char date[20];
	int providerId;
	char type[50];

} Doctor;



// Arrays to store patients and their histories
struct Prescription Prescription[MAX_HISTORY];
struct labtest LabTest[MAX_HISTORY];
struct diagnosis Diagnosis[MAX_HISTORY];
struct appointment Appointment[MAX_HISTORY];

// Functions
void orderLabTest( int patientId[], char testName[], int testDate[]) {}
void prescribeMedication(int patientId, char medicationName[], char dosage[], char frquency[], char duration[]){}
void patientDiagnosis(int patientId, char symptoms, int numSymptoms, char diagnosis, int numDiagnosis, char treatment, int numTreatment) {}
void scheduleAppointment(int patientId, char date[], int providerId, char type[]) {}



