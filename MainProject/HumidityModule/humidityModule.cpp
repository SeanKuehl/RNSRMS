#include "humidityModule.h"
#include <fstream>

#define FLUCT_VAL_FILE "HumidityModule/humidityFluctuatingValue.txt"
#define SENSOR_FILE "HumidityModule/humiditySensors.txt"

Humidity::Humidity() {
	
	fluctuatingValueIndex = 0;
	getFileValue(FLUCT_VAL_FILE);
	getSensorInformation(SENSOR_FILE);

	
	Sensors.AddSensor(Sensor(sensorNames.at(0), sensorValues.at(0)));
	Sensors.AddSensor(Sensor(sensorNames.at(1), sensorValues.at(1)));
	Sensors.AddSensor(Sensor(sensorNames.at(2), sensorValues.at(2)));
	Sensors.AddSensor(Sensor(sensorNames.at(3), sensorValues.at(3)));
	

}

SimInfo Humidity::getSim() {

	string tempString = "";

	vector<string> head;
	head.push_back("----Humidity----");
	head.push_back("\n");

	vector<string> body;
	body.push_back("Relative Humidity: " + to_string(getValueRange()) + fluctuatingValueAddon);
	body.push_back("\n");

	for (int i = 0; i < sensorNames.size(); i++) {
		tempString += sensorNames.at(i) + ": ";

		for (int k = 0; k < sensorValues.at(i).size(); k++) {
			if (sensorNames.at(i) == "fanspeed") {
				if (sensorValues.at(i).at(k) == fanspeed) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}


			if (sensorNames.at(i) == "humidity") {
				if (sensorValues.at(i).at(k) == humidity) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}



			if (sensorNames.at(i) == "pressure") {
				if (sensorValues.at(i).at(k) == pressure) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}

			if (sensorNames.at(i) == "airconditiontemp") {
				if (sensorValues.at(i).at(k) == airconditiontemp) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}
		}
		body.push_back(tempString);
		body.push_back("\n");
		tempString = "";
	}

	vector<string> conclusion;
	conclusion.push_back("--------------");


	Sim = SimInfo(head, body, conclusion);
	//Sim.PrintSim();

	int maxNumOfValues = 10;
	fluctuatingValueIndex += 1;
	if (fluctuatingValueIndex < maxNumOfValues) {

	}
	else {
		fluctuatingValueIndex = 0;
	}

	return Sim;
}

SensorInfo Humidity::getSensorInfo() {
	return Sensors;
}

void Humidity::ChangeValue(string sensorName, string sensorValue) {


	if (sensorName == "fanspeed") {
		fanspeed = stoi(sensorValue);
	}
	else if (sensorName == "humidity") {
		humidity = stoi(sensorValue);
	}
	else if (sensorName == "pressure") {
		pressure = stoi(sensorValue);
	}
	else if (sensorName == "airconditiontemp") {
		pressure = stoi(sensorValue);
	}
}



void Humidity::getFileValue(string fileName) {

	string myText;


	ifstream MyReadFile(fileName);


	while (getline(MyReadFile, myText)) {

		fluctuatingValueParts.push_back(stoi(myText));
	}


	MyReadFile.close();
}


int Humidity::getValueRange() {

	int fluctuatingValueToShow = fluctuatingValueParts.at(fluctuatingValueIndex);
	int range = stod(humidity) * stod(pressure) * stod(fanspeed) * stod(airconditiontemp);

	int lowRangeLimit = 1000;
	int midAndUpperRangeSeperator = 4000;

	if (range < lowRangeLimit) {
		fluctuatingValueToShow += 20;
		fluctuatingValueAddon = "%RH";
	}
	else if (range < midAndUpperRangeSeperator) {
		fluctuatingValueToShow += 40;
		fluctuatingValueAddon = "%RH";
	}
	else if (range > midAndUpperRangeSeperator) {
		fluctuatingValueToShow += 60;
		fluctuatingValueAddon = "%RH";
	}

	return fluctuatingValueToShow;
}


void Humidity::getSensorInformation(string fileName) {


	bool nameNotValue = true;
	vector<string> tempValues;
	string myText;


	ifstream MyReadFile(fileName);


	while (getline(MyReadFile, myText)) {


		if (myText == "x") {
			nameNotValue = true;
			sensorValues.push_back(tempValues);
			tempValues = {};

		}

		else if (nameNotValue) {
			sensorNames.push_back(myText);
			nameNotValue = false;
		}
		else if (nameNotValue == false) {
			tempValues.push_back(myText);
		}




	}


	MyReadFile.close();
}