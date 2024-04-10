#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Patients.h"
#include "Appointment.h"
#include "Labs.h"
#include "Prescription.h"
#include "Nurse.h"
#include "EList.h"

#define ADMINPASS "password"
#define ADMINUSER "admin"

// Function declarations
int authenticateUser(const char* username, const char* password, ENODE* head);
void showDoctorDashboard();
void showNurseDashboard();
void showBillingMenu();
void showAdminDashboard(ENODE** head);

int main() {
    srand(time(NULL));

    ENODE* head = NULL;
    const char* filename = "empdata.txt";
    FILE* file = fopen(filename, "r");

    if (file != NULL) {
        head = loadList(file);
        fclose(file); // Close the file after checking
    }
    else {
        printf("File doesn't exist.\n");
        showAdminDashboard(&head);
        file = fopen(filename, "w");
        saveList(file, head);
        fclose(file);
        return;
    }

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
    scanf("%s", &username);

    printf("Enter password: ");
    scanf("%s", &password);

    // Authenticate the user
    loginResult = authenticateUser(username, password, head);

    // Check login result and show the respective dashboard
    switch (loginResult) {
    case 1:
        showDoctorDashboard();
        break;
    case 2:
        showNurseDashboard();
        break;
    case 3:
        showAdminDashboard(&head);
    default:
        printf("Invalid login. Please try again.\n");
        break;
    }
    file = fopen(filename, "w");
    saveList(file, head);
    fclose(file);
    deleteList(head);
    
    return 0;
}

// Function to authenticate users
int authenticateUser(const char* username, const char* password, ENODE* head) {
    ENODE* current = head;
    if (strcmp(username, ADMINUSER) == 0 && strcmp(password, ADMINPASS) == 0)
        return 3;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            if (current->r == 0)
                return 1; // Authentication successful
            if (current->r == 1)
                return 2;
        }
        current = current->next;
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
        printf("D) Meds\n");
        printf("E) Labs\n");
        printf("F) Appointments\n");
        printf("G) Exit\n");
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
   
                printf("\Prescription Options:\n\n");
                printf("1) Prescribe\n");
                printf("2) View Prescription\n");
                printf("Enter choice: ");

                int select;
                scanf("%d", &select);

                switch (select) {
                case 1:
                {
                    Prescription prescription;

                    printf("Enter Patient Id: ");
                    scanf("%99s", &prescription.patientId);
                    clearInputBuffer(); // Clear the buffer after using scanf

                    printf("Enter medication name: ");
                    scanf("%99s", prescription.medicationName);
                    clearInputBuffer();

                    printf("Enter dosage: ");
                    scanf("%99s", prescription.dosage);
                    clearInputBuffer();

                    printf("Enter medication frequency: ");
                    fgets(prescription.frequency, sizeof(prescription.frequency), stdin);
                    prescription.frequency[strcspn(prescription.frequency, "\n")] = 0;

                    printf("Enter medication quantity: ");
                    fgets(prescription.quantity, sizeof(prescription.quantity), stdin);
                    prescription.quantity[strcspn(prescription.quantity, "\n")] = 0;

                    addPrescriptionToFile(prescription);
                    printf("Prescription added successfully.\n");
                }
                break;
                case 2:
                    printf("\Prescription sorted by name:\n");

                    printPrescriptionSorted("medicationName");

                    break;

            

                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
                }
                break;

        case 'E':
        case 'e':
            printf("\Lab Options:\n\n");
            printf("1) Labs\n");
            printf("2) View Labs\n");
            printf("Enter choice: ");

         

            int selectTwo;
            scanf("%d", &selectTwo);

            switch (selectTwo) {
            case 1:
            {
                LAB lab;

                printf("Enter Lab name: ");
                scanf("%99s", &lab.name);
                clearInputBuffer(); // Clear the buffer after using scanf

                printf("Enter Lab cost: ");
                scanf("%99s", lab.cost);
                clearInputBuffer();

                printf("Enter lab time: ");
                fgets(lab.time, sizeof(lab.time), stdin);
                lab.time[strcspn(lab.time, "\n")] = 0;

                printf("Enter Lab category: ");
                fgets(lab.category, sizeof(lab.category), stdin);
                lab.category[strcspn(lab.category, "\n")] = 0;

                addLabs(lab);
                printf("lab added successfully.\n");
            }
            break;
            case 2:
                printf("\Lab sorted by name:\n");
                printLabsSorted("labName");

                break;


            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
            break;
        case 'F':
        case 'f':
            printf("\Appointment Options:\n\n");
            printf("1) Add Appointment\n");
            printf("2) View Appointment\n");
            printf("Enter choice: ");



            int selectThree;
            scanf("%d", &selectThree);

            switch (selectThree) {
            case 1:
            {
                Appointment appointment;


                printf("Enter patient's first name: ");
                scanf("%99s", appointment.firstName);
                clearInputBuffer(); 

                printf("Enter patient's last name: ");
                scanf("%99s", appointment.lastName);
                clearInputBuffer();


                printf("Enter appointment date and time in the following format YYYY-MM-DD HH:MM ");
                fgets(appointment.time, sizeof(appointment.time), stdin);
                appointment.time[strcspn(appointment.time, "\n")] = 0;

                printf("Enter appointment description: ");
                fgets(appointment.description, sizeof(appointment.description), stdin);
                appointment.description[strcspn(appointment.description, "\n")] = 0;

  
                printf("Enter appointment location: ");
                scanf("%99s", appointment.location);
                clearInputBuffer();
           
                printf("Enter appointment category: ");
                fgets(appointment.category, sizeof(appointment.category), stdin);
                appointment.category[strcspn(appointment.category, "\n")] = 0;

                addAppointment(appointment);
                printf("appointment added successfully.\n");
            }
            break;
            case 2:
                printf("\Appointments sorted by date:\n");

                printAppointmentSorted("name");

                break;


            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
            break;
            break;
        case 'G':
        case 'g':

            printf("Exiting...\n");
            main();
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 'G' && choice != 'g');
}


