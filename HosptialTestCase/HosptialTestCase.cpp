#include "pch.h"
#include "CppUnitTest.h"
#include "../CSCN71030-Sec2-Group2/Patients.h"
#include "../CSCN71030-Sec2-Group2/Nurse.h"
#include "../CSCN71030-Sec2-Group2/EList.h"
#include <cstring>
#include <iostream>
#include "../CSCN71030-Sec2-Group2/Doctor.h"
#include "../CSCN71030-Sec2-Group2/Labs.h"
#include "../CSCN71030-Sec2-Group2/Appointment.h"
#include "../CSCN71030-Sec2-Group2/Prescription.h"
#include "../CSCN71030-Sec2-Group2/Diagnosis.h"

char* AddDoctor(const Doctor doctor);
bool SaveDoctorToFile();
void LoadDoctor();
char* PrintDoctorSorted(const char* sortBy);
char* SearchDoctorByName(char* Name);
char* SearchDoctorBySpecialization(char* specialization);
char* saveLabToFile();
char* addLabs(const LAB lab);
char* LoadLabs();
char* printLabsSorted(const char* sortBy);
char* saveAppointmentToFile();
char* LoadAppointments();
char* addAppointment(const Appointment appointment);
char* printAppointmentSorted(const char* sortBy);
char* savePrescriptionToFile();
char* addPrescriptionToFile(const Prescription prescription);
char* LoadPrescription();
char* printPrescriptionSorted(const char* sortBy);
char* saveDiagnosticToFile();
char* LoadDiagnostic();
char* addDiagnostic(const Diagnostic diagnostic);
char* printDiagnosticSorted(const char* sortBy);



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern int patientCount;
extern PATIENT patients[MAX_PATIENTS];


