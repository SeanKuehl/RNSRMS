#include "Memory.h"

#define FLUCT_VAL_FILE "MemoryModule/MemoryFluctuatingValue.txt"
#define SENSOR_FILE "MemoryModule/MemorySensors.txt"

Memory::Memory() {
	//must init stuff
	fluctuatingValueIndex = 0;
	GetContentFromFile(FLUCT_VAL_FILE);
	GetSensorsAndSensorInformationFromFile(SENSOR_FILE);

	//sensors currently has error in it at the moment
	mySensors.AddSensor(Sensor(sensorNames.at(0), sensorValues.at(0)));
	mySensors.AddSensor(Sensor(sensorNames.at(1), sensorValues.at(1)));
	mySensors.AddSensor(Sensor(sensorNames.at(2), sensorValues.at(2)));
	mySensors.AddSensor(Sensor(sensorNames.at(3), sensorValues.at(3)));


}

SimInfo Memory::getSim() {
	//this func isn't done, must change fluct index after
	//also may need to remake sim each time
	string tempString = "";

	vector<string> head;
	head.push_back("----Memory----");
	head.push_back("\n");

	vector<string> body;
	body.push_back("RAM: " + to_string(CalculateFluctuatingValueRange()) + fluctuatingValueAddon);
	body.push_back("\n");

	for (int i = 0; i < sensorNames.size(); i++) {
		tempString += sensorNames.at(i) + ": ";

		for (int k = 0; k < sensorValues.at(i).size(); k++) {
			if (sensorNames.at(i) == "processes") {
				if (stoi(sensorValues.at(i).at(k)) == processes) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}
				
			}
			

			if (sensorNames.at(i) == "allocation") {
				if (stoi(sensorValues.at(i).at(k)) == allocation) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}
			


			if (sensorNames.at(i) == "threads") {
				if (stoi(sensorValues.at(i).at(k)) == threads) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	//this indicates that this is the selected value
				}
				else {
					tempString += sensorValues.at(i).at(k) + " ";
				}

			}
			

			if (sensorNames.at(i) == "cpus") {
				if (stoi(sensorValues.at(i).at(k)) == cpus) {
					tempString += "*" + sensorValues.at(i).at(k) + "* ";	//this indicates that this is the selected value
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

	
	mySim = SimInfo(head, body, conclusion);
	//mySim.PrintSim();

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

SensorInfo Memory::getSensorInfo() {
	return mySensors;
}

void Memory::ChangeValue(string sensorName, string sensorValue) {
	//because of verify value, I know these inputs must be valid
	
	if (sensorName == "processes") {
		processes = stoi(sensorValue);
	}
	else if (sensorName == "allocation") {
		allocation = stoi(sensorValue);
	}
	else if (sensorName == "threads") {
		threads = stoi(sensorValue);
	}
	else if (sensorName == "cpus") {
		cpus = stoi(sensorValue);
	}
	

}


//this function will be used to read data from a file for the fluctuating value
void Memory::GetContentFromFile(string fileName) {
	// Create a text string, which is used to output the text file
	string myText;

	// Read from the text file
	ifstream MyReadFile(fileName);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(MyReadFile, myText)) {
		// Output the text from the file
		fluctuatingValueParts.push_back(stoi(myText));
	}

	// Close the file
	MyReadFile.close();
}

//this function will use the values of all sensors to determine what state the system is in, it will
//return an int, this is the number that will be added or subtracted to/from the base fluctuating value to give it it's appropriate range(doesn't need inputs because the sensors are data members of the class)
int Memory::CalculateFluctuatingValueRange() {

	int fluctuatingValueToShow = fluctuatingValueParts.at(fluctuatingValueIndex);
	int range = processes * allocation * threads * cpus;

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

//this function will be used to read sensor names and values from a file and set the data members. Because it will set data memebers, this function returns void
void Memory::GetSensorsAndSensorInformationFromFile(string fileName) {
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
			sensorValues.push_back(tempValues);
			tempValues = {};
			//skip this one, last one ended
		}

		else if (nameNotValue) {
			sensorNames.push_back(myText);
			nameNotValue = false;
		}
		else if (nameNotValue == false) {
			tempValues.push_back(myText);
		}
		
		

		
	}

	// Close the file
	MyReadFile.close();
}