#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;
class Sensor {
private:
	string name;
	vector<string> values;

public:
	Sensor(string names, vector<string> value) {
		int i = 0;
		char c;

		transform(names.begin(), names.end(), names.begin(), [](unsigned char c) { return tolower(c); });

		for (unsigned int i = 0; i < value.size(); i++) {
			string temp = value[i];

			int j = 0;
			while (temp[j]) {
				temp[j] = tolower(temp[j]); j++;
			}

			value[i] = temp;
		}

		name = names;
		values = value;

	}

	string getName() {
		return name;
	}

	vector<string> getValues() {
		return values;
	}

};