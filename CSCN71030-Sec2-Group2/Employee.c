#include "Employee.h"

EMPLOYEE createNurseEmployee(NURSE n, char* username, char* password) {
	EMPLOYEE e;
	e.role = NURSE_ROLE;
	e.data.n = n;
	e.username = username;
	e.password = password;
	e.Patients = NULL;
	return e;
}
EMPLOYEE createDoctorEmployee(Doctor d, char* username, char* password) {
	EMPLOYEE e;
	e.data.d = d;
	e.role = DOCTOR_ROLE;
	e.username = username;
	e.password = password;
	e.Patients = NULL;
	return e;
}
void printEmployee(EMPLOYEE e) {
	if(e.role == NURSE_ROLE)

}