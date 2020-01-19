#include "Interface.h"
#include "LinearRegression.h"
#include "Weather.h"

using namespace std;

Interface::Interface() {
	interfaceIntro();

	// m_all_ empty when initialising
	// It will hold all months for data analysis
	m_all_ = {};
}

Interface::~Interface() {}

void Interface::filterByMonth(vector<string>& months, vector<double>& temps,
	vector<string>& filt_months, vector<double>& filt_temps, int m) {
	// From (vector<string>) months of format "YYYY-MM" and respective temperature
	// values in (vector<double>) temps, filters data for all years of a given month
	// (m = 1 for JAN, m = 2 for FEB, etc.); Filtered values are added to 
	// (vector<string>) filt_months and (vector<double>) filt_temps.

	assert(m > 0 && m <= 12);
	assert(months.size() == temps.size());

	string search;
	if (m < 10) {
		search = "0" + to_string(m);
	} 
	else {
		search = to_string(m);
	}

	for (int i = 0; i < months.size(); i++) {
		if (search == months[i].substr(5, 2)) {
			filt_months.push_back(months[i]);
			filt_temps.push_back(temps[i]);
		}
	}
}

void Interface::interfaceIntro() {
	system("CLS");
	cout << endl << "-------------------------------" << endl;
	cout << " SINGAPORE TEMPERATURE PREDICTOR" << endl;
	cout << "-------------------------------" << endl << endl;

	cout << "-------------------------------" << endl;
	cout << " This software is designed to make preliminary predictions" 
		 << endl << "of the surface temperature variation in Singapore" << endl;
	cout << "-------------------------------" << endl << endl;

	cout << " Data used: " << endl;
	cout << "-------------------------------" << endl << endl;
	cout << " Average Surface Temperature of Singapore:" << endl;
	cout << " Changi Climate Station, Singapore, 1982 - 2018" << endl;
	cout << " World Bank Data, 1901 - 2018" << endl << endl;
	cout << " Population of Singapore:" << endl;
	cout << " World Bank Data, 1960 - 2017 " << endl << endl;
	cout << "------------------------------" << endl;

	cout << "Would you like to continue? (y/n)" << endl;
	cout << " >> ";
	char select;
	cin >> select;
	switch (select) 
	{
	case 'y': break;
	case 'n': exit(0);
	default: interfaceIntro();
	}

	interfaceSelectData();
}

void Interface::interfaceSelectData() {
	system("CLS");
	cin.clear();
	cout << endl << " Select Data:" << endl << endl;
	cout << " 1: Surface Temperature" << endl
		<< " b: Back" << endl
		<< " x: Exit" << endl << endl;
	cout << " >> ";
	string select;
	cin >> select;

	// String to char
	char* select_char = new char[1];
	if (select.size() != 1) *select_char = '#';
	else copy(select.begin(), select.end(), select_char);

	switch (*select_char) 
	{
	case '1': interfaceSelectRange(); break;
	case 'b': system("CLS"); cin.ignore(); interfaceIntro(); break;
	case 'x': exit(0);
	default: interfaceInvalid(""); interfaceSelectData();
	}
	delete[] select_char;
}

void Interface::interfaceInvalid(string message) {
	// ignore current line in cin stream up to '\n'
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	system("CLS");
	cout << endl << " Invalid Selection" << endl << endl;
	cout << "------------------------------" << endl;
	cout << message << endl << endl;
	cout << " Press enter to return..." << endl;
	cin.get(); // Only receive one character.
}

void Interface::interfaceSelectRange() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << " Insert date range to be analysed (1901-2018): " << endl << endl;
	cout << " Example: \n >> 1995 2006" << endl;

	cout << endl << " >> ";
	cin >> start_year_ >> end_year_;

	if (cin.fail()) {
		interfaceInvalid(" Please enter only integer characters");
		interfaceSelectData();
	}
	if (start_year_ < 1901 || start_year_ > 2017 || end_year_ < 1902 || end_year_ > 2018) {
		interfaceInvalid(" Date out of range, please select a date between 1901 - 2018");
		interfaceSelectData();
	}
	if (start_year_ >= end_year_) {
		interfaceInvalid(" Start year must be greater than end year");
		interfaceSelectData();
	}

	interfaceSelectMonth();
}

