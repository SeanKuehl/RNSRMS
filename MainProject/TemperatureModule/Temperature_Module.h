#pragma once

#include "module_interface.h"

#include <iostream>
#include <fstream>

using namespace std;



class Temperature : public module_interface {

private:
	float Temperature_Value;
	float AirFlow_Value;
	int WorkLoad_Value;
	int FanSpeed;

	int Temperature_Value_Index;

	bool Auto;

	SimInfo TempSim;

	SensorInfo TempSensor;

	

	vector<string> Temperature_Value_Range;
	vector<string> AirFlow_Value_Range;
	vector<string> Workload_Value_Range;

	const float TempMaxThreshold = 24;
	const float TempMinThreshold = 16;
	const float TempMaxExpectedMax = 21;
	const float TempMinExpectedMin = 20;

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

	void ChangeSpeed(int Speed);

	void ManualAdjust(int Speed);
};







