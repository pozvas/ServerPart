#pragma once
#include "Queue.h"
#include "Patient.h"
#include <iostream>
#include <typeinfo>

class PatientRepository
{
private:
	Queue<Patient> _patients;
public:
	Patient GetPatient() {
		if (!_patients.IsEmpty())
			return _patients.Pop();
		else
			throw std::out_of_range("Queue is empty");
	}
	void AddPatient(Patient& patient) {
		if(dynamic_cast<VIP_Patient*>(&patient) == nullptr)
		
		_patients.Push(patient);
	}
};

