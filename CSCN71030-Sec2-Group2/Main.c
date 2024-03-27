#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Patients.h"

#define FILENAME "empdata.txt"

// Function declarations
int authenticateUser(const char* username, const char* password);
void showDoctorDashboard();
void showNurseDashboard();
void showBillingMenu();


int main() {
    char* months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Get current time
    time_t now = time(NULL);
    // Convert time_t to tm struct
    struct tm* current_time = localtime(&now);

    // Print date and time
    printf("Date: %s %d, %d", months[current_time->tm_mon], current_time->tm_mday, current_time->tm_year + 1900);
    printf("\t\t\t\t\t\t\t\t\t\tTime: %02d:%02d:%02d\n", current_time->tm_hour, current_time->tm_min, current_time->tm_sec);


    printf("\n\t\t\t------------------------------------------------------------\n");
    printf("            \t\t\t*** Welcome to Hospital Management System ***\n");
    printf("\t\t\t------------------------------------------------------------\n");

    char username[50];
    char password[50];
    int loginResult;



    printf("\n\t\t\t------------------------------------------------------------\n");
    printf("            \t\t\t***  Please login to your account ***\n");
    printf("\t\t\t------------------------------------------------------------\n");
    printf("\n\n");
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Authenticate the user
    loginResult = authenticateUser(username, password);

    // Check login result and show the respective dashboard
    switch (loginResult) {
    case 1:
        showDoctorDashboard();
        break;
    case 2:
        showNurseDashboard();
        break;
    default:
        printf("Invalid login. Please try again.\n");
        break;
    }

    return 0;
}

// Function to authenticate users
int authenticateUser(const char* username, const char* password) {
    if (strcmp(username, "doctor") == 0 && strcmp(password, "docpass") == 0) {
        return 1; // Doctor
    }
    else if (strcmp(username, "nurse") == 0 && strcmp(password, "nursepass") == 0) {
        return 2; // Nurse
    }
    return 0; // Authentication failed
}



// Function to show the doctor dashboard


void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void showDoctorDashboard()
{
    char choice;
    char searchCriteria[100];
    char healthCardNumber[20];

    do {
        printf("\nHospital Management System\n");
        printf("A) Add Patient\n");
        printf("B) Find Patient - 1)Find, 2)Find and Edit, 3)Find and delete\n");
        printf("C) Print Patients (Sorted by Last Name)\n");
        printf("D) Prescribe Meds\n");
        printf("E) Request Labs\n");
        printf("F) Exit\n");
        printf("Select an option: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'A':
        case 'a':
        { PATIENT patient;

        printf("Enter patient's first name: ");
        scanf("%99s", patient.firstName);
        clearInputBuffer(); // Clear the buffer after using scanf

        printf("Enter patient's last name: ");
        scanf("%99s", patient.lastName);
        clearInputBuffer();

        printf("Enter DOB (YYYY-MM-DD): ");
        scanf("%10s", patient.dob);
        clearInputBuffer();

        // Use fgets for multi-word input fields
        printf("Enter medical history: ");
        fgets(patient.medicalHistory, sizeof(patient.medicalHistory), stdin);
        patient.medicalHistory[strcspn(patient.medicalHistory, "\n")] = 0; // Remove newline character

        printf("Enter contact info: ");
        scanf("%99s", patient.contactInfo);
        clearInputBuffer();

        printf("Enter health card number: ");
        scanf("%19s", patient.healthCardNumber);
        clearInputBuffer();

        printf("Enter family doctor's name: ");
        fgets(patient.familyDoctorName, sizeof(patient.familyDoctorName), stdin);
        patient.familyDoctorName[strcspn(patient.familyDoctorName, "\n")] = 0;

        printf("Enter address: ");
        fgets(patient.address, sizeof(patient.address), stdin);
        patient.address[strcspn(patient.address, "\n")] = 0;

        printf("Enter gender: ");
        fgets(patient.gender, sizeof(patient.gender), stdin);
        patient.gender[strcspn(patient.gender, "\n")] = 0;

        addPatient(patient);
        }
        break;
        case 'B':
        case 'b':
            printf("\nFind Options:\n");
            printf("1) Find\n");
            printf("2) Find and Edit\n");
            printf("3) Find and Delete\n");
            printf("Enter choice: ");
            int choiceTwo;
            scanf("%d", &choiceTwo);
            switch (choiceTwo) {
            case 1:
                printf("Enter search criteria (name or health card number): ");
                scanf("%s", searchCriteria);
                findPatient(searchCriteria);
                break;
            case 2:

                printf("Enter the health card number of the patient you wish to edit: ");
                clearInputBuffer(); // Clear the input buffer to ensure clean input for fgets
                fgets(healthCardNumber, sizeof(healthCardNumber), stdin);
                healthCardNumber[strcspn(healthCardNumber, "\n")] = 0; // Remove the newline character

                displayEditMenu(healthCardNumber);
                break;
            case 3:
                printf("Enter health card number of the patient to delete: ");
                scanf("%s", healthCardNumber);
                deletePatient(healthCardNumber);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
            break;
        case 'C':
        case 'c':
            printf("\nPatients Sorted by Last Name:\n");
            printPatientsSorted("lastName");
            break;
        case 'D':
        case 'd':
            // Prescribe medication TODO
            printf("Functionality to be implemented.\n");
            break;

        case 'E':
        case 'e':
            // Request Lab TODO
            printf("Functionality to be implemented.\n");
            break;
        case 'F':
        case 'f':

            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 'E' && choice != 'E');
}


// Simplified billing menu - Implement as needed
void showBillingMenu()
{
    printf("\n--- Billing Management ---\n");
    printf("Placeholder for billing functionality.\n");
   
}



// Function to show the nurse dashboard
void showNurseDashboard() {
    printf("Welcome, Nurse! Here are your options:\n");
    // Nurse-specific options here
}
