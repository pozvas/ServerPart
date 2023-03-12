#include "PatientRepository.h"

PatientRepository::PatientRepository() {
	VIP_Patient p1 = VIP_Patient("name1", "surname1", "patromymic1", State::REGULAR, 10000);
	Patient p2 = Patient("name2", "surname2", "patromymic2", State::REGULAR);
	Patient p3 = Patient("name3", "surname3", "patromymic3", State::CRITICAL);
	VIP_Patient p4 = VIP_Patient("name4", "surname4", "patromymic4", State::REGULAR, 30000);
	AddPatient(p1);
	AddPatient(p2);
	AddPatient(p3);
	AddPatient(p4);
}

Patient PatientRepository::GetPatient() {
	/*if (!_patients.IsEmpty())
		return _patients.Pop();
	else
		throw std::out_of_range("Queue is empty");*/

	if (!_vipPatients.IsEmpty()) {
		if (!_regularPatients.IsEmpty() && _regularPatients.Top().GetState() == State::CRITICAL
			&& _vipPatients.Top().GetState() != State::CRITICAL)
			return _regularPatients.Pop();
		else
			return _vipPatients.Pop();
	}
	else if (!_regularPatients.IsEmpty()) {
		return _regularPatients.Pop();
	}
	else
		throw std::out_of_range("Queue is empty");
}

void PatientRepository::AddPatient(Patient& patient) {
	/*if (patient.GetState() == State::CRITICAL) {
		if (!_patients.StartPush(patient))
			throw std::overflow_error("Queue is full");
	}
	else {
		if (dynamic_cast<VIP_Patient*>(&patient) == nullptr) {
			if (!_patients.PriorityPush(patient))
				throw std::overflow_error("Queue is full");
		}
		else {
			if (!_patients.Push(patient))
				throw std::overflow_error("Queue is full");
		}
	}*/
	VIP_Patient* castPatient = dynamic_cast<VIP_Patient*>(&patient);
	if (castPatient != nullptr) {
		if (!_vipPatients.PriorityPush(*castPatient))
			throw std::overflow_error("Queue is full");
	}
	else {
		if (!_regularPatients.PriorityPush(patient))
			throw std::overflow_error("Queue is full");
	}


}
