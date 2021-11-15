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
	//Sensors.AddSensor(Sensor(sensorNames.at(3), sensorValues.at(3)));
	//there is a sensor missing from the read file, Cyril please fix
	//then uncomment this line to make sure the addition works

}

SimInfo Humidity::getSim() {

	string tempString = "";

	vector<string> head;
	head.push_back("----Humidity----");
	head.push_back("\n");

	vector<string> body;
	body.push_back("RAM: " + to_string(getValueRange()) + fluctuatingValueAddon);
	body.push_back("\n");

	for (int i = 0; i < sensorNames.size(); i++) {
		tempString += sensorNames.at(i) + ": ";

		for (int k = 0; k < sensorValues.at(i).size(); k++) {
			if (sensorNames.at(i) == "fanSpeed") {
				if (stoi(sensorValues.at(i).at(k)) == fanSpeed) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}


			if (sensorNames.at(i) == "humidity") {
				if (stoi(sensorValues.at(i).at(k)) == humidity) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}



			if (sensorNames.at(i) == "pressure") {
				if (stoi(sensorValues.at(i).at(k)) == pressure) {
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


	if (sensorName == "fanSpeed") {
		fanSpeed = stoi(sensorValue);
	}
	else if (sensorName == "humidity") {
		humidity = stoi(sensorValue);
	}
	else if (sensorName == "pressure") {
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
	int range = humidity * pressure * fanSpeed ;

	int lowRangeLimit = 1000;
	int midAndUpperRangeSeperator = 4000;

	if (range < lowRangeLimit) {
		fluctuatingValueToShow += 20;
		fluctuatingValueAddon = "MB";
	}
	else if (range < midAndUpperRangeSeperator) {
		fluctuatingValueToShow += 900;
		fluctuatingValueAddon = "MB";
	}
	else if (range > midAndUpperRangeSeperator) {
		fluctuatingValueToShow += 0;
		fluctuatingValueAddon = "GB";
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