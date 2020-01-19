#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Interface {

public:
	Interface();
	~Interface();

private:
	vector<int> m_all_;
	int start_year_, end_year_;

	// Interface (terminal prompt) functions
	void interfaceIntro();
	void interfaceSelectData();
	void interfaceSelectRange();
	void interfaceInvalid(string message);
	void interfaceSelectMonth();
	void interfaceSelectOutput();

	// Analyse data
	void mainTemp();
	void filterByMonth(vector<string>& months, vector<double>& temps,
		vector<string>& filt_months, vector<double>& filt_temps, int m);
	void lineFit(vector<double> times_extrapolate);
	void findTemperature();
	void findTime();
	
	// Plotting
	void plotData();
	void plotDataLinearFit();
	void plotDataLinearExtrap();
};