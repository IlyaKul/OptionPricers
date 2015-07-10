//PerpAmerOption.cpp

//Perpetual American Option class

#include "GlobalFunctions.hpp"
#include "PerpAmerOption.hpp"
#include <cmath>
#include<vector>

using namespace std;

PerpAmerOption& PerpAmerOption::operator = (const PerpAmerOption& source)
{
	if (this == &source)							//check if current object and argument object are same object
		return *this;

	Option::operator=(source);
	return *this;
}


std::vector<double> PerpAmerOption::Range_of_Prices(double LowerLimit, double UpperLimit, int Num, FunctionPointer Ptr)
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
