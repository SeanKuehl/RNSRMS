#include "network.h";
#include <stdlib.h>
#include <time.h>

#define SENSOR_FILE	 "NetworkModule/NetworkSensors.txt"

//Initialize Network class
Network::Network()
{
	GetSensorInfoFromFile(SENSOR_FILE);

	mySensors.AddSensor(Sensor(deviceName.at(0), deviceConnection.at(0)));
	mySensors.AddSensor(Sensor(deviceName.at(1), deviceConnection.at(1)));
	mySensors.AddSensor(Sensor(deviceName.at(2), deviceConnection.at(2)));
	mySensors.AddSensor(Sensor(deviceName.at(3), deviceConnection.at(3)));
	mySensors.AddSensor(Sensor(deviceName.at(4), deviceConnection.at(4)));


}
//Prints Sim info
SimInfo Network::getSim()
{
	string tempString = "";

	vector<string> head;
	head.push_back("----Network----");
	head.push_back("\n");

	vector<string> body;
	body.push_back("Max Bandwidth: " + to_string(currentMaxBand) + " Mbps");
	body.push_back("\n");

	for (int i = 0; i < deviceName.size(); i++) {
		tempString += deviceName.at(i) + ": ";

		for (int k = 0; k < deviceConnection.at(i).size(); k++) {
			if (deviceName.at(i) == "laptop1") {
				if (deviceConnection.at(i).at(k) == laptop1) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}

			}


			if (deviceName.at(i) == "laptop2") {
				if (deviceConnection.at(i).at(k) == laptop2) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}

			}



			if (deviceName.at(i) == "PC1") {
				if (deviceConnection.at(i).at(k) == PC1) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}

			}


			if (deviceName.at(i) == "PC2") {
				if (deviceConnection.at(i).at(k) == PC2) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}

			}

			if (deviceName.at(i) == "AdminPC") {
				if (deviceConnection.at(i).at(k) == AdminPC) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}

			}





		}
		body.push_back(tempString);
		body.push_back("\n");
		tempString = "";
	}

	vector<string> conclusion;
	conclusion.push_back("--------------");

	mySim = SimInfo(head, body, conclusion);

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
	}//all connection types are linked(if one changes all of them do) <-- this is due to time constraint
	else if (name == "laptop1") {
		connectionType = value;
	}
	else if (name == "laptop2") {
		connectionType = value;
	}
	else if (name == "PC1") {
		connectionType = value;
	}
	else if (name == "PC2") {
		connectionType = value;
	}
	else if (name == "AdminPC") {
		connectionType = value;
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
	// Create a text string, which is used to output the text file
	string myText;

	bool nameNotValue = true;
	vector<string> tempValues;

	// Read from the text file
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file

		if (myText == "x") {
			nameNotValue = true;
			deviceConnection.push_back(tempValues);
			tempValues = {};
			//skip this one, last one ended
		}

		else if (nameNotValue) {
			deviceName.push_back(myText);
			nameNotValue = false;
		}
		else if (nameNotValue == false) {
			tempValues.push_back(myText);
		}




	}

	// Close the file
	MyReadFile.close();
}