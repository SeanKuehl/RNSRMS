#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class simTesting
{

private:

	vector<string> Head;
	vector<string> Body;
	vector<string> Conclusion;

public:

	simTesting(vector<string>, vector<string>, vector<string>);

	void PrintSim();

};