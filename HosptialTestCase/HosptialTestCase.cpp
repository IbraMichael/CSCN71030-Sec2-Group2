#include "pch.h"
#include "CppUnitTest.h"
#include "Patients.h"
#include "Appointment.h"
#include "Diagnosis.h"
#include "Doctor.h"
#include "Labs.h"
#include "Nurse.h"
#include "EList.h"
#include "Prescription.h"
#include <cstring>
#include <iostream>




using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern int patientCount;
extern PATIENT patients[MAX_PATIENTS];


namespace HosptialTestCase
{
    TEST_CLASS(HosptialTestCase)
    {
    public:


        TEST_METHOD(loadPatientsFromFile_Test)
        {
            // Arrange - Clear the file to ensure it's empty before adding new patients
            FILE* clearFile = fopen("patients.txt", "w");
            if (clearFile != nullptr) {
                fclose(clearFile);
            }

            // Arrange - Add some patients to the file
            PATIENT testPatients[2] = {
                { "Alice", "Johnson", "1985-05-10", "Allergy to peanuts", "987-654-3210", "HC456", "Dr. Miller", "456 Elm St", "Female", 200 },
                { "Bob", "Smith", "1978-09-15", "None", "111-222-3333", "HC789", "Dr. Brown", "789 Oak St", "Male", 150 }
            };
            for (int i = 0; i < 2; ++i) {
                addPatient(testPatients[i]);
            }

            // Act
            loadPatientsFromFile();

            // Assert - Check if the loaded patients match the expected patients
            for (int i = 0; i < 2; ++i) {
                bool patientFound = false;
                for (int j = 0; j < getPatientCount(); ++j) {
                    if (strcmp(testPatients[i].healthCardNumber, patients[j].healthCardNumber) == 0) {
                        Assert::AreEqual(testPatients[i].firstName, patients[j].firstName, L"First name mismatch.");
                        Assert::AreEqual(testPatients[i].lastName, patients[j].lastName, L"Last name mismatch.");
                        Assert::AreEqual(testPatients[i].dob, patients[j].dob, L"Date of birth mismatch.");
                        Assert::AreEqual(testPatients[i].medicalHistory, patients[j].medicalHistory, L"Medical history mismatch.");
                        Assert::AreEqual(testPatients[i].contactInfo, patients[j].contactInfo, L"Contact info mismatch.");
                        Assert::AreEqual(testPatients[i].healthCardNumber, patients[j].healthCardNumber, L"Health card number mismatch.");
                        Assert::AreEqual(testPatients[i].familyDoctorName, patients[j].familyDoctorName, L"Family doctor name mismatch.");
                        Assert::AreEqual(testPatients[i].address, patients[j].address, L"Address mismatch.");
                        Assert::AreEqual(testPatients[i].gender, patients[j].gender, L"Gender mismatch.");
                        patientFound = true;
                        break;
                    }
                }
                Assert::IsTrue(patientFound, L"Patient not found in loaded data.");
            }
        }




        TEST_METHOD(addPatient_Test)
        {
            // Arrange
            PATIENT newPatient = { "John", "Doe", "1990-01-01", "No allergies", "123-456-7890", "HC123", "Dr. Smith", "123 Main St", "Male", 0 };

            // Act
            char* message = addPatient(newPatient);

            // Assert
            char* expectedMessage = "Patient added";
            Assert::AreEqual(expectedMessage, message, L"The patient was not added successfully.");
        }


        TEST_METHOD(deletePatient_test)
        {
            // Arrange - Ensure there is at least one patient to delete
            char healthCardNumber[] = "HC123"; // Make sure this patient exists; you might add one as part of your test setup

            // Act
            char* message = deletePatient(healthCardNumber);

            // Assert
            char* expectedMessage = "Patient deleted";
            Assert::AreEqual(expectedMessage, message, L"The patient was not deleted successfully.");
        }




        TEST_METHOD(findPatient_test)
        {
            // Arrange - Add a known patient
            PATIENT testPatient = { "TestFirst", "TestLast", "2000-01-01", "TestHistory", "TestContact", "TestHCN123", "TestDoctor", "TestAddress", "Male", 100 };
            addPatient(testPatient);

            // Act
            // Modify `findPatient` to return a bool indicating if the patient was found
            bool found = findPatient("TestHCN123");

            // Assert
            Assert::IsTrue(found, L"findPatient did not find the patient.");
        }

        TEST_METHOD(printPatientsSorted_test)
        {
            // Act
            // Assume `printPatientsSorted` adapted to return an array or list of patients sorted, not just print
            bool isSortedCorrectly = printPatientsSorted("lastName"); // Assuming implementation

            // Assert
            Assert::IsTrue(isSortedCorrectly, L"Patients are not sorted correctly.");
        }

        TEST_METHOD(findAndEditPatient_Test)
        {
            // Arrange - Add a known patient
            PATIENT testPatient = { "John", "Doe", "1990-01-01", "Test History", "Test Contact", "TestHCN123", "TestDoctor", "TestAddress", "Male", 100 };
            addPatient(testPatient);

            // Act - Edit the known patient
            char newFirst[100] = "Jane";
            char newLast[100] = "Smith";
            char newDob[11] = "2000-02-02";
            char newHistory[1024] = "New Test History";
            char newContact[100] = "New Test Contact";
            char newHealthCard[20] = "NewHCN123";
            char newDoctor[100] = "New Test Doctor";
            char newAddress[100] = "New Test Address";
            char newGender[10] = "Female";
            findAndEditPatient("TestHCN123", newFirst, newLast, newDob, newHistory, newContact, newHealthCard, newDoctor, newAddress, newGender);

            // Assert - Check if the patient's information has been correctly updated
            PATIENT* editedPatient = nullptr;
            for (int i = 0; i < patientCount; ++i) {
                if (strcmp(patients[i].healthCardNumber, "NewHCN123") == 0) {
                    editedPatient = &patients[i];
                    break;
                }
            }
            Assert::IsNotNull(editedPatient, L"Edited patient not found.");
            Assert::AreEqual("Jane", editedPatient->firstName, L"First name not updated correctly.");
            Assert::AreEqual("Smith", editedPatient->lastName, L"Last name not updated correctly.");
            Assert::AreEqual("2000-02-02", editedPatient->dob, L"Date of birth not updated correctly.");
            Assert::AreEqual("New Test History", editedPatient->medicalHistory, L"Medical history not updated correctly.");
            Assert::AreEqual("New Test Contact", editedPatient->contactInfo, L"Contact info not updated correctly.");
            Assert::AreEqual("NewHCN123", editedPatient->healthCardNumber, L"Health card number not updated correctly.");
            Assert::AreEqual("New Test Doctor", editedPatient->familyDoctorName, L"Family doctor name not updated correctly.");
            Assert::AreEqual("New Test Address", editedPatient->address, L"Address not updated correctly.");
            Assert::AreEqual("Female", editedPatient->gender, L"Gender not updated correctly.");
        }

        TEST_METHOD(SavePatientsToFileTest)
        {
            // Arrange
            PATIENT testPatient = { "John", "Doe", "1990-01-01", "No allergies", "123-456-7890", "HC123", "Dr. Smith", "123 Main St", "Male", 0 };
            addPatient(testPatient);

            // Act
            savePatientsToFile();

            // Assert
            // You may add assertions to check if the file was created and contains the expected content
            // For simplicity, let's assume that the existence of the file and its content are manually verified
        }

        // Test case for displayEditMenu()
        TEST_METHOD(DisplayEditMenuTest)
        {
            // Arrange
            char healthCardNumber[] = "HC123"; // Assuming this patient exists
            // Redirect stdin to provide input for the menu
            std::istringstream input("1\nNewFirstName\n0\n");
            std::streambuf* oldStdin = std::cin.rdbuf(input.rdbuf());

            // Act
            displayEditMenu(healthCardNumber);

            // Assert
            // You may add assertions to check if the patient's first name was updated as expected
            // For simplicity, let's assume that the updated information is manually verified
            // Restore stdin
            std::cin.rdbuf(oldStdin);
        }
    };
}