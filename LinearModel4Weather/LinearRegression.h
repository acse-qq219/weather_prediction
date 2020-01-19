#pragma once
#include <vector>

using namespace std;

class LinearRegression {
	// A class to fit a linear regression given a set
	// of data using least-squares method 

public:
	LinearRegression(int month);
	~LinearRegression();

	// Accessors
	int getMonth() const;
	double getIntercept() const;
	double getGradient() const;

	// Mutators
	void leastSquaresRegression(vector<double> time, vector<double> temperature);
	double lineExtrapolationTimeSingle(double temperature);
	double lineExtrapolationTempSingle(double time);
	void lineExtrapolationTime(vector<double>& times, vector<double> temperatures);
	void lineExtrapolationTemp(vector<double> times, vector<double>& temperatures);

private:
	int m_;			// Month, if m_ == 0, select whole year
	double c_, g_;		// Interception and gradient
	bool calc_ = false; // Only true when intercept and gradient exist
};
