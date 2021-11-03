#include "SensorInfo.h"



SensorInfo::SensorInfo() {

}

bool SensorInfo::VerifyInput(string name, string value) {

	bool nameAndValueFound = false;

	for (int i = 0; i < sensorList.size(); i++) {
		Sensor thisSensor = sensorList.at(i);

		if (thisSensor.getName() == name) {

			for (int k = 0; k < thisSensor.getValues().size(); k++) {
				if (thisSensor.getValues().at(k) == value) {
					nameAndValueFound = true;
				}
			}

		}

	}

	return nameAndValueFound;

}

void SensorInfo::AddSensor(Sensor toAdd) {
	sensorList.push_back(toAdd);
}