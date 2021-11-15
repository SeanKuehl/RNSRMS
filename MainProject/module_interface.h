#pragma once
#include "SensorInfo.h"
#include "simInfo.h"

using namespace std;

class module_interface
{
public:

	module_interface();

	virtual SimInfo getSim() = 0;

	virtual SensorInfo getSensorInfo() = 0;

	virtual void ChangeValue(string, string) = 0;

};

