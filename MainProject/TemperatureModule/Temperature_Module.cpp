#pragma once

#include "Temperature_Module.h"

#define TEMPERATURE_FLUC_FILE "TemperatureModule/Temperature.txt"
#define AIRFLOW_FILE "TemperatureModule/AirFlow.txt"
#define WORKLOAD_FILE "TemperatureModule/WorkLoad.txt"
#define ACTIVEFANS_FILE "TemperatureModule/ActiveFans.txt"
#define FANSPEED_FILE "TemperatureModule/FanSpeed.txt"

using namespace std;

// Gathers default values from the text files and loads them up in the class.
Temperature::Temperature()
{
	Temperature_Value_Range = ReadFile(TEMPERATURE_FLUC_FILE);
	TempSensorNames.push_back("workload");
	ReadFileSensors(WORKLOAD_FILE);
	TempSensorNames.push_back("airflow");
	ReadFileSensors(AIRFLOW_FILE);
	TempSensorNames.push_back("activefans");
	ReadFileSensors(ACTIVEFANS_FILE);
	TempSensorNames.push_back("fanspeed");
	ReadFileSensors(FANSPEED_FILE);


	Temperature_Value_Index = 0;
	WorkLoad_Value_Index = 3;
	AirFlow_Value_Index = 2;
	ActiveFans_Value_Index = 2;
	FanSpeed_Value_Index = 3;

	Calculate();

	TempSensor.AddSensor(Sensor(TempSensorNames.at(0), TempSensorValues.at(0)));
	TempSensor.AddSensor(Sensor(TempSensorNames.at(1), TempSensorValues.at(1)));
	TempSensor.AddSensor(Sensor(TempSensorNames.at(2), TempSensorValues.at(2)));
	TempSensor.AddSensor(Sensor(TempSensorNames.at(3), TempSensorValues.at(3)));
}

SimInfo Temperature::getSim() {

	vector<string> Head;
	vector<string> Body;
	vector<string> Conclusion;
	Head.push_back("\n");
	Head.push_back("--------------- Temperature ---------------");
	Head.push_back("\n");
	Calculate();
	Body.push_back("Temperature: " + to_string(Temperature_Value) + "C");
	Body.push_back("\n");

	Body.push_back("workload: ");
	for (int i = 0; i < TempSensorValues.at(0).size(); i++) {
		if (i == WorkLoad_Value_Index) {
			Body.push_back(" *" + to_string(WorkLoad_Value) + "*");
		}
		else {
			Body.push_back(" " + to_string(stoi(TempSensorValues.at(0).at(i))));
		}
	}
	Body.push_back("\n");

	Body.push_back("airflow:  ");
	for (int i = 0; i < TempSensorValues.at(1).size(); i++) {
		if (i == AirFlow_Value_Index) {
			Body.push_back(" *" + to_string(AirFlow_Value) + "*");
		}
		else {
			Body.push_back(" " + to_string(stoi(TempSensorValues.at(1).at(i))));
		}
	}
	Body.push_back("\n");

	Body.push_back("activefans: ");
	for (int i = 0; i < TempSensorValues.at(2).size(); i++) {
		if (i == ActiveFans_Value_Index) {
			Body.push_back(" *" + to_string(ActiveFans_Value) + "*");
		}
		else {
			Body.push_back(" " + to_string(stoi(TempSensorValues.at(2).at(i))));
		}
	}
	Body.push_back("\n");

	Body.push_back("fanspeed: ");
	for (int i = 0; i < TempSensorValues.at(3).size(); i++) {
		if (i == FanSpeed_Value_Index) {
			Body.push_back(" *" + to_string(FanSpeed_Value) + "*");
		}
		else {
			Body.push_back(" " + to_string(stoi(TempSensorValues.at(3).at(i))));
		}
	}
	Body.push_back("\n");

	Conclusion.push_back("---------------------------------------------");
	Conclusion.push_back("\n");

	TempSim = SimInfo(Head, Body, Conclusion);

	return TempSim;
}

SensorInfo Temperature::getSensorInfo() {
	return TempSensor;
}

void Temperature::ChangeValue(string TargetSensor, string NewValue) {

	string Temp = TargetSensor;

	transform(Temp.begin(), Temp.end(), Temp.begin(), ::tolower);

	if (Temp == "workload") {
		for (int i = 0; i < TempSensorValues.at(0).size(); i++) {
			if (TempSensorValues.at(0).at(i) == NewValue) {
				WorkLoad_Value_Index = i;
			}
		}
	}
	else if (Temp == "airflow") {
		for (int i = 0; i < TempSensorValues.at(1).size(); i++) {
			if (TempSensorValues.at(1).at(i) == NewValue) {
				AirFlow_Value_Index = i;
			}
		}
	}
	else if (Temp == "activefans") {
		for (int i = 0; i < TempSensorValues.at(2).size(); i++) {
			if (TempSensorValues.at(2).at(i) == NewValue) {
				ActiveFans_Value_Index = i;
			}
		}
	}
	else if (Temp == "fanspeed") {
		for (int i = 0; i < TempSensorValues.at(3).size(); i++) {
			if (TempSensorValues.at(3).at(i) == NewValue) {
				FanSpeed_Value_Index = i;
			}
		}
	}
}

void Temperature::TemperatureSensor() {

	Temperature_Value_Index += 1;

	if (Temperature_Value_Index > 9) {

		Temperature_Value_Index = 0;
	}

	Temperature_Value = stoi(Temperature_Value_Range.at(Temperature_Value_Index));
}

// This function handles all of the main calculations and relations between Temperature, AirFlow and WorkLoad.
void Temperature::Calculate() {

	TemperatureSensor();

	WorkLoad_Value = stoi(TempSensorValues.at(0).at(WorkLoad_Value_Index));
	AirFlow_Value = stoi(TempSensorValues.at(1).at(AirFlow_Value_Index));
	ActiveFans_Value = stoi(TempSensorValues.at(2).at(ActiveFans_Value_Index));
	FanSpeed_Value = stoi(TempSensorValues.at(3).at(FanSpeed_Value_Index));

	Temperature_Value += (WorkLoad_Value / 10);

	AirFlow_Value = ((AirFlow_Value / 100) * FanSpeed_Value * ActiveFans_Value);

	Temperature_Value -= (AirFlow_Value/300);

}

// Reads a file and saves all of its values in a vector string
vector<string> Temperature::ReadFile(string FileName) {

	vector<string> FileData;

	string FileLine;

	ifstream FileReader(FileName);

	while (getline(FileReader, FileLine)) {

		FileData.push_back(FileLine);
	}

	FileReader.close();

	return FileData;
}

void Temperature::ReadFileSensors(string FileName) {

	vector<string> FileData;

	string FileLine;

	ifstream FileReader(FileName);

	while (getline(FileReader, FileLine)) {

		FileData.push_back(FileLine);

	}

	FileReader.close();

	TempSensorValues.push_back(FileData);
}