#pragma once
#include "sensor.h"
#include <string>
#include <vector>

using namespace std;


class SimInfo

{

private:

	vector<string> Head;
	vector<string> Body;
	vector<string> Conclusion;

public:

	SimInfo();

	void PrintSim();

};