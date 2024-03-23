#pragma once
#include"Doctor.c"

#define MAX_PATIENTS 500
#define MAX_HISTORY 200

// Define a struct for a doctor

struct Patients {
	char Name[40];
	int age;
	char address[300];
	int id;

};

// Structure to represent patient history
struct History {
	int patientID;
	char symptoms[MAX_HISTORY][200];
	int numSynptoms;
	char diagnosis[MAX_HISTORY][200];
	int numDiagnosis;
	char prescriptions[MAX_HISTORY][200];
	int numPrescriptions;
};

// Arrays to store patients and their histories
struct Patient patients[MAX_PATIENTS];
struct History history[MAX_PATIENTS];

// Functions
void addPatient(int id, char name[], char address[], int age) {}
void addPatientHistory(int id, char symptom[200], int numSymptoms, char diagnosis[200], int prescription[200], int numPrescriptions){}
void displayPatient(int id){}
void displayPatientHistory(int id){}


