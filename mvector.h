#ifndef MVECTOR_H // the 'include guard'
#define MVECTOR_H // see C++ Primer Sec. 2.9.2

#include <iostream>
#include <vector>

// Class that represents a mathematical vector
class MVector
{
public:
	// constructors
	MVector() {}
	explicit MVector(int n) : v(n) {}
	MVector(int n, double x) : v(n, x) {}

	// access element (lvalue)
	double &operator[](int index) { return v[index]; }

	// access element (rvalue)
	double operator[](int index) const { return v[index]; }

	int size() const { return v.size(); } // number of elements

private:
	std::vector<double> v;
};

// Operator overload for "scalar * vector"
inline MVector operator*(const double& lhs, const MVector& rhs)
{
	MVector temp = rhs;
	for (int i = 0; i<temp.size(); i++) temp[i] *= lhs;
	return temp;
}

// Operator overload for "vector * scalar"
inline MVector operator*(const MVector& lhs, const double& rhs)
{
	MVector temp = lhs;
	for (int i = 0; i<temp.size(); i++) temp[i] *= rhs;
	return temp;
}

// Operator overload for "vector / scalar"
inline MVector operator/(const MVector& lhs, const double& rhs)
{
	if (rhs != 0)
	{
		MVector temp = lhs;
		for (int i = 0; i<temp.size(); i++) temp[i] /= rhs;
		return temp;
	}
	else
	{
		std::cout << "Error: cannot divide a vector by 0." << std::endl;
		exit(1);
	}
}

// Operator overload for "vector + vector"
inline MVector operator+(const MVector& lhs, const MVector& rhs)
{
	if (lhs.size() != rhs.size())
	{
		std::cout << "Error: vectors must be of the same length for vector addition." << std::endl;
		exit(1);
	}
	else
	{
		MVector temp = rhs;
		for (int i = 0; i<temp.size(); i++) temp[i] += lhs[i];
		return temp;
	}
}

// Operator overload for "vector - vector"
inline MVector operator-(const MVector& lhs, const MVector& rhs)
{
	if (lhs.size() != rhs.size())
	{
		std::cout << "Error: vectors must be of the same length for vector subraction." << std::endl;
		exit(1);
	}
	else
	{
		MVector temp = lhs;
		for (int i = 0; i<temp.size(); i++) temp[i] -= rhs[i];
		return temp;
	}
}

// Overload the << operator to output MVectors to screen or file
std::ostream& operator<<(std::ostream& os, const MVector& v)
{
	int n = v.size();
	os << "(";
	for (int i = 0; i < v.size() - 1; i++) os << v[i] << ", ";
	os << v[v.size() - 1];
	os << ")";
	return os;
}

struct MFunction
{
	virtual MVector operator()(const double& x, const MVector& y) = 0;
};

class FunctionF1 : public MFunction
{
public:
	MVector operator()(const double& x, const MVector& y)
	{
		MVector temp(2);
		temp[0] = y[0] + x*y[1];
		temp[1] = x*y[0] - y[1];
		return temp;
	}
};

class FunctionF2 : public MFunction
{
public:
	MVector operator()(const double& x, const MVector& y)
	{
		MVector temp(2);
		temp[0] = x;
		temp[1] = y[1];
		return temp;
	}
};

class Eqn1p32DerivsIVP : public MFunction
{
public:
	MVector operator()(const double& x, const MVector& y)
	{
		MVector temp(2);
		temp[0] = y[1];
		temp[1] = ((1/8)*(32+2*x*x*x - y[0]*y[1]));
		return temp;
	}
};

class Eqn1p5Derivs : public MFunction
{
public:
	// constructor to initialise kappa
	Eqn1p5Derivs() { kappa = 1.0; }
	MVector operator()(const double& x, const MVector& y)
	{
		MVector temp(4);
		temp[0] = y[1];
		temp[1] = -kappa*y[1] - x*y[0];
		temp[2] = y[3];
		temp[3] = -kappa*y[3] - x*y[2];
		return temp;
	}
	void SetKappa(double k) { kappa = k; } // change kappa
private:
	double kappa; // class member variable, accessible within
				  // all Eqn1p5Derivs member functions
};

class Eqn1p32Derivs : public MFunction
{
public:
	MVector operator()(const double& x, const MVector& y)
	{	// temp is the derivatives of the input y[], (F)
		// y[0] = y = Y1, y[1] = dy/dx = Y2
		// y[2] = dy/dg = Z1, y[3] = dZ1/dx = Z2
		MVector temp(4);
		temp[0] = y[1];
		temp[1] = 0.125*(32 + 2*x*x*x - y[0]*y[1]);
		temp[2] = y[3];
		temp[3] = -0.125*(y[1]*y[2] + y[0]*y[3]);
		return temp;
	}
};


#endif