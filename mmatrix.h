#ifndef MMATRIX_H
#define MMATRIX_H

#include <vector>
#include <iostream>
#include "mvector.h"

// All indexes start from zero, unlike standard matrix notation

// Class that represents a mathematical matrix
class MMatrix
{
public:
	// constructors
	// The vector A is the rows of the matrix written out one after another
	MMatrix() : nRows(0), nCols(0) {}
	MMatrix(int n, int m, double x = 0) : nRows(n), nCols(m), A(n * m, x) {}

	// set all matrix entries equal to a double
	MMatrix &operator=(double x)
	{
		for (int i = 0; i < nRows * nCols; i++) A[i] = x;
		return *this;
	}

	// access element, indexed by (row, column) [rvalue]
	double operator()(int i, int j) const
	{ // nCols is the length of each row of the matrix
		// i*nCols 
		return A[j + i * nCols];
	}

	// access element, indexed by (row, column) [lvalue]
	double &operator()(int i, int j)
	{
		return A[j + i * nCols];
	}

	// size of matrix
	int Rows() const { return nRows; }
	int Cols() const { return nCols; }

private:
	unsigned int nRows, nCols;
	std::vector<double> A;
};

// Overload the << operator to output MMatrix to screen or file
std::ostream& operator<<(std::ostream& os, const MMatrix& rhs)
{
	for (int i = 0; i < rhs.Rows(); i++)
	{
		for (int j = 0; j < rhs.Cols(); j++)
		{
			os << rhs(i, j) << ", ";
		}
		os << "\n";
	}

	return os;
}

// Operator overload for "scalar * matrix"
inline MMatrix operator*(const double& lhs, const MMatrix& rhs)
{
	MMatrix temp = rhs;
	for (int i = 0; i < rhs.Rows(); i++)
	{
		for (int j = 0; j < rhs.Cols(); j++)
		{
			temp(i, j) *= lhs;
		}
	}

	return temp;
}

// Operator overload for "matrix * scalar"
inline MMatrix operator*(const MMatrix& lhs, const double& rhs)
{
	MMatrix temp = lhs;
	for (int i = 0; i < lhs.Rows(); i++)
	{
		for (int j = 0; j < lhs.Cols(); j++)
		{
			temp(i, j) *= rhs;
		}
	}

	return temp;
}

// Operator overload for "matrix / scalar"
inline MMatrix operator/(const MMatrix& lhs, const double& rhs)
{
	if (rhs != 0)
	{
		MMatrix temp = lhs;
		for (int i = 0; i < lhs.Rows(); i++)
		{
			for (int j = 0; j < lhs.Cols(); j++)
			{
				temp(i, j) /= rhs;
			}
		}

		return temp;
	}

	else
	{
		std::cout << "Error: cannot divide a matrix by 0." << std::endl;
		exit(1);
	}
}

// Operator overload for "matrix + matrix"
inline MMatrix operator+(const MMatrix& lhs, const MMatrix& rhs)
{
	if (lhs.Cols() != rhs.Cols())
	{
		std::cout << "Error: to add matrices together they must have the same number of columns." << std::endl;
		exit(1);
	}
	if (lhs.Rows() != rhs.Rows())
	{
		std::cout << "Error: to add matrices together they must have the same number of rows." << std::endl;
		exit(1);
	}


	else
	{
		MMatrix temp = rhs;
		for (int i = 0; i < rhs.Rows(); i++)
		{
			for (int j = 0; j < rhs.Cols(); j++)
			{
				temp(i, j) += lhs(i,j);
			}
		}

		return temp;

	}

}

// Operator overload for "matrix - matrix"
inline MMatrix operator-(const MMatrix& lhs, const MMatrix& rhs)
{
	if (lhs.Cols() != rhs.Cols())
	{
		std::cout << "Error: to subtract matrices from one another they must have the same number of columns." << std::endl;
		exit(1);
	}
	if (lhs.Rows() != rhs.Rows())
	{
		std::cout << "Error: to subtract matrices from one another they must have the same number of rows." << std::endl;
		exit(1);
	}

	else
	{
		MMatrix temp = lhs;
		for (int i = 0; i < lhs.Rows(); i++)
		{
			for (int j = 0; j < lhs.Cols(); j++)
			{
				temp(i, j) -= rhs(i, j);
			}
		}

		return temp;

	}

}

// Operator overload for "matrix * vector"
inline MVector operator*(const MMatrix& lhs, const MVector& rhs)
{
	if (lhs.Cols() != rhs.size())
	{
		std::cout << "Error: to multiply a matrix by a vector the size of the vector must equal the number of columns of the matrix." << std::endl;
		exit(1);
	}

	else
	{
		MVector temp(lhs.Rows(), 0);
		for (int i = 0; i < lhs.Rows(); i++)
		{
			for (int j = 0; j < lhs.Cols(); j++)
			{
				temp[i] += lhs(i,j)*rhs[j];
			}
		}

		return temp;

	}

}

#endif
