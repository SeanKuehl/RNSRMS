#pragma once

#include "module_interface.h"
#include "iostream";
#include "string";
#include "vector";
#include "fstream";

class Network : public module_interface
{
private:

	/*
	Note:
	average WIFI speed = 12 - 25 Mbps
	average ethernet speed = 45 - 100MBps
	*/
	double maxBandwidth = 800; //units in Megabits(Mb)
	double minBandwidth = 8; // 8Mb = 1MB
	double currentMax = 80; // <= 10MBps
	double currentSpeed = 50;
	string connectionType = "WIFI";

	SensorInfo mySensors;
	SimInfo mySim;
	vector <string> connectedDevices;
	vector<string> sensorNames;
	vector<vector<string>> sensorValues;
	void GetSensorsAndSensorInformationFromFile(string fileName);
	double calcCurrentSpeed();

public:
	Network();

	SimInfo getSim();

	SensorInfo getSensorInfo();

	void ChangeValue(string, string);

	void addDevice(vector<string>);	//allows user to add a connection outside the server

	void deleteDevice(vector<string>);	//allows user to delete a connection outside the server
};