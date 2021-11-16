#pragma once
#pragma once

#include "module_interface.h"


#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Humidity : public module_interface
{
public:

	Humidity();

	SimInfo getSim();

	SensorInfo getSensorInfo();

	void ChangeValue(string, string);




private:
	SensorInfo Sensors;
	SimInfo Sim;

	vector<string> sensorNames;
	vector<vector<string>> sensorValues;

	vector<int> fluctuatingValueParts;
	int fluctuatingValueIndex = -1;	
	string fluctuatingValueAddon = "";
	double fanSpeed = 200.0;	
	double humidity = 52.2;	
	double pressure = 16.1;
	double airConditionTemp = 22.0;



	void getFileValue(string fileName);

	
	int getValueRange();

	void getSensorInformation(string fileName);


};
