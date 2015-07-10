//PerpAmerOption.hpp

//Perpetual American Option class

#ifndef PerpAmerOption_hpp
#define PerpAmerOption_cpp

#include "Option.hpp"
#include "GlobalFunctions.hpp"
#include <vector>
#include <boost/math/distributions/normal.hpp>


//Perpetual american option class will be derived from Option base class and hold no data members
class PerpAmerOption : public Option
{
public:
	PerpAmerOption() : Option() {}
	PerpAmerOption(double S, double K, double r, double sig, double b) : Option(S, K, r, sig, b) {}
	PerpAmerOption(PerpAmerOption& source) : Option(source) {}

	~PerpAmerOption() {}

	PerpAmerOption& operator = (const PerpAmerOption& source);

	//All the setters and Getters are inherited

	double CallPrice()const { return PerpetualCall(S, K, r, sig, b); }
	double PutPrice()const { return PerpetualPut(S, K, r, sig, b); }
	double CallPrice_S(double S1) const { return PerpetualCall(S1, K, r, sig, b); }
	double PutPrice_S(double S1) const { return PerpetualPut(S1, K, r, sig, b); }

	//Pricing function that returns vector. Used in combination with function pointer for better versatility
	typedef double(PerpAmerOption::*FunctionPointer)(double)const;
	std::vector<double> Range_of_Prices(double LowerLimit, double UpperLimit, int Num, FunctionPointer Ptr);




};



#endif
