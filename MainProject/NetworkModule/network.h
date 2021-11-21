#pragma once

#include "module_interface.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Network : public module_interface
{
private:

	/*
	Note:
	average WIFI speed = 12 - 25 Mbps
	average ethernet speed = 45 - 100 MBps = 360 - 800 Mbps
	*/
	double maxBandwidth = 800; //units in Megabits(Mb) = 100 MegaBytes(MB)
	double minBandwidth = 12; // min of WIFI (which is lowest it can go)
	double currentMaxBand = 80; // <= 10MBps
	double currentSpeed = 50;	//50Mbps for now
	string connectionType = "wifi";
	
	string cpus = "connected";
	string switches = "connected";
	string routers = "connected";
	string fans = "connected";
	string ram = "connected";

	string laptop1 = "wifi";
	string laptop2 = "wifi";
	string pc1 = "wifi";
	string pc2 = "wifi";
	string adminpc = "wifi";

	vector<int> fluctuatingValues;
	int fluctuatingValueIndex = -1;	//-1 so it can't be a valid value by default

	SensorInfo mySensors;
	SimInfo mySim;
	vector<string> deviceName;
	vector<string> sectionName;
	vector<vector<string>> deviceConnection;
	void GetSensorInfoFromFile(string fileName);
	void GetContentFromFile(string fileName);
	int calcCurrentSpeed();

public:
	Network();

	SimInfo getSim();

	SensorInfo getSensorInfo();

	void ChangeValue(string, string);

	//will add the following if time permits
	//void addDevice(vector<string>);	//allows user to add a connection outside the server

	//void deleteDevice(vector<string>);	//allows user to delete a connection outside the server
};