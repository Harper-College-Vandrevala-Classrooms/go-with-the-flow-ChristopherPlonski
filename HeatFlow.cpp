#include "HeatFlow.hpp"

#include <iostream>

HeatFlow::HeatFlow(double initialRodTemp, int numberOfRodSections, double K, map<int, double> sourcesAndSinks)
: INITAL_ROD_TEMP(initialRodTemp), NUMBER_OF_ROD_SECTIONS(numberOfRodSections), K(K) {
	this->sourcesAndSinks = sourcesAndSinks;
	this->rodSectionTempsArray = new double[NUMBER_OF_ROD_SECTIONS];

	for (int i = 0; i < NUMBER_OF_ROD_SECTIONS; i++) {
		rodSectionTempsArray[i] = INITAL_ROD_TEMP;
	}
	for (pair<int, double> const &sourceOrSink : sourcesAndSinks) {
		int sourceOrSinkyRodSectionIndex = sourceOrSink.first;

		if (sourceOrSinkyRodSectionIndex < 0 || sourceOrSinkyRodSectionIndex >= NUMBER_OF_ROD_SECTIONS) {
			throw("Source/Sink rod section is out of rod bounds.");
			return;
		}

		rodSectionTempsArray[sourceOrSinkyRodSectionIndex] = sourceOrSink.second;
	}
}

void HeatFlow::tick()
{

}

void HeatFlow::pretty_print()
{
	print_rod_horizontal_border();

	for (int i = 0; i < NUMBER_OF_ROD_SECTIONS; i++) {
		double sectionTemperature = rodSectionTempsArray[i];
		string sectionTemperatureAsString = get_rod_section_temp_as_string(sectionTemperature);
		cout << VERTICAL_SEPERATOR << SPACE << sectionTemperatureAsString << SPACE;
	}
	cout << VERTICAL_SEPERATOR << endl;

	print_rod_horizontal_border();
}

void HeatFlow::print_rod_horizontal_border()
{
	for (int i = 0; i < NUMBER_OF_ROD_SECTIONS; i++) {
		double sectionTemperature = rodSectionTempsArray[i];
		string sectionTemperatureAsString = get_rod_section_temp_as_string(sectionTemperature);
		cout << CORNER_SYMBOL << HORIZONTAL_SEPERATOR;
		for (int j = 0; j < sectionTemperatureAsString.size(); j++) {
			cout << HORIZONTAL_SEPERATOR;
		}
		cout << HORIZONTAL_SEPERATOR;
	}

	cout << CORNER_SYMBOL << endl;
}

string HeatFlow::get_rod_section_temp_as_string(double rodSectionTemp)
{
	string rodSectionTempString = to_string(rodSectionTemp);

	size_t periodIndexFound = rodSectionTempString.find('.');

	if (periodIndexFound != string::npos) {
		// This double has a period
		//cout << "has period.";
		rodSectionTempString = rodSectionTempString.substr(0, periodIndexFound + 2);
	}

	return rodSectionTempString;
}
