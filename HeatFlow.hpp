#ifndef HEATFLOW_H
#define HEATFLOW_H

#include <map>
#include <string>

using namespace std;

class HeatFlow {

public:
	HeatFlow(double initialRodTemp, int numberOfRodSections, double K, map<int, double> sourcesAndSinks);
	void tick();
	void pretty_print();

private:
	static const char HORIZONTAL_SEPERATOR = '-';
	static const char VERTICAL_SEPERATOR = '|';
	static const char CORNER_SYMBOL = '+';
	static const char SPACE = ' ';
	const double INITAL_ROD_TEMP;
	const int NUMBER_OF_ROD_SECTIONS;
	const double K;
	map<int, double> sourcesAndSinks;
	double *rodSectionTempsArray;
	string get_rod_section_temp_as_string(double rodSectionTemp);
	void print_rod_horizontal_border();
};

#endif // !HEATFLOW_H
