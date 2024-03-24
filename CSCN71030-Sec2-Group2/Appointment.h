#pragma once


#define PatientName 100
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_LOCATION_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define TIME_IN_STRING_LENGTH 20


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct appointment
{
    char firstName[PatientName];
    char lastName[PatientName];
    char description[MAX_DESCRIPTION_LENGTH];
    char time[TIME_IN_STRING_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    char category[MAX_CATEGORY_LENGTH];

} Appointment;

void saveAppointmentToFile();
void LoadToSchedule();
void addAppointment(const Appointment appointment);
void printAppointmentSorted(const char* sortBy);

