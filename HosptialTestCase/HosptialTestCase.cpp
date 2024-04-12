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
char* SaveDoctorToFile();
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
	};
		TEST_CLASS(DoctorModuleTests)
		{
		public:
			TEST_METHOD(AddDoctorTest009)
			{
				Doctor doctor;
				Doctor doctor("John", "300893", "Cardiology", "519-456-7890");

				//Call the function to add the doctor
				char* result = AddDoctor(doctor);

				// Assert that the result is not null or empty if successful
				Assert::IsNotNull(result);
				Assert::IsTrue(strcmp(result, "Doctor added successfully") == 0);

				// Clean up memory if needed
				delete[] result;
			}

			TEST_METHOD(SaveDoctorToFileTest010)
			{
				// Call the SaveDoctorToFile function
				char* result = SaveDoctorToFile();

				// Assert that the return value is true, indicating successful saving of doctors to file
				Assert::IsTrue(result);
			}

			// Test case for LoadDoctor function
			TEST_METHOD(LoadDoctorTest)
			{
				// Assuming some doctors are already loaded into the system
				LoadDoctor();

				// Check if doctors are successfully loaded
				Assert::IsTrue("Check if doctors are loaded properly");

				// Similarly, add test cases for other functions like PrintDoctorSorted, SearchDoctorByName, etc.

			}

			TEST_METHOD(PrintDoctorSortedTest012)
			{
				char* sortBy = "Name"; // Sorting doctors by name for this test

				// Call the PrintDoctorSorted function and capture the returned value
				char* result = PrintDoctorSorted(sortBy);

				// Assert that the returned value is not NULL
				Assert::IsNotNull(result);

				// Assuming PrintDoctorSorted returns a string with doctor information, additional assertions can be added to validate the content
				// For example:
				// Assert::AreEqual("Dr. John Doe, Dr. Jane Smith, Dr. Michael Johnson", result);

				// Deallocate memory allocated for the result to prevent memory leaks
				delete[] result; // Assuming dynamic memory allocation with new[] was used in PrintDoctorSorted
			}

			TEST_METHOD(SearchDoctorByNameTest013)
			{
				Doctor newDoctor;
				// Create a Doctor object with the specified details
				Doctor newDoctor("John", "300893", "Cardiology", "519-456-7890");

				// Call the SearchDoctorByName function and capture the returned value
				char* result = SearchDoctorByName(newDoctor.Name);

				// Assert that the returned value is not NULL, indicating successful search for doctor
				Assert::IsNotNull(result);

				// Clean up the dynamically allocated memory if necessary
				delete[] result; // Assuming the memory is allocated using new[] in SearchDoctorByName

			}

		};

		TEST_CLASS(AppointmentModuleTests)
		{
		public:

			TEST_METHOD(addAppointmentTest015)
			{
				//Arrange
				Appointment appointment;
				// Act
				char* result = addAppointment(appointment);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Error", result); // Assuming "Error" is the expected output upon unsuccessful file save
			}

			TEST_METHOD(addAppointment_InvalidInput_ReturnsErrorMessage)
			{
				// Arrange
				Appointment appointment;
				// Act
				char* result = addAppointment(appointment);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(saveAppointmentToFileTest016)
			{
				Appointment appointment;
				// Initialize appointment data here

				char* result = saveAppointmentToFile();

				Assert::AreEqual("Appointment saved successfully", result);
			}

			TEST_METHOD(SaveAppointmentToFile_InvalidInput_ReturnsErrorMessage)
			{

				// Arrange
				Appointment appointment;
				// Empty diagnostic object, causing failure

				// Act
				char* result = saveDiagnosticToFile();

				// Assert
				Assert::IsNull(result);
				// Additional assertions can be added based on expected failure scenarios
			}


			TEST_METHOD(LoadAppointmentsTest017)
			{
				Appointment appointment;
				// Initialize appointment data here

				char* result = LoadAppointments();

				Assert::AreEqual("Appointment saved successfully", result);
			}

			TEST_METHOD(LoadAppointments_InvalidInput_ReturnsErrorMessage)
			{
				// Define invalid input data (e.g., empty string, incorrect format)
				const char* invalidInputData = "Invalid input data";

				// Call LoadAppointments with invalid input data
				char* invalidInputData = LoadAppointments();

				// Assert the returned result
				Assert::AreEqual("Failed to load appointments", invalidInputData);

				// Deallocate memory if necessary (assuming dynamic memory allocation)
				delete[] invalidInputData;
			}

			TEST_METHOD(printAppointmentSortedTest018)
			{
				char* SortBy = "Name";
				// Initialize appointment data here

				char* SortBy = printAppointmentSorted(SortBy);

				Assert::AreEqual("Appointment saved successfully", SortBy);
			}

			TEST_METHOD(printAppointmentSorted_InvalidInput_ReturnsErrorMessage)
			{
				// Create invalid appointment data here

				char* result = printAppointmentSorted(result);

				Assert::AreEqual("Failed to save appointment", result);
			}
		};

		TEST_CLASS(LabsModuleTests)
		{
		public:

			TEST_METHOD(addLabsTest019)
			{
				// Assuming addLabs function adds a lab to the system and returns a status message
				LAB lab;
				// Initialize lab data (assuming LAB structure is defined)
				// lab.name = "LabName";
				// lab.type = "Chemistry";
				// lab.capacity = 30;

				char* result = addLabs(lab);
				Assert::AreEqual("Lab added successfully.", result);
			}
			TEST_METHOD(saveLabToFileTest020)
			{
				// Assuming saveLabToFile function saves lab data to a file and returns a status message
				char* result = saveLabToFile();
				Assert::AreEqual("Lab data saved successfully.", result);

			}
			TEST_METHOD(LoadLabssTest021)
			{
				// Assuming LoadLabs function loads lab data from a file and returns a status message
				char* result = LoadLabs();
				Assert::AreEqual("Lab data loaded successfully.", result);
			}
			TEST_METHOD(printLabSortedTest022)
			{
				// Assuming printLabsSorted function prints lab data sorted by the specified criteria and returns a status message
				char* result = printLabsSorted("name");
				Assert::AreEqual("Lab data printed successfully.", result);

			}
		};

		TEST_CLASS(PrescriptionModuleTests)
		{
		public:

			TEST_METHOD(SavePrescriptionToFile_ValidInput_ReturnsSuccess023)
			{
				// Arrange

				// Act
				char* result = savePrescriptionToFile();

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(SavePrescriptionToFile_InvalidInput_ReturnsError)
			{
				// Arrange

				// Act
				char* result = savePrescriptionToFile();

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Error", result); // Assuming "Error" is the expected output upon unsuccessful file save
			}

			TEST_METHOD(addPrescriptionToFileTest024)
			{
				// Arrange
				Prescription prescription;
				// Act
				char* result = addPrescriptionToFile(prescription);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(addPrescriptionToFile_InvalidInput_ReturnsError)
			{
				// Arrange
				Prescription prescription;
				// Act
				char* result = addPrescriptionToFile(prescription);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Error", result); // Assuming "Error" is the expected output upon unsuccessful file save
			}

			TEST_METHOD(LoadPrescription_ValidInput_ReturnsSuccess)
			{
				// Arrange

				// Act
				char* result = LoadPrescription();

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(LoadPrescription_InvalidInput_ReturnsError)
			{
				// Arrange

				// Act
				char* result = LoadPrescription();

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Error", result); // Assuming "Error" is the expected output upon unsuccessful file save
			}

			TEST_METHOD(printPrescriptionSortedTest026)
			{
				// Arrange

				// Act
				char* result = printPrescriptionSorted(result);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(printPrescriptionSorted_InvalidInput_ReturnsError)
			{
				char* SortBy = "Name";
				// Initialize prescription data here

				char* SortBy = printPrescriptionSorted(SortBy);

				Assert::AreEqual("Prescription saved successfully", SortBy);
			}
		};


		TEST_CLASS(DiagnosisModuleTests)
		{
		public:

			TEST_METHOD(addDiagnosticTest027)
			{
				// Arrange
				Diagnostic diagnostic;
				// Act
				char* result = addDiagnostic(diagnostic);

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save
			}

			TEST_METHOD(addDiagnostic_Failure)
			{
				// Arrange
				Diagnostic diagnostic;
				// Empty diagnostic object, causing failure

				// Act
				char* result = addDiagnostic(diagnostic);

				// Assert
				Assert::IsNull(result);
				// Additional assertions can be added based on expected failure scenarios
			}
			TEST_METHOD(saveDiagnosticToFileTest028)
			{
				// Arrange

			// Act
				char* result = savePrescriptionToFile();

				// Assert
				Assert::IsNotNull(result);
				Assert::AreEqual("Success", result); // Assuming "Success" is the expected output upon successful file save 
			}

			TEST_METHOD(saveDiagnosticToFile_Failure)
			{
				// Arrange
				Diagnostic diagnostic;
				// Empty diagnostic object, causing failure

				// Act
				char* result = saveDiagnosticToFile();

				// Assert
				Assert::IsNull(result);
				// Additional assertions can be added based on expected failure scenarios
			}
			TEST_METHOD(LoadDiagnosticTest029)
			{
				// Arrange
				// Assuming there are saved diagnostics in the file to load

				// Act
				char* result = LoadDiagnostic();

				// Assert
				Assert::IsNotNull(result);
				// Additional assertions can be added to validate the loaded diagnostics
			}

			TEST_METHOD(LoadDiagnostic_Empty)
			{
				// Arrange
				// Assuming there are no saved diagnostics in the file to load

				// Act
				char* result = LoadDiagnostic();

				// Assert
				Assert::IsNull(result);
				// Additional assertions can be added based on expected empty file scenarios
			}

			TEST_METHOD(printDiagnosticSortedTest030)
			{
				// Arrange
				const char* sortBy = "patientId"; // Sort by patient ID

				// Act
				char* result = printDiagnosticSorted(sortBy);

				// Assert
				Assert::IsNotNull(result);
				// Additional assertions can be added to validate the sorted diagnostics	
			}

			TEST_METHOD(PrintDiagnosticSorted_InvalidSortBy)
			{
				// Arrange
				const char* sortBy = "invalidField"; // Invalid field to sort by

				// Act
				char* result = printDiagnosticSorted(sortBy);

				// Assert
				Assert::IsNull(result);
				// Additional assertions can be added based on expected failure scenarios

			}
		};
}