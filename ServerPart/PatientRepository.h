#pragma once
#include "Queue.h"
#include "Patient.h"
#include <iostream>
#include <typeinfo>

class PatientRepository
{
private:
	Queue<Patient> _regularPatients;
	Queue<VIP_Patient> _vipPatients;
	//Queue<Patient> _patients;
public:
	PatientRepository();
	Patient GetPatient();
	void AddPatient(Patient& patient);
};

