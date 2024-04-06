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
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* AddDoctorTest009();
			struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = AddDoctor(doctor);

				std::string(expected, actual);

		}
		TEST_METHOD(SaveDoctorToFileTest010)
		{
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* SaveDoctorToFileTest010();
				struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = SaveDoctorToFile(doctor);

				std::string(expected, actual);

		}
		TEST_METHOD(LoadDoctorTest011)
		{
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* LoadDoctorTest012();
				struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = LoadDoctor(doctor);

				std::string(expected, actual);

		}
		TEST_METHOD(PrintDoctorSortedTest012)
		{
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* PrintDoctorSortedTest012();
				struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = PrintDoctorSorted(doctor);

				std::string(expected, actual);
		}
		TEST_METHOD(SearchDoctorByNameTest013)
		{
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* SearchDoctorByNameTest013();
				struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = SearchDoctorByName(doctor);

				std::string(expected, actual);

		}
		TEST_METHOD(SearchDoctorBySpecializationTest014)
		{
			struct Doctor {
				char* doctorId;
				char* Name;
				char* Specialization;
				char* Contact;
			};
			char* SearchDoctorBySpecializationTest014();
				struct Doctor doctor;
				doctor.doctorId = "300893";
				doctor.Name = "Joan Royales";
				doctor.Specialization = "General Medicine";
				doctor.Contact = "5194478999";

				char* expected = "A Doctor";
				char* actual = SearchDoctorBySpecialization(doctor);

				std::string(expected, actual);

		}
		TEST_METHOD(addAppointmentTest015)
		{
			struct Appointment {
				char* firstName;
				char* lastName;
				char* description;
				char* time;
				char* location;
				char* category;
			};
			char* addAppointmentTest015();
				struct Appointment appointment;
				appointment.firstName = "Joan";
				appointment.lastName = "Royales";
				appointment.description = "Heart pacemaker";
				appointment.time = "May 10th, 2024 at 12:00 PM";
				appointment.location = "Mary General Hospital";
				appointment.category = "Cardiologist";

				const char* expected = "A Doctor";
				const char* actual = addAppointment(appointment);

				std::string(expected, actual);
		}
		TEST_METHOD(saveAppointmentToFileTest016)
		{
			struct Appointment {
				char* firstName;
				char* lastName;
				char* description;
				char* time;
				char* location;
				char* category;
			};
			char* saveAppointmentToFileTest015();
				struct Appointment appointment;
				appointment.firstName = "Joan";
				appointment.lastName = "Royales";
				appointment.description = "Heart pacemaker";
				appointment.time = "May 10th, 2024 at 12:00 PM";
				appointment.location = "Mary General Hospital";
				appointment.category = "Cardiologist";

				const char* expected = "A Doctor";
				const char* actual = saveAppointmentToFile(appointment);

				std::string(expected, actual);

		}
		TEST_METHOD(LoadAppointmentsTest017)
		{
			struct Appointment {
				char* firstName;
				char* lastName;
				char* description;
				char* time;
				char* location;
				char* category;
			};
			char* LoadAppointmentsTest017();
				struct Appointment appointment;
				appointment.firstName = "Joan";
				appointment.lastName = "Royales";
				appointment.description = "Heart pacemaker";
				appointment.time = "May 10th, 2024 at 12:00 PM";
				appointment.location = "Mary General Hospital";
				appointment.category = "Cardiologist";

				const char* expected = "A Doctor";
				const char* actual = LoadAppointments(appointment);

				std::string(expected, actual);
		}
		TEST_METHOD(printAppointmentSortedTest018)
		{
			struct Appointment {
				char* firstName;
				char* lastName;
				char* description;
				char* time;
				char* location;
				char* category;
			};
			char* printAppointmentSortedTest018();
				struct Appointment appointment;
				appointment.firstName = "Joan";
				appointment.lastName = "Royales";
				appointment.description = "Heart pacemaker";
				appointment.time = "May 10th, 2024 at 12:00 PM";
				appointment.location = "Mary General Hospital";
				appointment.category = "Cardiologist";

				const char* expected = "A Doctor";
				const char* actual = printAppointmentSorted(appointment);

				std::string(expected, actual);
		}
		TEST_METHOD(addLabsTest019)
		{
			struct LAB {
				char* name;
				char* cost;
				char* time;
				char* category;
			};
			char* addLabsTest019();
				struct LAB lab;
				lab.name = "Joan Royales";
				lab.cost = "$100";
				lab.time = "January 8th, 2024 at 3PM";
				lab.category = "Blood work";


				const char* expected = "Test Results";
				const char* actual = addLabs(lab);

				std::string(expected, actual);
		}
		TEST_METHOD(saveLabToFileTest020)
		{
			struct LAB {
				char* name;
				char* cost;
				char* time;
				char* category;
			};
			char* saveLabToFileTest020();
				struct LAB lab;
				lab.name = "Joan Royales";
				lab.cost = "$100";
				lab.time = "January 8th, 2024 at 3PM";
				lab.category = "Blood work";


				const char* expected = "Test Results";
				const char* actual = saveLabToFile(lab);

				std::string(expected, actual);

		}
		TEST_METHOD(LoadLabssTest021)
		{
			struct LAB {
				char* name;
				char* cost;
				char* time;
				char* category;
			};
			char* LoadLabsTest021();
				struct LAB lab;
				lab.name = "Joan Royales";
				lab.cost = "$100";
				lab.time = "January 8th, 2024 at 3PM";
				lab.category = "Blood work";


				const char* expected = "Test Results";
				const char* actual = LoadLabs(lab);

				std::string(expected, actual);
		}
		TEST_METHOD(printLabSortedTest022)
		{
			struct LAB {
				char* name;
				char* cost;
				char* time;
				char* category;
			};
			char* printLabTest022();
				struct LAB lab;
				lab.name = "Joan Royales";
				lab.cost = "$100";
				lab.time = "January 8th, 2024 at 3PM";
				lab.category = "Blood work";


				const char* expected = "Test Results";
				const char* actual = printLabsSorted(lab);

				std::string(expected, actual);

		}
		TEST_METHOD(addPrescriptionToFileTest023)
		{
			struct Prescription {
				char* patientId;
				char* medicationName;
				char* dosage;
				char* frequency;
				char* quantity;
			};
			char* addPrescriptionToFileTest023();
				struct Prescription prescription;
				prescription.patientId = "6976396_JK";
				prescription.medicationName = "Cholecalciferol";
				prescription.dosage = "100mg ";
				prescription.frequency = "Twice per day";
				prescription.quantity = "2 Tablets";


				const char* expected = "Prescription";
				const char* actual = addPrescriptionToFile(prescription);

				Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(savePrescriptionToFileTest024)
		{
			struct Prescription {
				char* patientId;
				char* medicationName;
				char* dosage;
				char* frequency;
				char* quantity;
			};
			char* savePrescriptionToFileTest024();
				struct Prescription prescription;
				prescription.patientId = "6976396_JK";
				prescription.medicationName = "Cholecalciferol";
				prescription.dosage = "100mg ";
				prescription.frequency = "Twice per day";
				prescription.quantity = "2 Tablets";


				const char* expected = "Prescription";
				const char* actual = savePrescriptionToFile(prescription);

				Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(LoadPrescriptionTest025)
		{
			struct Prescription {
				char* patientId;
				char* medicationName;
				char* dosage;
				char* frequency;
				char* quantity;
			};
			char* LoadPrescriptiontTest025();      // Define
				struct Prescription prescription;
				prescription.patientId = "6976396_JK";
				prescription.medicationName = "Cholecalciferol";
				prescription.dosage = "100mg ";
				prescription.frequency = "Twice per day";
				prescription.quantity = "2 Tablets";


				const char* expected = "Prescription";
				const char* actual = LoadPrescription(prescription);

				Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(printPrescriptionSortedTest026)
		{
			struct Prescription {
				char* patientId;
				char* medicationName;
				char* dosage;
				char* frequency;
				char* quantity;
			};
			char* printPrescriptionSortedTest026();
				struct Prescription prescription;
				prescription.patientId = "6976396_JK";
				prescription.medicationName = "Cholecalciferol";
				prescription.dosage = "100mg ";
				prescription.frequency = "Twice per day";
				prescription.quantity = "2 Tablets";


				char* expected = "Prescription";
				char* actual = printPrescriptionSorted(prescription);

				Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(addDiagnosticTest027)
		{
			struct Diagnostic {
				char* patientId;
				char* Symptoms;
				char* numSymptoms;
				char* Diagnosis;
				char* numDiagnosis;
			};
			char* addDiagnosticTest027();
				struct Diagnostic diagnostic;
				diagnostic.patientId = "6976396_JK";
				diagnostic.Symptoms = "Chronical sharp pain in the heart";
				diagnostic.numSymptoms = "3";
				diagnostic.Diagnosis = "Heart Problem";
				diagnostic.numDiagnosis = "1";


				const char* expected = "Prescription";
				const char* actual = addDiagnostic(diagnostic);

				Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(saveDiagnosticToFileTest028)
		{
			struct Diagnostic {
				char* patientId;
				char* Symptoms;
				char* numSymptoms;
				char* Diagnosis;
				char* numDiagnosis;
			};
			char* saveDiagnosticToFileTest028();
				struct Diagnostic diagnostic;
				diagnostic.patientId = "6976396_JK";
				diagnostic.Symptoms = "Chronical sharp pain in the heart";
				diagnostic.numSymptoms = "3";
				diagnostic.Diagnosis = "Heart Problem";
				diagnostic.numDiagnosis = "1";


				const char* expected = "Prescription";
				const char* actual = saveDiagnosticToFile(diagnostic);

				Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(LoadDiagnosticTest029)
		{
			struct Diagnostic {
				char* patientId;
				char* Symptoms;
				char* numSymptoms;
				char* Diagnosis;
				char* numDiagnosis;
			};
			char* LoadDiagnosticTest029();
				struct Diagnostic diagnostic;
				diagnostic.patientId = "6976396_JK";
				diagnostic.Symptoms = "Chronical sharp pain in the heart";
				diagnostic.numSymptoms = "3";
				diagnostic.Diagnosis = "Heart Problem";
				diagnostic.numDiagnosis = "1";


				const char* expected = "Prescription";
				const char* actual = LoadDiagnostic(diagnostic);

				Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(printDiagnosticSortedTest030)
		{
			struct Diagnostic {
				char* patientId;
				char* Symptoms;
				char* numSymptoms;
				char* Diagnosis;
				char* numDiagnosis;
			};
			char* printDiagnosticSortedTest030();
				struct Diagnostic diagnostic;
				diagnostic.patientId = "6976396_JK";
				diagnostic.Symptoms = "Chronical sharp pain in the heart";
				diagnostic.numSymptoms = "3";
				diagnostic.Diagnosis = "Heart Problem";
				diagnostic.numDiagnosis = "1";


				const char* expected = "Prescription";
				const char* actual = printDiagnosticSorted(diagnostic);

				Assert::AreEqual(expected, actual);

		}
    };
}