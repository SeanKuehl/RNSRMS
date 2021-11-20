#include "network.h";

#define SENSOR_FILE	 "NetworkModule/NetworkSensors.txt"
#define FLUCT_VAL_FILE "NetworkModule/fluctValues.txt"

//Initialize Network class
Network::Network()
{
	GetSensorInfoFromFile(SENSOR_FILE);
	GetContentFromFile(FLUCT_VAL_FILE);
	fluctuatingValueIndex = 0;

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
	if (connectionType == "WIFI")
	{
		body.push_back("Current network speed: " + to_string(calcCurrentSpeed()) + " Mbps");
		body.push_back("\n");
	}
	else if (connectionType == "ethernet")
	{
		body.push_back("Current network speed: " + to_string(calcCurrentSpeed()) + " MBps");
		body.push_back("\n");
	}

	for (int i = 0; i < deviceName.size(); i++) {
		tempString += deviceName.at(i) + ": ";

		for (int k = 0; k < deviceConnection.at(i).size(); k++) {
			if (deviceName.at(i) == "CPU") {
				if (deviceConnection.at(i).at(k) == CPU) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}
			}

			if (deviceName.at(i) == "switches") {
				if (deviceConnection.at(i).at(k) == switches) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}
			}

			if (deviceName.at(i) == "routers") {
				if (deviceConnection.at(i).at(k) == routers) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}
			}

			if (deviceName.at(i) == "RAM") {
				if (deviceConnection.at(i).at(k) == RAM) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}
			}

			if (deviceName.at(i) == "fans") {
				if (deviceConnection.at(i).at(k) == fans) {
					tempString += "*" + deviceConnection.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += deviceConnection.at(i).at(k) + " ";
				}
			}

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

	//increment the fluctuating value index for next time
	int maxNumOfValues = 10;
	fluctuatingValueIndex += 1;
	if (fluctuatingValueIndex < maxNumOfValues) {
		//that's fine
	}
	else {
		fluctuatingValueIndex = 0;
	}


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
		routers = value;
	}
	else if (name == "fans") {
		fans = value;
	}
	else if (name == "RAM") {
		RAM = value;
	}
	else if (name == "laptop1") {
		laptop1 = value;
	}
	else if (name == "laptop2") {
		laptop2 = value;
	}
	else if (name == "PC1") {
		PC1 = value;
	}
	else if (name == "PC2") {
		PC2 = value;
	}
	else if (name == "AdminPC") {
		AdminPC = value;
	}

}

//this function will be used to read data from a file for the fluctuating value
void Network::GetContentFromFile(string fileName) {
	// Create a text string, which is used to output the text file
	string myText;

	// Read from the text file
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		fluctuatingValues.push_back(stoi(myText));
	}

	// Close the file
	MyReadFile.close();
}

//Calculate the current network speed
int Network::calcCurrentSpeed()	//no input needed since values are 
{
	/*
	Note:
	average WIFI speed = 12 - 25 Mbps
	average ethernet speed = 45 - 100 MBps
	*/
	int valueToShow = fluctuatingValues.at(fluctuatingValueIndex);


	if (connectionType == "WIFI")
	{
		valueToShow += 12; //12 Mbps is the min speed for wifi
	}
	else if (connectionType == "ethernet")
	{
		valueToShow = 100 - (valueToShow * 2); //this will read whatever value from the text file and subtract from the max speed(100 MBps)
	}

	return valueToShow;
}

void Network::GetSensorInfoFromFile(string fileName) {
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