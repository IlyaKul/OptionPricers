//GlobalFunctions.cpp

//Modification Date: 6/22/15

#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "GlobalFunctions.hpp"
using namespace std;


double CallPrice(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (S * exp((b - r)*T) * N(d1)) - (K * exp(-r * T)* N(d2));
}

double CallPricePCP(double P, double S, double K, double T, double r, double b) {
	return P + S*exp((b-r)*T) - K*exp(-r*T);
}



double PutPrice(double S, double K, double T, double r, double sig, double b){
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r*T) * N(-d2)) - (S * exp((b - r) * T) * N(-d1));
}

double PutPricePCP(double C, double S, double K, double T, double r, double b) {
	return C - S*exp((b - r)*T) + K*exp(-r*T);
}


std::vector<double> MeshArray(double LowerLimit, double UpperLimit, int Num)			//N - amount of steps
{
	vector<double> mesh;
	mesh.reserve(Num+1);
	double h = (UpperLimit - LowerLimit) / Num;
	
	for (double x = LowerLimit; x <= UpperLimit; x += h)
	{
		mesh.push_back(x); 		
	}
	return mesh;
}

void PrintVector (const vector<double>& V)
{
	for (vector<double>::const_iterator it = V.begin(); it != V.end(); ++it)
		cout << *it << ", ";
}

double N(double x) {
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return boost::math::cdf(myNormal, x);
}

double n(double x) {
	boost::math::normal_distribution<> myNormal(0.0, 1.0);
	return boost::math::pdf(myNormal, x);
}

double CallDelta(double S, double K, double T, double r, double sig, double b)
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;

	return exp((b - r)*T) * N(d1);
}

double PutDelta(double S, double K, double T, double r, double sig, double b)
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;

	return exp((b - r)*T) * (N(d1) - 1.0);
}

double GammaGF(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;

	return n(d1)*exp((b - r)*T) / (S*tmp);
}

double VegaGF(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;

	return S*sqrt(T)*exp((b - r)*T)*n(d1);
}

double CallTheta(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return -S*sig*exp((b - r)*T)*n(d1) / (2 * sqrt(T)) - (b - r)*S*exp((b - r)*T)*N(d1) - r*K*exp(-r*T)*N(d2);
}

double PutTheta(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return -S*sig*exp((b - r)*T)*n(d1) / (2 * sqrt(T)) - (b - r)*S*exp((b - r)*T)*N(-d1) + r*K*exp(-r*T)*N(-d2);
}

double CallRho(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return 0.01*K*T*exp(- r*T)*N(d2);
}

double PutRho(double S, double K, double T, double r, double sig, double b) {
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (b + (sig*sig)*0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return -0.01*K*T*exp(- r*T)*N(-d2);
}

double CallDelta(double S, double h, double K, double T, double r, double sig, double b) {		//Delta Aproximation  using divided difference
	return (CallPrice(S + h, K, T, r, sig, b) - CallPrice(S - h, K, T, r, sig, b)) / (2 * h);
}

double PutDelta(double S, double h, double K, double T, double r, double sig, double b) {		//Delta Aproximation  using divided difference
	return (PutPrice(S + h, K, T, r, sig, b) - PutPrice(S - h, K, T, r, sig, b)) / (2 * h);
}

double GammaGF(double S, double h, double K, double T, double r, double sig, double b) {		//Gamma Aproximation  using divided difference
	return (CallPrice(S + h, K, T, r, sig, b) - 2 * CallPrice(S, K, T, r, sig, b) + CallPrice(S - h, K, T, r, sig, b)) / (h * h);
}


double PerpetualCall(double S, double K, double r, double sig, double b)
{ // Dividend q = r - b

	double sig2 = sig*sig;								//sig to the second power defined for convenience
	double fac = b / sig2 - 0.5; fac *= fac;			//fac to the second power defined for convenience
	double y1 = 0.5 - b / sig2 + sqrt(fac + 2.0*r / sig2);


	if (1.0 == y1)								//no need to calculate the function if y1 equals to 1,
		return S;

	double fac2 = ((y1 - 1.0)*S) / (y1 * K);
	double c = K * pow(fac2, y1) / (y1 - 1.0);

	return c;
}

double PerpetualPut(double S, double K, double r, double sig, double b)
{
	double sig2 = sig*sig;
	double fac = b / sig2 - 0.5; fac *= fac;
	double y2 = 0.5 - b / sig2 - sqrt(fac + 2.0*r / sig2);

	if (0.0 == y2)
		return S;

	double fac2 = ((y2 - 1.0)*S) / (y2 * K);
	double p = K * pow(fac2, y2) / (1.0 - y2);

	return p;
}
