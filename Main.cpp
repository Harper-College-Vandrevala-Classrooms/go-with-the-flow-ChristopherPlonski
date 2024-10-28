#include <iostream>

#include "HeatFlow.hpp"

using namespace std;

void test1() {
	cout << "Test 1 \n";
	map<int, double> sourcesAndSinks;
	sourcesAndSinks[0] = 100.0;

	HeatFlow heatFlow = HeatFlow(10.0, 5, 0.1, sourcesAndSinks, 10.0);
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();
}

void test2() {
	cout << "Test 2 \n";
	map<int, double> sourcesAndSinks;
	sourcesAndSinks[2] = 200.0;

	HeatFlow heatFlow = HeatFlow(20.0, 5, 0.1, sourcesAndSinks, 20.0);
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();
}

void test3() {
	cout << "Test 3 \n";
	map<int, double> sourcesAndSinks;
	sourcesAndSinks[0] = -100;
	sourcesAndSinks[4] = -100;

	HeatFlow heatFlow = HeatFlow(0.0, 5, 0.1, sourcesAndSinks, 0.0);
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();

	heatFlow.tick();
	heatFlow.pretty_print();
}

int main() {
	cout << "--Starting main. \n";

	test1();
	test2();
	test3();

	cout << "--Main finished. \n";
}