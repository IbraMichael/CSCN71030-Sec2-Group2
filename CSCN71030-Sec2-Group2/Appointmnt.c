//
//


#define _CRT_SECURE_NO_WARNINGS
#include"Appointment.h"

#define MAX_APPOINTMENTS 2000
Appointment appointment[MAX_APPOINTMENTS];
int appointmentCount = 0;

void saveAppointmentToFile() {
	FILE* file = fopen("appointment.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < appointmentCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            appointment[i].name, appointment[i].description, appointment[i].time,
            appointment[i].location, appointment[i].category);
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
    while (fscanf(file, "%99[^,],%99[^,],%10[^,],%1023[^,],%99[^,],%19[^,],%99[^,],%99[^,],%9[^\n]\n",
        appointment[appointmentCount].name, appointment[appointmentCount].description,
        appointment[appointmentCount].time, appointment[appointmentCount].location,
        appointment[appointmentCount].category) == 9) {
        appointmentCount++;
        if (appointmentCount >= MAX_APPOINTMENTS) {
            printf("Reached max capacity. Some appointment may not be loaded.\n");
            break;
        }
    }
    fclose(file);
}

