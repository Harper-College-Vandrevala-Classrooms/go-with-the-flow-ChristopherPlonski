#include <iostream>

#include "HeatFlow.hpp"

using namespace std;

int main() {
	cout << "Starting main. \n";

	map<int, double> sourcesAndSinks;
	sourcesAndSinks[0] = 100.0;

	HeatFlow heatFlow = HeatFlow(10.0, 5, 0.1, sourcesAndSinks, 10.0);
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();

	cout << "Main finished. \n";
}