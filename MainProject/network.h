#pragma once

#include "module_interface.h"
#include "iostream";
#include "string";
#include "vector";

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
	double currentSpeed;
	vector <string> connectedDevices;


public:
	Network();

	SimInfo getSim();

	SensorInfo getSensorInfo();

	void ChangeValue(string, string);
};