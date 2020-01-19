#include "LinearRegression.h"
#include "Weather.h"

using namespace std;

// Constructor and Destructor 
LinearRegression::LinearRegression(int month) {
	// Month for the linear regression
	assert(month >= 0 and month <= 12);
	m_ = month;
}

LinearRegression::~LinearRegression() {}

// Accessors
int LinearRegression::getMonth() const {
	return m_;
}

double LinearRegression::getIntercept() const {
	if (!calc_) {
		cerr << "Interception must be calculated. Run function leastSquaresRegression()\n";
		return(-1);
	}
	return c_;
}

double LinearRegression::getGradient() const {
	if (!calc_) {
		cerr << "Gradient must be calculated. Run function leastSquaresRegression()\n";
		return(-1);
	}
	return g_;
}

// Mutators
void LinearRegression::leastSquaresRegression(vector<double> time, vector<double> temperature) {
	assert(time.size() == temperature.size());
	int N = time.size();
	double sum_t, sum_tt, sum_T, sum_tT;
	sum_t = sum_tt = sum_T = sum_tT = 0;

	// Compute gradient
	for (int i = 0; i < N; i++) {
		sum_t += time[i];
		sum_tt += time[i] * time[i];
		sum_T += temperature[i];
		sum_tT += time[i] * temperature[i];
	}

	g_ = (N * sum_tT) - (sum_t * sum_T);
	g_ /= (N * sum_tt) - (sum_t * sum_t);

	// Compute intercept
	c_ = (sum_T - g_ * sum_t) / N;

	calc_ = true;
}

double LinearRegression::lineExtrapolationTimeSingle(double temperature) {
	// Predict time at which a specific temperature is likely to happen
	if (!calc_) {
		cerr << "Gradient and interception must be calculated before attempting extrapolation. Run function leastSquaresRegression()" << endl;
		return(-1);
	}
	return ((temperature - c_) / g_);
}

double LinearRegression::lineExtrapolationTempSingle(double time) {
	// Predict temperature at a specific time (year)
	if (!calc_) {
		cerr << "Gradient and interception must be calculated before attempting extrapolation. Run function leastSquaresRegression()" << endl;
		return(-1);
	}
	return (g_ * time + c_);
}

void LinearRegression::lineExtrapolationTime(vector<double>& times, vector<double> temperatures) {
	for (int i = 0; i < temperatures.size(); i++) {
		times.push_back(lineExtrapolationTimeSingle(temperatures[i]));
	}
}

void LinearRegression::lineExtrapolationTemp(vector<double> times, vector<double>& temperatures) {
	for (int i = 0; i < times.size(); i++) {
		temperatures.push_back(lineExtrapolationTempSingle(times[i]));
	}
}