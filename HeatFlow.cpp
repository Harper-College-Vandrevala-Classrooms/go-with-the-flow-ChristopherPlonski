#include "HeatFlow.hpp"

#include <iostream>

HeatFlow::HeatFlow(double initialRodTemp, int numberOfRodSections, double K, map<int, double> sourcesAndSinks, double outsideTemperature)
: INITAL_ROD_TEMP(initialRodTemp), NUMBER_OF_ROD_SECTIONS(numberOfRodSections), K(K), OUTSIDE_TEMPERATURE(outsideTemperature) {
	this->sourcesAndSinks = sourcesAndSinks;
	this->rodSectionTempsArray = new double[NUMBER_OF_ROD_SECTIONS];

	for (int i = 0; i < NUMBER_OF_ROD_SECTIONS; i++) {
		rodSectionTempsArray[i] = INITAL_ROD_TEMP;
	}
	for (pair<int, double> const &sourceOrSink : sourcesAndSinks) {
		int sourceOrSinkRodSectionIndex = sourceOrSink.first;

		if (sourceOrSinkRodSectionIndex < 0 || sourceOrSinkRodSectionIndex >= NUMBER_OF_ROD_SECTIONS) {
			throw("Source/Sink rod section is out of rod bounds.");
			return;
		}

		rodSectionTempsArray[sourceOrSinkRodSectionIndex] = sourceOrSink.second;
	}
}

HeatFlow::~HeatFlow()
{
	delete[] rodSectionTempsArray;
}

void HeatFlow::tick()
{
	double* newRodSectionTempsArray = new double[NUMBER_OF_ROD_SECTIONS];

	for (int i = 0; i < NUMBER_OF_ROD_SECTIONS; i++) {
		if (is_rod_section_index_a_source_or_sink(i)) {
			newRodSectionTempsArray[i] = rodSectionTempsArray[i];
			continue;
		}

		double rodSectionNewTemperature = get_new_tick_rod_section_temperature(i);
		newRodSectionTempsArray[i] = rodSectionNewTemperature;
	}

	delete[] rodSectionTempsArray;
	rodSectionTempsArray = newRodSectionTempsArray;
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

bool HeatFlow::is_rod_section_index_a_source_or_sink(int rodSectionIndexToCheck)
{
	for (pair<int, double> const& sourceOrSink : sourcesAndSinks) {
		int sourceOrSinkRodSectionIndex = sourceOrSink.first;
		
		if (sourceOrSinkRodSectionIndex == rodSectionIndexToCheck) {
			return true;
		}
	}

	return false;
}

double HeatFlow::get_temperature_of_next_rod_section(int currentRodSectionIndex)
{
	const int NEXT_ROD_SECTION_INDEX = currentRodSectionIndex + 1;

	// Prevents trying to check the next rod section if the current rod section is the end of the rod.
	if (NEXT_ROD_SECTION_INDEX == NUMBER_OF_ROD_SECTIONS) {
		return OUTSIDE_TEMPERATURE;
	}

	return rodSectionTempsArray[NEXT_ROD_SECTION_INDEX];
}

double HeatFlow::get_temperature_of_previous_rod_section(int currentRodSectionIndex)
{
	const int PREVIOUS_ROD_SECTION_INDEX = currentRodSectionIndex - 1;

	// Prevents trying to previous the next rod section if the current rod section is the beginning of the rod.
	if (PREVIOUS_ROD_SECTION_INDEX == -1) {
		return OUTSIDE_TEMPERATURE;
	}

	return rodSectionTempsArray[PREVIOUS_ROD_SECTION_INDEX];
}

double HeatFlow::get_new_tick_rod_section_temperature(int rodSectionIndex)
{
	double rodSectionCurrentTemperature = rodSectionTempsArray[rodSectionIndex];
	double nextRodSectionTemperature = get_temperature_of_next_rod_section(rodSectionIndex);
	double previousRodSectionTemperature = get_temperature_of_previous_rod_section(rodSectionIndex);
	double rodSectionNewTemperature = rodSectionCurrentTemperature + K *
		(nextRodSectionTemperature - (2 * rodSectionCurrentTemperature) + previousRodSectionTemperature);

	return rodSectionNewTemperature;
}
