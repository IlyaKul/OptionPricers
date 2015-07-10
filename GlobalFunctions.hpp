//GlobalFunctions.hpp

//modification date: 6/23/15

#ifndef GlobalFunctions_hpp
#define GlobalFunctions_hpp


#include <vector>
using namespace std;

double N(double x);
double n(double x);

double CallPrice(double S, double K, double T, double r, double sig, double b);
double CallPricePCP(double P, double S, double K, double T, double r, double b);
double CallDelta(double S, double K, double T, double r, double sig, double b);
double GammaGF(double S, double K, double T, double r, double sig, double b);
double VegaGF(double S, double K, double T, double r, double sig, double b);
double CallTheta(double S, double K, double T, double r, double sig, double b);
double CallRho(double S, double K, double T, double r, double sig, double b);


double PutPrice(double S, double K, double T, double r, double sig, double b);
double PutPricePCP(double C, double S, double K, double T, double r, double b);
double PutDelta(double S, double K, double T, double r, double sig, double b);
double PutTheta(double S, double K, double T, double r, double sig, double b);
double PutRho(double S, double K, double T, double r, double sig, double b);


double CallDelta(double S, double h, double K, double T, double r, double sig, double b);		//Delta Aproximation  using divided difference
double PutDelta(double S, double h, double K, double T, double r, double sig, double b);	//Delta Aproximation  using divided difference
double GammaGF(double S, double h, double K, double T, double r, double sig, double b);		//Gamma Aproximation  using divided difference


double PerpetualCall(double K, double S, double sig, double r, double b);
double PerpetualPut(double K, double S, double sig, double r, double b);


std::vector<double> MeshArray(double LowerLimit, double UpperLimit, int Num);

void PrintVector(const std::vector<double>& V);




#endif
