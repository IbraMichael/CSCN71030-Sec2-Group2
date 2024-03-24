
#define _CRT_SECURE_NO_WARNINGS
#include"Appointment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_APPOINTMENTS 2000

Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

// Helper functions
int compareTime(const void* a, const void* b) {
    const Appointment* pa = (const Appointment*)a;
    const Appointment* pb = (const Appointment*)b;
    return strcmp(pa->time, pb->time);

}

void saveAppointmentToFile() {
	FILE* file = fopen("appointment.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < appointmentCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n",
            appointments[i].firstName, appointments[i].lastName, appointments[i].time, appointments[i].description,
            appointments[i].location, appointments[i].category);
    }
    fclose(file);
}


void LoadToSchedule()
{
    FILE* file = fopen("appointment.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    appointmentCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%99[^\n]\n",
        appointments[appointmentCount].firstName, appointments[appointmentCount].lastName, appointments[appointmentCount].time,
        appointments[appointmentCount].description, appointments[appointmentCount].location,
        appointments[appointmentCount].category) == 6) {
        appointmentCount++;
        if (appointmentCount >= MAX_APPOINTMENTS) {
            printf("Reached max capacity. Some appointment may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}

void addAppointment(const Appointment appointment) {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("Cannot add more labs. Storage full.\n");
        return;
    }
    appointments[appointmentCount++] = appointment;
    saveAppointmentToFile();
}



void printAppointmentSorted(const char* sortBy) {
    // Load labs from file
    LoadToSchedule();

    // Assuming compareTime is correctly implemented elsewhere.
  qsort(appointments, appointmentCount, sizeof(Appointment), compareTime);

    for (int i = 0; i < appointmentCount; ++i) {
        printf("---------------------------------------------------\n");
        printf("Name: %s %s\n", appointments[i].firstName, appointments[i].lastName);
        printf("Time: %s\n", appointments[i].time);
        printf("Description: %s\n", appointments[i].description);
        printf("Location: %s\n", appointments[i].location);
        printf("Category: %s\n", appointments[i].category);
        printf("---------------------------------------------------\n");
    }
}