// Simplified billing menu - Implement as needed
void showBillingMenu()
{
    printf("\n--- Billing Management ---\n");
 

    // Assuming PATIENT is defined properly
    PATIENT patient;
    patient.bills = 0; // Initialize patient bills

    // Generate a bill for the patient
    generateBill(&patient);
    printf("Patient's bill: %d\n", patient.bills);

    // Clear a part of the bill
    int payment = 5; // Example payment amount
    clearBill(&patient, payment, false);
    if (patient.bills >= 0) {
        printf("Patient's remaining bill after payment: %d\n", patient.bills);
    }

    return 0;
}



// Function to show the nurse dashboard
void showNurseDashboard() 
{



    int select;
    printf("Welcome, Nurse! Here are your options:\n");

    printf("1)Patient\n");
    printf("2) Bills\n");
    printf("3) Quit/logout\n");
    scanf("%d", &select);


    char choice;
    char searchCriteria[100];
    char healthCardNumber[20];
    switch (select) {
    case 1:


        do {


            printf("\nHospital Management System\n");
            printf("A) Add Patient\n");
            printf("B) Find Patient - 1)Find, 2)Find and Edit, 3)Find and delete\n");
            printf("C) Print Patients (Sorted by Last Name)\n");
            printf("E) Exit\n");
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

                break;
            case 'E':
            case 'e':

                printf("Exiting...\n");
                showNurseDashboard();
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
            }
        } while (choice != 'e' && choice != 'E');

    case 2:
        showBillingMenu();
        break;
    case 3:
        printf("Exiting...\n");
        main();
        break;
    default:
        printf("Invalid choice. Please enter a valid option.\n");
        break;




    }
}

void showAdminDashboard(ENODE** head) {
    int choice2;
    do {
        printf("Admin Dashboard\n1: Add doctor\n2: Add nurse\n3: Delete Employee\n4: Exit\nMake a selection: ");
        scanf(" %d", &choice2);
       
        switch (choice2) {
        case 1: {
            char name[100];
            char username[100];
            char password[100];

            printf("Enter the doctor's name: ");
            scanf("%s", name);
            printf("Enter the doctor's username: ");
            scanf("%s", username);
            printf("Enter the doctor's password: ");
            scanf("%s", password);

            ENODE* e = createNode(username, password, name, 0);

            if (*head == NULL)
                *head = e;
            else {
                e->next = *head;
                *head = e;
            }

            break;
        }
        case 2: {
            char name[100];
            char username[100];
            char password[100];

            printf("Enter the nurse's name: ");
            scanf("%s", name);
            printf("Enter the nurse's username: ");
            scanf("%s", username);
            printf("Enter the nurse's password: ");
            scanf("%s", password);

            ENODE* e = createNode(username, password, name, 1);

            if (*head == NULL)
                *head = e;
            else {
                e->next = *head;
                *head = e;
            }

            break;
        }

        case 3: {
            char username[100]; // Ensure username is properly initialized and allocated
            printf("Enter employee's username: \n");
            scanf("%s", username);
            ENODE* current = *head;
            ENODE* prev = NULL;

            while (current != NULL) {
                // Use strcmp instead of strncmp
                if (strcmp(current->username, username) == 0) {
                    // Node found, delete it
                    if (prev == NULL) {
                        // If the node to be deleted is the head
                        *head = current->next;
                    }
                    else {
                        // If the node to be deleted is not the head
                        prev->next = current->next;
                    }
                    free(current); // Free memory for the node
                    printf("Employee %s deleted\n", username);
                    break;
                }
                prev = current;
                current = current->next;
            }

            
            break;
        }
        case 4:
            printf("Exiting...\n\n");
            FILE* file = fopen("empdata.txt", "w");
            saveList(file, *head);
            fclose(file);
            main();
            break;
        default:
            printf("Invalid Selection\n");
            break;
        }
    } while (choice2 != 4);

    
    return;

   
}

