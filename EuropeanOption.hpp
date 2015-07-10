//EuropeanOption.hpp
//
//Modification date: 6/17/15

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include "Option.hpp"
#include "GlobalFunctions.hpp"
#include <boost/math/distributions/normal.hpp>
#include <vector>


class EuropeanOption : public Option
{
protected:
	double T;			//time till maturity
	
public:
	//Constructors
	EuropeanOption() : Option(), T(0.25)	{	}
	EuropeanOption(double new_S, double new_K, double new_T, double new_r, double new_sig) : Option(new_S,new_K,new_r,new_sig), T(new_T)	{	}		//default b=r Black and Scholes stock option model (1973)
	EuropeanOption(double new_S, double new_K, double new_T, double new_r, double new_sig, double new_b) : Option(new_S, new_K, new_r, new_sig, new_b), T(new_T)	{	}
	EuropeanOption(const EuropeanOption& source) : Option(source), T(source.T)	{	}

	//Destructor
	virtual ~EuropeanOption() {}

	//Operator overloads
	EuropeanOption& operator = (const EuropeanOption& source);

	//Getters
	double get_T() { return T; }
	
	virtual void Print()const = 0;

	//Setters	
	void set_T(double new_T) { T = new_T; }
	
	//Pricers (pure virtual functions)	
	virtual double Price()const = 0;
	virtual double PricePCP(double PC)const = 0;
	virtual double Price_S(double S1) = 0;
	virtual double Price_K(double K1) = 0;
	virtual double Price_T(double T1) = 0;
	virtual double Price_r(double r1) = 0;
	virtual double Price_sig(double sig1) = 0;
	virtual double Price_b(double b1) = 0;

	//Checkers
	bool PutCallParity(double C, double P)const;

	//Greeks
	virtual double Delta() const = 0;
	double Gamma() { return GammaGF(S, K, T, r, sig, b); }		//Gamma is the same for put and call options
	double Gamma(double h) { return GammaGF(S, h, K, T, r, sig, b); }
	double Vega() { return VegaGF(S, K, T, r, sig, b); }		//Vega is the same for put and call options, no need to define it in derived classes
	virtual double Theta() const = 0;
	virtual double Rho() const = 0;


		
};

class EuropeanCallOption : public EuropeanOption
{
public:
	//Constructors
	EuropeanCallOption() : EuropeanOption() {}
	EuropeanCallOption(double new_S, double new_K, double new_T, double new_r, double new_sig) : EuropeanOption(new_S, new_K, new_T, new_r, new_sig) {}
	EuropeanCallOption(double new_S, double new_K, double new_T, double new_r, double new_sig, double new_b) : EuropeanOption(new_S, new_K, new_T, new_r, new_sig, new_b) {}
	EuropeanCallOption(const EuropeanOption& source) : EuropeanOption(source) {}

	//Destructor
	virtual ~EuropeanCallOption() {}

	EuropeanOption& operator = (const EuropeanOption& source);

	void Print()const;

	//Pricers
	double Price()const	{	return CallPrice(S, K, T, r, sig, b);	}
	double Price_S(double S1)	{ return CallPrice(S1, K, T, r, sig, b); }
	double Price_K(double K1)	{ return CallPrice(S, K1, T, r, sig, b); }
	double Price_T(double T1)	{ return CallPrice(S, K, T1, r, sig, b); }
	double Price_r(double r1)	{ return CallPrice(S, K, T, r1, sig, b); }
	double Price_sig(double sig1)	{ return CallPrice(S, K, T, r, sig1, b); }
	double Price_b(double b1)	{ return CallPrice(S, K, T, r, sig, b1); }
	double PricePCP(double P)const	{ return CallPricePCP(P, S, K, T, r, b); }
	
	//Pricing function that returns vector. Used in combination with function pointer for better versatility
	typedef double(EuropeanCallOption::*FunctionPointer)(double);
	std::vector<double> Price(double LowerLimit, double UpperLimit, int Num, FunctionPointer Ptr );
	
	//Greeks
	double Delta()const { return CallDelta( S, K, T, r, sig, b); }
	double Delta_S(double S1) { return CallDelta(S1, K, T, r, sig, b); }		//function to override spot price
	double Theta() const { return CallTheta(S, K, T, r, sig, b); }
	double Rho() const { return CallRho(S, K, T, r, sig, b); }
	double Delta(double h)const { return CallDelta(S, h, K, T, r, sig, b); }
	//double Gamma() { return GammaGF(S, K, T, r, sig, b); }
	//double Gamma(double h) { return GammaGF(S, h, K, T, r, sig, b); }

};

class EuropeanPutOption : public EuropeanOption
{
public:
	//Constructors
	EuropeanPutOption() : EuropeanOption() {}
	EuropeanPutOption(double new_S, double new_K, double new_T, double new_r, double new_sig) : EuropeanOption(new_S, new_K, new_T, new_r, new_sig) {}
	EuropeanPutOption(double new_S, double new_K, double new_T, double new_r, double new_sig, double new_b) : EuropeanOption(new_S, new_K, new_T, new_r, new_sig, new_b) {}
	EuropeanPutOption(const EuropeanOption& source) : EuropeanOption(source) {}

	//Destructor
	virtual ~EuropeanPutOption() {}

	EuropeanOption& operator = (const EuropeanOption& source);

	void Print()const;

	//Pricers
	double Price()const		{	return PutPrice(S, K, T, r, sig, b);	}
	double PricePCP(double C)const		{	return PutPricePCP(C, S, K, T, r, b);	}
	double Price_S(double S1)	{ return PutPrice(S1, K, T, r, sig, b); }
	double Price_K(double K1)	{ return PutPrice(S, K1, T, r, sig, b); }
	double Price_T(double T1)	{ return PutPrice(S, K, T1, r, sig, b); }
	double Price_r(double r1)	{ return PutPrice(S, K, T, r1, sig, b); }
	double Price_sig(double sig1)	{ return PutPrice(S, K, T, r, sig1, b); }
	double Price_b(double b1)	{ return PutPrice(S, K, T, r, sig, b1); }

	//Pricing function that returns vector. Used in combination with function pointer for better versatility
	typedef double(EuropeanPutOption::*FunctionPointer)(double);
	std::vector<double> Price(double LowerLimit, double UpperLimit, int Num,const FunctionPointer Ptr);

	//Greeks
	double Delta()const { return PutDelta(S, K, T, r, sig, b); }
	double Delta_S(double S1) { return PutDelta(S1, K, T, r, sig, b); }																		//function to override spot price
	double Theta() const { return PutTheta(S, K, T, r, sig, b); }
	double Rho() const { return PutRho(S, K, T, r, sig, b); }
	double Delta(double h)const { return PutDelta(S, h, K, T, r, sig, b); }
	

};


#endif
