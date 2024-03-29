//#include "Employee.h"
//
//EMPLOYEE createNurseEmployee(NURSE n, char* username, char* password) {
//	EMPLOYEE e;
//	e.role = NURSE_ROLE;
//	e.data.n = n;
//	e.username = username;
//	e.password = password;
//	return e;
//}
//EMPLOYEE createDoctorEmployee(Doctor d, char* username, char* password) {
//	EMPLOYEE e;
//	e.data.d = d;
//	e.role = DOCTOR_ROLE;
//	e.username = username;
//	e.password = password;
//	return e;
//}
//void printEmployee(EMPLOYEE e) {
//	if (e.role == NURSE_ROLE) {
//		printf("Nurse %s\n Username: %s\n", e.data.n.name, e.username);
//	}
//	if (e.role == DOCTOR_ROLE)
//		printf("Doctor %s\n Username: %s\n", e.data.d.Name, e.username);
//}