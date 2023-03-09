#pragma once
#include <iostream>

enum class State {
	UNDEFIEND,
	REGULAR,
	MEDIUM,
	CRITICAL
};
class Patient
{
protected:
	std::string _firstname;
	std::string _lastname;
	std::string _patronymic;
	State _state;
public:
	Patient() : _state(State::UNDEFIEND) {}
	Patient(const std::string& firstname,
			const std::string& lastname,
			const std::string& patronymic,
			State state) : _firstname(firstname), _lastname(lastname), _patronymic(patronymic), _state(state) {}
	std::string GetFirstname() const { return _firstname; }
	std::string GetLastname() const { return _lastname; }
	std::string GetPatronymic() const { return _patronymic; }
	State GetState() const { return _state; }
	bool operator>(const Patient& p) const {
		if (p._state == State::CRITICAL) return false;
		else return true;
	}
	virtual ~Patient() {}
};

class VIP_Patient : public Patient{
private:
	size_t _moneyAmount;
public:
	VIP_Patient():Patient(){}
	VIP_Patient(const std::string& firstname,
		const std::string& lastname,
		const std::string& patronymic,
		State state,
		size_t moneyAmount = 100) : Patient(firstname, lastname, patronymic, state), _moneyAmount(moneyAmount) {
	}
	size_t GetMoney() const { return _moneyAmount; }
	bool operator>(const VIP_Patient& p) const {
		if (p._state == State::CRITICAL || p.GetMoney() >= this->GetMoney()) return false;
		else return true;
	}
};




	