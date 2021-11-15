#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TempSim
{

private:

	vector<string> Head;
	vector<string> Body;
	vector<string> Conclusion;

public:

	TempSim(vector<string>, vector<string>, vector<string>);

	void PrintSim();

};

