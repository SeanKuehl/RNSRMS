
#include "simInfo.h"

using namespace std;

SimInfo::SimInfo(vector<string> NewHead, vector<string> NewBody, vector<string> NewConclusion) {

	SimInfo::Head = NewHead;
	SimInfo::Body = NewBody;
	SimInfo::Conclusion = NewConclusion;

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