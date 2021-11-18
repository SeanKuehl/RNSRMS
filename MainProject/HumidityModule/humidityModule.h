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
	string fanSpeed = "122.3";
	string humidity = "56.2";	
	string pressure = "14.1";
	string airConditionTemp = "22.1";



	void getFileValue(string fileName);

	
	int getValueRange();

	void getSensorInformation(string fileName);


};
