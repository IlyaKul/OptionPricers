//EuropeanOption.cpp

//Modification date: 6/17/15

#include "EuropeanOption.hpp"
#include "GlobalFunctions.hpp"
#include <cmath>
#include <iostream>
#include <boost/math/distributions/normal.hpp>
using namespace std;



//Operator Overloads
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)
{
	if (this == &source)							//check if current object and argument object are same object
		return *this;

	Option::operator =(source);

	T = source.T;
	
	return *this;
}

EuropeanOption& EuropeanCallOption::operator = (const EuropeanOption& source)
{
	if (this == &source)							//check if current object and argument object are same object
		return *this;

	EuropeanOption::operator=(source);
	return *this;
}

EuropeanOption& EuropeanPutOption::operator = (const EuropeanOption& source)
{
	if (this == &source)							//check if current object and argument object are same object
		return *this;

	EuropeanOption::operator=(source);
	return *this;
}

void EuropeanCallOption::Print() const{
	cout << "Call Option data: T=" << T << ", K=" << K << ", sig=" << sig << ", r=" <<r << ", S=" << S << "\n";
	double C = CallPrice(S, K, T, r, sig, b); double P = PutPrice(S, K, T, r, sig, b);
	cout << "Black Scholes Formulae: C=" << C << ", P=" << P << "\n";
	cout << "Put Call Parity: C=" << CallPricePCP(P, S, K, T, r, b) << ", P=" << PutPricePCP(C, S, K, T, r, b) << "\n";
	cout << "Delta(Call)=" << CallDelta(S, K, T, r, sig, b) << "\n";
	cout << "Gamma=" << GammaGF(S, K, T, r, sig, b) << ", Vega=" << VegaGF(S, K, T, r, sig, b) << "\n";		//Gamma and Vega are the same for call and put option, given the parameters are.
	cout << "Theta(Call)=" << CallTheta(S, K, T, r, sig, b) << "\n";
	cout << "Rho(Call)=" << CallRho(S, K, T, r, sig, b) << endl;

	if (PutCallParity(C, P))						//calling on either type of option, as long as Option Data is the same.
		cout << "Put Call Parity is Satisfied\n";
	else
		cout << "Arbitrage oportunity is detected!!!!\n";

}

void EuropeanPutOption::Print()const {
	cout << "Put Option data: T=" << T << ", K=" << K << ", sig=" << sig << ", r=" << r << ", S=" << S << "\n";
	double C = CallPrice(S, K, T, r, sig, b); double P = PutPrice(S, K, T, r, sig, b);
	cout << "Black Scholes Formulae: C=" << C << ", P=" << P << "\n";
	cout << "Put Call Parity: C=" << CallPricePCP(P, S, K, T, r, b) << ", P=" << PutPricePCP(C, S, K, T, r, b) << "\n";
	cout << "Delta(Put)=" << PutDelta(S, K, T, r, sig, b) << "\n";
	cout << "Gamma=" << GammaGF(S, K, T, r, sig, b) << ", Vega=" << VegaGF(S, K, T, r, sig, b) << "\n";		//Gamma and Vega are the same for call and put option, given the parameters are.
	cout << "Theta(Put)=" << PutTheta(S, K, T, r, sig, b) << "\n";
	cout << "Rho(Put)=" << CallRho(S, K, T, r, sig, b) << endl;

	if (PutCallParity(C, P))						//calling on either type of option, as long as Option Data is the same.
		cout << "Put Call Parity is Satisfied\n";
	else
		cout << "Arbitrage oportunity is detected!!!!\n";

}


//Pricing option functions

std::vector<double> EuropeanCallOption::Price(double LowerLimit, double UpperLimit, int Num, FunctionPointer Ptr)
{
	vector<double> mesh = MeshArray(LowerLimit, UpperLimit, Num);
	
	vector<double> result;
	result.reserve(mesh.size());
	
	for (vector<double>::iterator it = mesh.begin(); it != mesh.end(); ++it)
	{
		result.push_back((this->*Ptr)(*it));		//Calculate result using function pointer. Current value of vector element is taken as an argument.
	}
	return result;
}

std::vector<double> EuropeanPutOption::Price(double LowerLimit, double UpperLimit, int Num, FunctionPointer Ptr)
{
	vector<double> mesh = MeshArray(LowerLimit, UpperLimit, Num);

	vector<double> result;
	result.reserve(mesh.size());

	for (vector<double>::iterator it = mesh.begin(); it != mesh.end(); ++it)
	{
		result.push_back((this->*Ptr)(*it));
	}
	return result;
}

bool EuropeanOption::PutCallParity(double C, double P)const
{
	static const double epsilon = 0.00001;

	if ((C + K*exp(-r*T) - P - S*exp((b - r)*T)) > epsilon)
	{		
		return false;
	}
	else
	{
		return true;
	}
}
