#pragma once

#include "Temperature_Module.h"

#define TEMPERATURE_FLUC_FILE "TemperatureModule/Temperature.txt"
#define AirFlow_FILE "TemperatureModule/AirFlow.txt"
#define WORKLOAD_FILE "TemperatureModule/WorkLoad.txt"

using namespace std;

// Gathers default values from the text files and loads them up in the class.
Temperature::Temperature()
{
	Temperature_Value_Range = ReadFile(TEMPERATURE_FLUC_FILE);
	Workload_Value_Range = ReadFile(AirFlow_FILE);
	AirFlow_Value_Range = ReadFile(WORKLOAD_FILE);

	Temperature_Value_Index = 0;

	Calculate();
}

SimInfo Temperature::getSim() {

	vector<string> Head;
	vector<string> Body;
	vector<string> Conclusion;

	Head.push_back("################ Temperature ################");

	Calculate();
	Body.push_back("Temperature: " + to_string(Temperature_Value) + "°C");
	Body.push_back("\n");

	Body.push_back("WorkLoad: " + to_string(WorkLoad_Value) + "%");
	Body.push_back("AirFlow: " + to_string(AirFlow_Value) + "CFM");
	Body.push_back("Fan Speed: " + to_string(FanSpeed) + "%");

	Conclusion.push_back("################ Temperature ################");

	TempSim = SimInfo(Head, Body, Conclusion);

	return TempSim;
}

SensorInfo Temperature::getSensorInfo() {
	return TempSensor;
}

void Temperature::ChangeValue(string Target, string Replacement) {
	Target = Replacement;
}

// This function auto adjust the fan speed for the user based off of the current temperature and if the fan needs to be running to support it.
void Temperature::AutoAdjust() {
	FanSpeed = 0;

	if (Temperature_Value >= TempMaxThreshold) {

		double Temp = Temperature_Value - TempMaxThreshold;
		FanSpeed += Temp;

		if (FanSpeed > 100) {

			FanSpeed = 100;
		}
	}
}

// Detects the current Base Temperature before calculating the additional Enviromental Factors
void Temperature::TemperatureSensor() {
	if ((rand() % 100) == 99) {

		Temperature_Value_Index += 1;
	}

	if (Temperature_Value_Index > 9) {

		Temperature_Value_Index = 0;
	}

	Temperature_Value = stoi(Temperature_Value_Range.at(Temperature_Value_Index));
}

// This function handles all of the main calculations and relations between Temperature, AirFlow and WorkLoad.
void Temperature::Calculate() {

	TemperatureSensor();

	WorkLoadSensor();

	Temperature_Value += (WorkLoad_Value / 10);

	if (Auto == true) {

		AutoAdjust();
	}

	AirFlowSensor();

	AirFlow_Value = ((AirFlow_Value / 100) * FanSpeed);

	Temperature_Value -= (AirFlow_Value/100);

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

void Temperature::WorkLoadSensor() {

	if ((rand() % 100) == 99) {

		WorkLoad_Value = stoi(Workload_Value_Range.at(rand() % 10));
	}
}

void Temperature::AirFlowSensor() {

	if ((rand() % 100) == 99) {

		AirFlow_Value = stoi(AirFlow_Value_Range.at(rand() % 10));
	}
}

void Temperature::ChangeSpeed(double Speed) {

	FanSpeed = Speed;
}

void Temperature::ManualAdjust(double Speed) {
	// Integration with the Main Module Needed for this
}
