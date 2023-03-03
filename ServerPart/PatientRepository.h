#pragma once
#include "Queue.h"
#include "Patient.h"
#include <iostream>
#include <typeinfo>

class PatientRepository
{
private:
	/*Queue<Patient> _regularPatients;
	Queue<VIP_Patient> _vipPatients;*/
	Queue<Patient> _patients;
public:
	PatientRepository() {
		VIP_Patient p1 = VIP_Patient("name1", "surname1", "patromymic1", State::REGULAR, 10000);
		Patient p2 = Patient("name2", "surname2", "patromymic2", State::REGULAR);
		Patient p3 = Patient("name3", "surname3", "patromymic3", State::CRITICAL);
		VIP_Patient p4 = VIP_Patient("name4", "surname4", "patromymic4", State::REGULAR, 30000);
		AddPatient(p1);
		AddPatient(p2);
		AddPatient(p3);
		AddPatient(p4);
	}
	Patient GetPatient() {
		if (!_patients.IsEmpty())
			return _patients.Pop();
		else
			throw std::out_of_range("Queue is empty");
	}
	void AddPatient(Patient& patient) {
		//if(dynamic_cast<VIP_Patient*>(&patient) == nullptr)
		if (!_patients.IsFull())
			_patients.PriorityPush(patient);
		else
			throw std::overflow_error("Queue is full");
		
	}
};