void Interface::interfaceSelectMonth() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	system("CLS");
	cout << endl << "Analysing data from " << start_year_ << "-" << end_year_ << endl;
	cout << " Select Month for Analysis:" << endl << endl;
	cout << " 0: All months" << endl
		<< " 1: January \t 2: February" << endl
		<< " 3: March \t 4: April" << endl
		<< " 5: May \t 6: June" << endl
		<< " 7: July \t 8: August" << endl
		<< " 9: September \t 10: October" << endl
		<< " 11: November \t 12: December" << endl
		<< " b: Back" << endl
		<< " x: Exit" << endl << endl;

	bool cont = true;
	int m;

	while (cont) {
		cout << " >> ";
		string select;
		cin >> select;

		// String to char
		char* select_char = new char[2];
		if (select.size() > 2) *select_char = '#';
		else copy(select.begin(), select.end(), select_char);

		switch (*select_char)
		{
		case '0': m = 0; break;
		case '1': m = 1; break;
		case '2': m = 2; break;
		case '3': m = 3; break;
		case '4': m = 4; break;
		case '5': m = 5; break;
		case '6': m = 6; break;
		case '7': m = 7; break;
		case '8': m = 8; break;
		case '9': m = 9; break;
		case '10': m = 10; break;
		case '11': m = 11; break;
		case '12': m = 12; break;
		case 'x': exit(0);
		case 'b': system("CLS"); interfaceSelectData(); break;
		default: interfaceInvalid(""); interfaceSelectMonth();
		}
		delete[] select_char;

		m_all_.push_back(m);
		// sort and remove duplicated value
		sort(m_all_.begin(), m_all_.end());
		m_all_.erase(unique(m_all_.begin(), m_all_.end()), m_all_.end());
		
		cout << endl;
		// equal to (python) for int mm in m_all_:
		for (int mm : m_all_) {
			cout << " " << numberToMonth(mm) << " ";
		}
		cout << " selected. " << endl << endl;

		// clear all stuff in cin stream.
		cin.clear();
		cin.ignore();

		char select2;
		cout << "Would you like to select another month? (y/n) >> ";
		cin >> select2;
		switch (select2)
		{
		case 'y': cont = true; break;
		case 'n': cont = false; break;
		default: interfaceInvalid(""); interfaceSelectMonth();
		}
	}
	mainTemp();
}

void Interface::mainTemp() {
	// Function to read average temperature data, filter it
	// by date and save filtered data as a CSV file.

	// Create vectors to store data, for all months and single month.
	vector<string> months;
	vector<double> temps;

	// Read file and store data in vectors
	string filename = "./data/surface-air-temperature-monthly-mean/surface-air-temperature-monthly-mean.csv";
	readDataFile(filename, months, temps, start_year_, end_year_);

	// Filter by month and output monthly data to CSV file;
	// If m = 0, store whole dataset.
	vector<string> filt_months;
	vector<double> filt_temps;

	for (int mm : m_all_) {
		filt_months.clear();
		filt_temps.clear();

		if (mm != 0) {
			filterByMonth(months, temps, filt_months, filt_temps, mm);
		}
		else {
			for (int i = 0; i < months.size(); i++) {
				filt_months.push_back(to_string(dateStringToFloatSingle(months[i])));
				filt_temps.push_back(temps[i]);
			}
		}
		string outaddress = "./data/processed_data/avg_temp_data_" + to_string(mm) + ".csv";
		saveCsv(filt_months, filt_temps, outaddress, "year", "temperature(c)");
	}
	interfaceSelectOutput();
}

