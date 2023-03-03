#pragma once
#include <iostream>
#include "Patient.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DataHandler
{
public:
	static std::string Packing(const Patient& patient) {
		return json{ {"firstname", patient.GetFirstname()}, {"lastname", patient.GetLastname()}, 
				{"patronymic", patient.GetPatronymic()}, {"state", patient.GetState()}}.dump();

	}


	static Patient Unpacking(const std::string& str) {
		json j = json::parse(str);
		if (j.contains("money"))
			return VIP_Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"), j.at("money"));
		else
			return Patient(j.at("firstname"), j.at("lastname"), j.at("patronymic"), j.at("state"));
	}
};


