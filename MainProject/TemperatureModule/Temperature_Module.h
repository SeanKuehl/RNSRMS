#pragma once

#include "module_interface.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;



class Temperature : public module_interface {

private:
	SimInfo TempSim;
	SensorInfo TempSensor;
	
	vector<string> TempSensorNames;
	vector<vector<string>> TempSensorValues;

	int Temperature_Value;
	int AirFlow_Value;
	int WorkLoad_Value;
	int FanSpeed_Value;
	int ActiveFans_Value;

	int Temperature_Value_Index;
	int AirFlow_Value_Index;
	int WorkLoad_Value_Index;
	int FanSpeed_Value_Index;
	int ActiveFans_Value_Index;

	vector<string> Temperature_Value_Range;

	const float TempMaxThreshold = 24;
	const float TempMinThreshold = 16;
	const float TempMaxExpectedMax = 21;
	const float TempMinExpectedMin = 20;

public:

	void ChangeValue(string, string);

	Temperature();
	
	SimInfo getSim();

	SensorInfo getSensorInfo();

	void TemperatureSensor();

	void Calculate();

	vector<string> ReadFile(string);

	void ReadFileSensors(string);
};







