#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>     
#include <Windows.h>	//for using the function sleep
#include "SensorInfo.h"
#include "simInfo.h"

#include "humidityModule.h"
#include "Temperature_Module.h"
#include "network.h"
#include "Memory.h"

using namespace std;

#define SIM_LENGTH 10

void RumSim();
void MainMenu();
void HandleUserInput();

//instance objects of all modules here
Memory memoryModule = Memory();
Network networkModule = Network();
Humidity humidityModule = Humidity();
Temperature temperatureModule = Temperature();


int main(void) {

	
	
	MainMenu();

}


void MainMenu() {

	string userInput = "";


	while (userInput == "") {
		cout << "Welcome to RNSRMS, enter a command, 'exit' or 'sim'." << endl;

		//call each module's getsim and call it's printsim
		SimInfo humSim = humidityModule.getSim();
		humSim.PrintSim();

		SimInfo tempSim = temperatureModule.getSim();
		tempSim.PrintSim();

		SimInfo netSim = networkModule.getSim();
		netSim.PrintSim();

		SimInfo memSim = memoryModule.getSim();
		memSim.PrintSim();

		

		//call handle user input
		HandleUserInput();


	}

	



}

void HandleUserInput() {

	string temp = "";
	string collector = "";
	string moduleName = "";
	string sensorName = "";
	string sensorValue = "";
	int howManyTaken = 0;

	cout << "Please enter a command: " << endl;
	getline(cin, temp);


	if (temp == "exit") {
		exit(EXIT_SUCCESS);
	}
	else if (temp == "sim") {
		//run sim, remember about clearing the screen and waiting
		RumSim();
	}
	else {
		//its just a regular command
		temp += " ";	//add a space onto the end so it detects value
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
		else if (temperatureModule.getSensorInfo().VerifyInput(sensorName, sensorValue)) {
			temperatureModule.ChangeValue(sensorName, sensorValue);
		}
		else if (networkModule.getSensorInfo().VerifyInput(sensorName, sensorValue)) {
			networkModule.ChangeValue(sensorName, sensorValue);
		}
		else if (memoryModule.getSensorInfo().VerifyInput(sensorName, sensorValue)) {
			memoryModule.ChangeValue(sensorName, sensorValue);
		}
		else {
			cout << "Invalid Command" << endl;
		}

		//call change value of correct module if valid, otherwise

		//print message telling user that's an invalid command


	}


	


}



void RumSim() {
	//call each modules getsim and then it's printsim 10 times,
	//each time wait a few seconds(maybe) and then clear the screen
	
	//clear things on screen before sim
	system("CLS");	//clear the screen, this is windows only code

	for (int i = 0; i < SIM_LENGTH; i++) {
		SimInfo humSim = humidityModule.getSim();
		humSim.PrintSim();

		SimInfo tempSim = temperatureModule.getSim();
		tempSim.PrintSim();

		SimInfo netSim = networkModule.getSim();
		netSim.PrintSim();

		SimInfo memSim = memoryModule.getSim();
		memSim.PrintSim();

		Sleep(2000);
		system("CLS");	//clear the last sim screen

		


	}

	//clear things on screen after sim
	system("CLS");	//clear the screen, this is windows only code

	
}