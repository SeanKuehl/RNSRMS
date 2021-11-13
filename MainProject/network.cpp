#include "network.h";

void Network::GetSensorsAndSensorInformationFromFile(string fileName) {
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