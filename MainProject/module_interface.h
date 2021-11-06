#pragma once
#include "SensorInfo.h";
#include "simInfo.h";

using namespace std;

class module_interface
{
public:

	module_interface();

	virtual SimInfo getSim();

	virtual SensorInfo getSensorInfo();

	virtual void ChangeValue(string, string);

};