void Interface::interfaceSelectOutput() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	system("CLS");
	cout << endl << "Analysing ";
	for (int mm : m_all_) {
		cout << numberToMonth(mm) << " ";
	}
	cout << "Data from " << start_year_ << "-" << end_year_ << endl << endl;

	cout << " Select output:" << endl << endl
		<< " 1: Find temperature for specific time" << endl
		<< " 2: Find time for specific temperature" << endl
		<< " b: Back" << endl
		<< " x: Exit" << endl << endl;
	cout << " >> ";
	string select;
	cin >> select;

	char* select_char = new char[1];
	if (select.size() != 1) *select_char = '#';
	else copy(select.begin(), select.end(), select_char);

	switch (*select_char)
	{
	case '1': findTemperature(); break;
	case '2': findTime(); break;
	case 'b': m_all_.clear(); interfaceSelectMonth(); break;
	case 'x': exit(0);
	default: interfaceInvalid(""); interfaceSelectOutput();
	}
	delete[] select_char;
}

void Interface::findTemperature() {
	// Find a temperature value for a user-specified year using
	// extrapolated line regression year given in decimals and 
	// temperature in degrees celcius

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << " Insert year" << endl << endl;
	cout << " Example: \n >> 2056" << endl;
	double extrapolation_year;
	cout << endl << " >> ";
	cin >> extrapolation_year;

	if (cin.fail()) {
		interfaceInvalid(" Please enter only integer or float characters");
		interfaceSelectOutput();
	}

	vector<double> month_temps, years;
	vector<string> year_string;
	// A vector includes (class) LinearRegression objects
	// vector<LinearRegression> lines;

	for (int mm : m_all_) {
		month_temps.clear();
		year_string.clear();
		years.clear();

		// Read monthly data
		string inaddress = "./data/processed_data/avg_temp_data_" + to_string(mm) + ".csv";
		readDataFile(inaddress, year_string, month_temps, start_year_, end_year_);

		// Transform time data to years
		years = dateStringToFloat(year_string);

		// Create linear regression object and initialise it
		LinearRegression Regression(mm);
		Regression.leastSquaresRegression(years, month_temps);

		// Extrapolate at chosen times
		cout << endl << numberToMonth(mm) + " " << extrapolation_year
			<< " : " << Regression.lineExtrapolationTempSingle(extrapolation_year)
			<< " C " << endl;
	}
	cout << endl;
	system("pause");
	interfaceSelectOutput();
}

void Interface::findTime() {
	// Find the year for a user-specified temperature value using
	// extrapolated linear regression year given in decimals and 
	// temperature in degree celcius

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl << " Insert temperature (C)" << endl << endl;
	cout << " Example: \n >> 29.45" << endl;
	double temperature_find;
	cout << endl << " >> ";
	cin >> temperature_find;

	if (cin.fail()) {
		interfaceInvalid(" Please enter only integer or float characters");
		interfaceSelectOutput();
	}

	vector<double> month_temps, years;
	vector<string> year_string;
	// vector<LinearRegression> lines;

	for (int mm : m_all_) {
		month_temps.clear();
		year_string.clear();
		years.clear();

		// Read monthly data
		string inaddress = "./data/processed_data/avg_temp_data_" + to_string(mm) + ".csv";
		readDataFile(inaddress, year_string, month_temps, start_year_, end_year_);

		// Transform time data to years
		years = dateStringToFloat(year_string);

		// Create linear regression object and initialise it
		LinearRegression Regression(mm);
		Regression.leastSquaresRegression(years, month_temps);

		// Extrapolate at chosen times
		cout << endl << numberToMonth(mm) + " " << temperature_find << " C : "
			<< Regression.lineExtrapolationTimeSingle(temperature_find) << endl;
	}
	cout << endl;
	system("pause");
	interfaceSelectOutput();
}