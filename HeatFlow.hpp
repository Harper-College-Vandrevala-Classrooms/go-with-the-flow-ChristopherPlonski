#ifndef HEATFLOW_H
#define HEATFLOW_H

#include <map>
#include <string>

using namespace std;

class HeatFlow {

public:
	HeatFlow(double initialRodTemp, int numberOfRodSections, double K, map<int, double> sourcesAndSinks, double outsideTemperature = 0.0);
	~HeatFlow();
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
	const double OUTSIDE_TEMPERATURE;
	map<int, double> sourcesAndSinks;
	double *rodSectionTempsArray;
	string get_rod_section_temp_as_string(double rodSectionTemp);
	void print_rod_horizontal_border();
	bool is_rod_section_index_a_source_or_sink(int rodSectionIndexToCheck);
	double get_temperature_of_next_rod_section(int currentRodSectionIndex);
	double get_temperature_of_previous_rod_section(int currentRodSectionIndex);
	double get_new_tick_rod_section_temperature(int rodSectionIndex);
};

#endif // !HEATFLOW_H
