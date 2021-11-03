#pragma once
#include "sensor.h"
#include <string>
#include <vector>

using namespace std;


class SensorInfo
{

public:

	SensorInfo();

	bool VerifyInput(string name, string value);

	void AddSensor(Sensor toAdd);


private:
	vector<Sensor> sensorList;


};

