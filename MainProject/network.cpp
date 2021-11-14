#include "network.h";
#include <stdlib.h>
#include <time.h>

#define SENSOR_FILE	 "NetworkSensors.txt"

//Initialize Network class
Network::Network()
{
	GetSensorInfoFromFile(SENSOR_FILE);
}

SimInfo Network::getSim()
{
	string tempString = "";

	vector<string> head;
	head.push_back("----Network----");
	head.push_back("\n");

	vector<string> body;
	body.push_back("Max Bandwidth: " + to_string(currentMaxBand) + " Mbps");
	body.push_back("\n");

	for (int i = 0; i < sectionName.size(); i++)
	{
		tempString += sectionName.at(i) + ": ";

		for (int j = 0; j < deviceName.size(); j++)
		{
			tempString += deviceName.at(j) + ": ";

			for (int k = 0; k < deviceConnection.at(j).size(); k++)
			{
				if (sectionName.at(j) == "CPU")
				{
					if (deviceConnection.at(j).at(k) == CPU) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}

				if (sectionName.at(j) == "switches")
				{
					if (deviceConnection.at(j).at(k) == switches) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}

				if (sectionName.at(j) == "router")
				{
					if (deviceConnection.at(j).at(k) == router) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}

				if (sectionName.at(j) == "fans")
				{
					if (deviceConnection.at(j).at(k) == fans) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}

				if (sectionName.at(j) == "RAM")
				{
					if (deviceConnection.at(j).at(k) == RAM) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}

				if (sectionName.at(j) == "laptop1")
				{
					if (deviceConnection.at(j).at(k) == connectionType) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}
				if (sectionName.at(j) == "laptop2")
				{
					if (deviceConnection.at(j).at(k) == connectionType) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}
				if (sectionName.at(j) == "PC1")
				{
					if (deviceConnection.at(j).at(k) == connectionType) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}
				if (sectionName.at(j) == "PC2")
				{
					if (deviceConnection.at(j).at(k) == connectionType) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}
				if (sectionName.at(j) == "AdminPC")
				{
					if (deviceConnection.at(j).at(k) == connectionType) {
						tempString += "*" + deviceConnection.at(j).at(k) + "* ";	//this indicates that this is the selected value
					}
					else {
						tempString += deviceConnection.at(j).at(k) + " ";
					}

				}
			}
			body.push_back(tempString);
			body.push_back("\n");
			tempString = "";
		}
	}

	vector<string> conclusion;
	conclusion.push_back("--------------");

	return mySim;
}

SensorInfo Network::getSensorInfo() 
{
	return mySensors;
}

void Network::ChangeValue(string name, string value)	//i know that the 'value' has to be valid because of validation
{
	if (name == "bandwidth") {
		 currentMaxBand= stoi(value);
	}
	else if (name == "CPU") {
		CPU = value;
	}
	else if (name == "switches") {
		switches = value;
	}
	else if (name == "router") {
		router = value;
	}
	else if (name == "fans") {
		fans = value;
	}
	else if (name == "RAM") {
		RAM = value;
	}
	else if (name == "laptop1") {
		RAM = value;
	}
	else if (name == "laptop2") {
		RAM = value;
	}
	else if (name == "PC1") {
		RAM = value;
	}
	else if (name == "PC2") {
		RAM = value;
	}
	else if (name == "AdminPC") {
		RAM = value;
	}

}

//Calculate the current network speed
void Network::calcCurrentSpeed()	//no input needed since values are 
{
	/*
	Note:
	average WIFI speed = 12 - 25 Mbps
	average ethernet speed = 45 - 100 MBps
	*/
	double tempSpeed = currentSpeed;

	srand(time(0));

	if (connectionType == "WIFI")
	{
		tempSpeed = rand() % 13 + 12;	//gives range from 12-24
	}
	else if (connectionType == "ethernet")
	{
		tempSpeed = rand() % 440 + 360;	//gives range from 360-799
	}

	currentSpeed = tempSpeed;
}

void Network::GetSensorInfoFromFile(string fileName) {
	// Create a text string, which is used to output the text file
	string myText;

	bool isSectionName = true;
	bool isDeviceName = false;
	vector<string> tempValues;

	// Read from the text file
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file

		if (myText == "x") {
			isSectionName = true;
			isDeviceName = false;
			deviceConnection.push_back(tempValues);
			tempValues = {};
			//end of section
		}
		else if (isSectionName) {
			sectionName.push_back(myText);
			isSectionName = false;
			isDeviceName = true;
		}
		else if (isDeviceName) {
			deviceName.push_back(myText);
			isDeviceName = false;
		}
		else if (isSectionName == false && isDeviceName == false)
		{
			tempValues.push_back(myText);
		}
	}

	// Close the file
	MyReadFile.close();
}