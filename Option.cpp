//Option.cpp

#include "Option.hpp"

Option& Option::operator = (const Option& source)
{
	if (this == &source)							//check if current object and argument object are same object
		return *this;

	S = source.S;
	K = source.K;
	r = source.r;
	sig = source.sig;
	b = source.b;
	return *this;
}
