#include <iostream>
#include <vector>
#include <string>
#include "SensorInfo.h"
#include "simInfo.h"
#include "humidityModule.h"

using namespace std;

void RumSim();
void MainMenu();
void HandleUserInput();

//instance objects of all modules here
Humidity humidityModule = Humidity();

int main(void) {

	
	vector<SensorInfo> sensorInformation;
	//add the sensor info from all the modules to the list
	sensorInformation.push_back(humidityModule.getSensorInfo());




}


void MainMenu() {

	string userInput = "";


	while (userInput == "") {
		cout << "Welcome to RNSRMS, enter a command, 'exit' or 'sim." << endl;

		//call each module's getsim and call it's printsim
		SimInfo humSim = humidityModule.getSim();
		humSim.PrintSim();

		//call handle user input


	}

	



}

void HandleUserInput() {

	string temp = "";
	string collector = "";
	string moduleName = "";
	string sensorName = "";
	string sensorValue = "";
	int howManyTaken = 0;

	getline(cin, temp);


	if (temp == "exit") {

	}
	else if (temp == "sim") {
		//run sim
	}
	else {
		//its just a regular command

		for (int i = 0; i < temp.size(); i++) {
			if (temp.at(i) != ' ') {
				collector += temp.at(i);
			}
			else if (temp.at(i) == ' ' && howManyTaken == 0) {
				//it's the first spot, it's module name
				moduleName = collector;
				collector = "";
				howManyTaken += 1;
			}
			else if (temp.at(i) == ' ' && howManyTaken == 1) {
				//it's the second spot, sensor name
				sensorName = collector;
				collector = "";
				howManyTaken += 1;
			}
			else if (temp.at(i) == ' ' && howManyTaken == 2) {
				//it's the last one, must be value
				sensorValue = collector;
				collector = "";
				howManyTaken += 1;
			}
		}

		//call the verifyInput's of each object in the sensorInfo list

		if (humidityModule.getSensorInfo().VerifyInput(sensorName, sensorValue)) {
			//it's valid, modify it
			humidityModule.ChangeValue(sensorName, sensorValue);
		}

		//call change value of correct module if valid, otherwise

		//print message telling user that's an invalid command


	}


	


}



void RumSim() {
	//call each modules getsim and then it's printsim 10 times,
	//each time wait a few seconds(maybe) and then clear the screen
}