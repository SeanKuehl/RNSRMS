#include "simTesting.h"


using namespace std;
simTesting::simTesting(vector<string> passedHead, vector<string> passedBody, vector<string> passedConclusion) {

	Head = passedHead;
	Body = passedBody;
	Conclusion = passedConclusion;

}

void simTesting::PrintSim() {

	for (string i : TempSim::Head)
		cout << i;

	cout << " ";

	for (string i : TempSim::Body)
		cout << i;

	cout << " ";

	for (string i : TempSim::Conclusion)
		cout << i;

	cout << " ";
}