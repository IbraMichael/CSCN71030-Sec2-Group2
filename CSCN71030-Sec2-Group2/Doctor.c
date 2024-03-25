// CSCN71030-Sec2-24W
// Group 2
// Implementation of a hospital management software.
// Conpiling Doctor ()
// Evalyne Juan

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "Doctor.h"

// Define your doctor struct
#define MAX_DOCTORS 200
Doctor doctors[MAX_DOCTORS];
int doctorCount = 0;

// Helper functions for scheduled patient appointment
int compareId(const void* a, const void* b)
{
    const Doctor* pa = (const Doctor*)a;
    const Doctor* pb = (const Doctor*)b;
    return strcmp(pa->Id, pb->Id);

}

// 
void AddDoctor(const Doctor doctor) 
{
    if (doctorCount >= MAX_DOCTORS)
    {
        printf("Cannot add more labs. Storage full.\n");
        return;
    }
    doctors[doctorCount++] = doctor;
    savedDoctorToFile();
}

//
void saveDoctorToFile() 
{
    FILE* file = fopen("doctor.txt", "w");
    if (!file)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < doctorCount; ++i)
    {
        fprintf(file, "%d,%s,%s\n",
            doctors[i].Name, doctors[i].Id, doctors[i].Specialization);
    }
    fclose(file);
}

//
void LoadDoctor() 
{
    FILE* file = fopen("doctor.txt", "r");
    if (!file)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    doctorCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%99[^\n]\n",
        doctors[doctorCount].Name, doctors[doctorCount].Id, doctors[doctorCount].Specialization) == 3)
    {
        doctorCount++;
        if (doctorCount >= MAX_DOCTORS)
        {
            printf("Reached max capacity. Some doctor may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}

//
void SearchDoctorByName(char* Name) 
{
    for (int i = 0; i < doctorCount; ++i) 
    {
        if (strcmp(doctors[i].Name, Name) == 0) 
        {
            fprintf("Doctor Id: %d, Name: %s, Specialization: %s\n", doctors[i].Id,
                doctors[i].Name, doctors[i].Specialization);
            doctorCount = 1;
        }
    }
    if (!doctorCount) 
    {
        printf("Doctor not found.\n");
    }
}

//
void SearchDoctorBySpecialization(char* Specialization) 
{
    for (int i = 0; i < doctorCount; ++i)
    {
        if (strcmp(doctors[i].Specialization, Specialization ) == 0)
        {
            fprintf("Doctor Id: %d, Name: %s, Specialization: %s\n", doctors[i].Id,
                doctors[i].Name, doctors[i].Specialization);
            doctorCount = 1;
        }
    }
    if (!doctorCount)
    {
        printf("No Doctors found with the given specialization,\n");
    }
}

//
void printDoctorSorted(const char* sortBy) 
{
        // Load labs from file
        LoadDoctor();

        // Assuming compareTime is correctly implemented elsewhere.
        qsort(doctors, doctorCount, sizeof(Doctor), compareId);

        for (int i = 0; i < doctorCount; ++i)
        {
            printf("---------------------------------------------------\n");
            printf("ID: %d\n", doctors[i].Id);
            printf("Name: %s\n", doctors[i].Name);
            printf("Specialization: %s\n", doctors[i].Specialization);
            printf("---------------------------------------------------\n");
        }
   
}