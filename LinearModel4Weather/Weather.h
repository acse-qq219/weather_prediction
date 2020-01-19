#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

void readDataFile(string filename, vector<string>& months,
	vector<double>& temps, int start_year, int end_year);

void saveCsv(vector<string> xdata, vector<double> ydata, string outAddress,
	string headerX, string headerY);

string numberToMonth(int m);

// Data parsing
double dateStringToFloatSingle(string& date);

vector<double> dateStringToFloat(vector<string>);

bool isInputValid(string input);
