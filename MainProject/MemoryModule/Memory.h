#pragma once

#include "module_interface.h"
#include "TempSim.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Memory : public module_interface
{
public:

	Memory();

	SimInfo getSim();

	SensorInfo getSensorInfo();

	void ChangeValue(string, string);


	

private:
	SensorInfo mySensors;
	SimInfo mySim;

	vector<string> sensorNames;
	vector<vector<string>> sensorValues;

	vector<int> fluctuatingValueParts;
	int fluctuatingValueIndex = -1;	//-1 so it can't be a valid value by default
	string fluctuatingValueAddon = "";
	int processes = 5;	//default value
	int allocation = 5;	//default value
	int threads = 3;	//default value
	int cpus = 1;	//default value


	//this function will be used to read data from a file for the fluctuating value
	void GetContentFromFile(string fileName);

	//this function will use the values of all sensors to determine what state the system is in, it will
	//return an int, this is the number that will be added or subtracted to/from the base fluctuating value to give it it's appropriate range(doesn't need inputs because the sensors are data members of the class)
	int CalculateFluctuatingValueRange();

	//this function will be used to read sensor names and values from a file and set the data members. Because it will set data memebers, this function returns void
	void GetSensorsAndSensorInformationFromFile(string fileName);


};

