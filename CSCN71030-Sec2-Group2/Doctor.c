// CSCN71030-Sec2-24W
// Group 2
// Implementation of a hospital management software.
// Conpiling Doctor ()
// Evalyne Juan

#include "Doctor.h"
#define _CRT_SECURE_NO_WARNINGS

// Define your doctor struct
#define MAX_DOCTORS 200
Doctor doctors[MAX_DOCTORS];
int doctorCount = 0;

// Helper functions for scheduled patient appointment
int compareId(const void* a, const void* b)
{
    const Doctor* pa = (const Doctor*)a;
    const Doctor* pb = (const Doctor*)b;
    return strcmp(pa->doctorId, pb->doctorId);

}

// 
char* AddDoctor(const Doctor doctor) 
{
    if (doctorCount >= MAX_DOCTORS)
    {
        printf("Cannot add more labs. Storage full.\n");
        return;
    }
    doctors[doctorCount++] = doctor;
    SaveDoctorToFile();
}

//
bool SaveDoctorToFile() 
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
            doctors[i].Name, doctors[i].doctorId, doctors[i].Specialization, doctors[i].Contact);
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
        doctors[doctorCount].Name, doctors[doctorCount].doctorId, doctors[doctorCount].Specialization, doctors[doctorCount].Contact) == 3)
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
char* SearchDoctorByName(char* Name) 
{
    for (int i = 0; i < doctorCount; ++i) 
    {
        if (strcmp(doctors[i].Name, Name) == 0) 
        {
            fprintf("Doctor Id: %d, Name: %s, Specialization: %s\n", doctors[i].doctorId,
                doctors[i].Name, doctors[i].Specialization, doctors[i].Contact);
            doctorCount = 1;
        }
    }
    if (!doctorCount) 
    {
        printf("Doctor not found.\n");
    }
}

//
char* SearchDoctorBySpecialization(char* Specialization) 
{
    for (int i = 0; i < doctorCount; ++i)
    {
        if (strcmp(doctors[i].Specialization, Specialization ) == 0)
        {
            fprintf("Doctor Id: %d, Name: %s, Specialization: %s\n", doctors[i].doctorId,
                doctors[i].Name, doctors[i].Specialization, doctors[i].Contact);
            doctorCount = 1;
        }
    }
    if (!doctorCount)
    {
        printf("No Doctors found with the given specialization,\n");
    }
}

//
char* PrintDoctorSorted(const char* sortBy) 
{
        // Load labs from file
        LoadDoctor();

        // Assuming compareTime is correctly implemented elsewhere.
        qsort(doctors, doctorCount, sizeof(Doctor), compareId);

        for (int i = 0; i < doctorCount; ++i)
        {
            printf("---------------------------------------------------\n");
            printf("ID: %d\n", doctors[i].doctorId);
            printf("Name: %s\n", doctors[i].Name);
            printf("Specialization: %s\n", doctors[i].Specialization);
            printf("Contact: %s\n", doctors[i].Contact);
            printf("---------------------------------------------------\n");
        }
   
}