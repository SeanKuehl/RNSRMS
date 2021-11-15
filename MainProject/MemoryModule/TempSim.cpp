#include "TempSim.h"



TempSim::TempSim(vector<string> passedHead, vector<string> passedBody, vector<string> passedConclusion) {

	Head = passedHead;
	Body = passedBody;
	Conclusion = passedConclusion;

}

void TempSim::PrintSim() {

	for (string i : TempSim::Head)
		std::cout << i;

	std::cout << " ";

	for (string i : TempSim::Body)
		std::cout << i;

	std::cout << " ";

	for (string i : TempSim::Conclusion)
		std::cout << i;

	std::cout << " ";
}