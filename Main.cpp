#include <iostream>

#include "HeatFlow.hpp"

using namespace std;

int main() {
	cout << "Starting main. \n";

	map<int, double> sourcesAndSinks;
	sourcesAndSinks[0] = 100.0;

	HeatFlow heatFlow = HeatFlow(10, 5, 0.1, sourcesAndSinks);
	heatFlow.pretty_print();
}