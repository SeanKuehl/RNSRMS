
#include "simInfo.h"

using namespace std;

SimInfo::SimInfo() {

	//initialize

}

void SimInfo::PrintSim() {

	for (string i : SimInfo::Head)
		std::cout << i;

	std::cout << " ";

	for (string i : SimInfo::Body)
		std::cout << i;

	std::cout << " ";

	for (string i : SimInfo::Conclusion)
		std::cout << i;

	std::cout << " ";
}