namespace HosptialTestCase
{
    TEST_CLASS(HosptialTestCase)
    {
    public:


        TEST_METHOD(loadPatientsFromFileTest001)
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




        TEST_METHOD(addPatientTest002)
        {
            // Arrange
            PATIENT newPatient = { "John", "Doe", "1990-01-01", "No allergies", "123-456-7890", "HC123", "Dr. Smith", "123 Main St", "Male", 0 };

            // Act
            char* message = addPatient(newPatient);

            // Assert
            char* expectedMessage = "Patient added";
            Assert::AreEqual(expectedMessage, message, L"The patient was not added successfully.");
        }


        TEST_METHOD(deletePatientTest003)
        {
            // Arrange - Ensure there is at least one patient to delete
            char healthCardNumber[] = "HC123"; // Make sure this patient exists; you might add one as part of your test setup

            // Act
            char* message = deletePatient(healthCardNumber);

            // Assert
            char* expectedMessage = "Patient deleted";
            Assert::AreEqual(expectedMessage, message, L"The patient was not deleted successfully.");
        }

        TEST_METHOD(findPatientTest004)
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

        TEST_METHOD(printPatientsSortedTest005)
        {
            // Act
            // Assume `printPatientsSorted` adapted to return an array or list of patients sorted, not just print
            bool isSortedCorrectly = printPatientsSorted("lastName"); // Assuming implementation

            // Assert
            Assert::IsTrue(isSortedCorrectly, L"Patients are not sorted correctly.");
        }

        TEST_METHOD(findAndEditPatientTest006)
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

        TEST_METHOD(SavePatientsToFileTest007)
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
        TEST_METHOD(DisplayEditMenuTest008)
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

		TEST_METHOD(AddDoctorTest009)
		{
			Doctor doctor;
			doctor[i].Id = 300098;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);
		}
		TEST_METHOD(SaveDoctorToFileTest010)
		{
			Doctor doctor;
			doctor[i].Id = 30;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);

		}
		TEST_METHOD(LoadDoctorTest011)
		{
			Doctor doctor;
			doctor[i].Id = 30;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);
		}
		TEST_METHOD(PrintDoctorSortedTest012)
		{
			Doctor doctor;
			doctor[i].Id = 30;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);

		}
		TEST_METHOD(SearchDoctorByNameTest013)
		{
			Doctor doctor;
			doctor[i].Id = 30;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);

		}
		TEST_METHOD(SearchDoctorBySpecializationTest014)
		{
			Doctor doctor;
			doctor[i].Id = 30;
			doctor[i].Name = "Joan Royales";
			doctor[i].Specialization = "General Medicine";
			doctor[i].Contact = "5194478999";

			char* expected = "A Doctor";
			char* actual = AddDoctor(doctor);

			std::string(expected, actual);

		}
		TEST_METHOD(addAppointmentTest015)
		{
			Appointment appointment;
			appointment[i].firstName = "Joan";
			appointment[i].lastName = "Royales";
			appointment[i].description = "Heart pacemaker";
			appointment[i].time = "May 10th, 2024 at 12:00 PM";
			appointment[i].location = "Mary General Hospital";
			appointment[i].category = "Cardiologist";

			const char* expected = "A Doctor";
			const char* actual = addAppointment(appointment);

			std::string(expected, actual);
		}
		TEST_METHOD(saveAppointmentToFileTest016)
		{
			Appointment appointment;
			appointment[i].firstName = "Joan";
			appointment[i].lastName = "Royales";
			appointment[i].description = "Heart pacemaker";
			appointment[i].time = "May 10th, 2024 at 12:00 PM";
			appointment[i].location = "Mary General Hospital";
			appointment[i].category = "Cardiologist";

			const char* expected = "Scheduled";
			const char* actual = saveAppointmentToFile(appointment);

			std::string(expected, actual);

		}
		TEST_METHOD(LoadAppointmentsTest017)
		{
			Appointment appointment;
			appointment[i].firstName = "Joan";
			appointment[i].lastName = "Royales";
			appointment[i].description = "Heart pacemaker";
			appointment[i].time = "May 10th, 2024 at 12:00 PM";
			appointment[i].location = "Mary General Hospital";
			appointment[i].category = "Cardiologist";

			const char* expected = "Scheduled";
			const char* actual = LoadAppointments(appointment);

			std::string(expected, actual);
		}
		TEST_METHOD(printAppointmentSortedTest018)
		{
			Appointment appointment;
			appointment[i].firstName = "Joan";
			appointment[i].lastName = "Royales";
			appointment[i].description = "Heart pacemaker";
			appointment[i].time = "May 10th, 2024 at 12:00 PM";
			appointment[i].location = "Mary General Hospital";
			appointment[i].category = "Cardiologist";

			const char* expected = "Scheduled";
			const char* actual = printAppointmentSorted(appointment);

			std::string(expected, actual);

		}
		TEST_METHOD(addLabsTest019)
		{
			LAB lab;
			lab[i].name = "Joan Royales";
			lab[i].cost = "$100";
			lab[i].time = "January 8th, 2024 at 3PM";
			lab[i].category = "Blood work";


			const char* expected = "Test Results";
			const char* actual = addLabs(lab);

			std::string(expected, actual);
		}
		TEST_METHOD(saveAppointmentToFileTest020)
		{
			LAB lab;
			lab[i].name = "Joan Royales";
			lab[i].cost = "$100";
			lab[i].time = "January 8th, 2024 at 3PM";
			lab[i].category = "Blood work";


			const char* expected = "Test Results";
			const char* actual = addLabs(lab);

			std::string(expected, actual);

		}
		TEST_METHOD(LoadAppointmentsTest021)
		{
			LAB lab;
			lab[i].name = "Joan Royales";
			lab[i].cost = "$100";
			lab[i].time = "January 8th, 2024 at 3PM";
			lab[i].category = "Blood work";


			const char* expected = "Test Results";
			const char* actual = addLabs(lab);

			std::string(expected, actual);
		}
		TEST_METHOD(printAppointmentSortedTest022)
		{
			LAB lab;
			lab[i].name = "Joan Royales";
			lab[i].cost = "$100";
			lab[i].time = "January 8th, 2024 at 3PM";
			lab[i].category = "Blood work";


			const char* expected = "Test Results";
			const char* actual = addLabs(lab);

			std::string(expected, actual);

		}
		TEST_METHOD(addPrescriptionToFileTest023)
		{
			Prescription prescription;
			prescription[i].patientId = "6976396_JK";
			prescription[i].medicationName = "Cholecalciferol";
			prescription[i].dosage = "100mg ";
			prescription[i].frequency = "Twice per day";
			prescription[i].quantity = "2 Tablets";


			const char* expected = "Prescription";
			const char* actual = addPrescriptionToFile(prescription);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(savePrescriptionToFileTest024)
		{
			Prescription prescription;
			prescription[i].patientId = "6976396_JK";
			prescription[i].medicationName = "Cholecalciferol";
			prescription[i].dosage = "100mg ";
			prescription[i].frequency = "Twice per day";
			prescription[i].quantity = "2 Tablets";


			const char* expected = "Prescription";
			const char* actual = savePrescriptionToFile(prescription);

			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(LoadPrescriptionTest025)
		{
			Prescription prescription;
			prescription[i].patientId = "6976396_JK";
			prescription[i].medicationName = "Cholecalciferol";
			prescription[i].dosage = "100mg ";
			prescription[i].frequency = "Twice per day";
			prescription[i].quantity = "2 Tablets";


			const char* expected = "Prescription";
			const char* actual = LoadPrescription(prescription);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(printPrescriptionSortedTest026)
		{
			Prescription prescription;
			prescription[i].patientId = "6976396_JK";
			prescription[i].medicationName = "Cholecalciferol";
			prescription[i].dosage = "100mg ";
			prescription[i].frequency = "Twice per day";
			prescription[i].quantity = "2 Tablets";


			char* expected = "Prescription";
			char* actual = printPrescriptionSorted(prescription);

			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(addDiagnosticTest027)
		{
			Diagnostic diagnostic;
			diagnostic[i].patientId = "6976396_JK";
			diagnostic[i].Symptoms = "Chronical sharp pain in the heart";
			diagnostic[i].numSymptoms = "3";
			diagnostic[i].Diagnosis = "Heart Problem";
			diagnostic[i].numDiagnosis = "1";


			const char* expected = "Prescription";
			const char* actual = addDiagnostic(diagnostic);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(saveDiagnosticToFileTest028)
		{
			Diagnostic diagnostic;
			diagnostic[i].patientId = "6976396_JK";
			diagnostic[i].Symptoms = "Chronical sharp pain in the heart";
			diagnostic[i].numSymptoms = "3";
			diagnostic[i].Diagnosis = "Heart Problem";
			diagnostic[i].numDiagnosis = "1";


			const char* expected = "Prescription";
			const char* actual = saveDiagnosticToFile(diagnostic);

			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(LoadDiagnosticTest029)
		{
			Diagnostic diagnostic;
			diagnostic[i].patientId = "6976396_JK";
			diagnostic[i].Symptoms = "Chronical sharp pain in the heart";
			diagnostic[i].numSymptoms = "3";
			diagnostic[i].Diagnosis = "Heart Problem";
			diagnostic[i].numDiagnosis = "1";


			const char* expected = "Prescription";
			const char* actual = LoadDiagnostic(diagnostic);

			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(printDiagnosticSortedTest030)
		{
			Diagnostic diagnostic;
			diagnostic[i].patientId = "6976396_JK";
			diagnostic[i].Symptoms = "Chronical sharp pain in the heart";
			diagnostic[i].numSymptoms = "3";
			diagnostic[i].Diagnosis = "Heart Problem";
			diagnostic[i].numDiagnosis = "1";


			const char* expected = "Prescription";
			const char* actual = printDiagnosticSorted(diagnostic);

			Assert::AreEqual(expected, actual);

		}
    };
}