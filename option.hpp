//Option.hpp


#ifndef Option_hpp
#define Option_hpp



class Option
{
protected:
	double S;			//Spot price
	double K;			//strike price
	double r;			//risk free interest rate
	double sig;			//volatility
	double b;			//cost of carry

public:
	//Constructors
	Option() : S(60), K(65), r(0.08), sig(0.3), b(0.08)	{	}
	Option(double new_S, double new_K, double new_r, double new_sig) : S(new_S), K(new_K), r(new_r), sig(new_sig), b(new_r)	{	}		//default b=r Black and Scholes stock option model (1973)
	Option(double new_S, double new_K, double new_r, double new_sig, double new_b) : S(new_S), K(new_K), r(new_r), sig(new_sig), b(new_b)	{	}
	Option(const Option& source) : S(source.S), K(source.K), r(source.r), sig(source.sig), b(source.b)	{	}

	//Destructor
	virtual ~Option() {}

	//Operator overloads
	Option& operator = (const Option& source);

	//Getters
	double get_S() { return S; }
	double get_K() { return K; }
	double get_r() { return r; }
	double get_sig() { return sig; }
	double get_b() { return b; }

	//Setters
	void set_S(double new_S) { S = new_S; }
	void set_K(double new_K) { K = new_K; }
	void set_r(double new_r) { r = new_r; }
	void set_sig(double new_sig) { sig = new_sig; }
	void set_b(double new_b) { b = new_b; }

	//Pricers (pure virtual functions)	
	virtual double Price()const = 0;
};


#endif
