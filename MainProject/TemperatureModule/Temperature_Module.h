#pragma once

#include "module_interface.h"

#include <iostream>
#include <fstream>

using namespace std;



class Temperature : public module_interface {

private:
	double Temperature_Value;
	double AirFlow_Value;
	double WorkLoad_Value;
	double FanSpeed;

	int Temperature_Value_Index;

	bool Auto;

	SimInfo TempSim;

	SensorInfo TempSensor;

	

	vector<string> Temperature_Value_Range;
	vector<string> AirFlow_Value_Range;
	vector<string> Workload_Value_Range;

	const double TempMaxThreshold = 28;
	const double TempMinThreshold = 10;
	const double TempMaxExpectedMax = 21;
	const double TempMinExpectedMin = 20;

public:

	void ChangeValue(string, string);

	Temperature();
	
	SimInfo getSim();

	SensorInfo getSensorInfo();

	void AutoAdjust();

	void TemperatureSensor();

	void Calculate();

	vector<string> ReadFile(string);

	void WorkLoadSensor();

	void AirFlowSensor();

	void ChangeSpeed(double Speed);

	void ManualAdjust(double Speed);
};







