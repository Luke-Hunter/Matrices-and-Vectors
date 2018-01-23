#ifndef ODE_SOLVERS
#define ODE_SOLVERS

#include "mvector.h"
#include <fstream>

// Declaration for an Euler scheme ODE solver
int EulerSolve(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." <<std::endl;
		return 0;
	}
	else
	{
		double h = (b - a) / (steps - 1); //calculating step size h
		double x = a;

		for (int i = 0; i < steps; i++)
		{
			x = a + i*h;
			y = y + h*f(x, y);
		}
	}

	return 0;
};

// Declaration for an MidpointSolve ODE solver
int MidpointSolve(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." << std::endl;
		return 0;
	}
	double h = (b - a) / (steps - 1); //calculating step size h
	double x = a;

	for (int i = 0; i < steps; i++)
	{
		x = a + i*h;
		y = y + h*f(x + 0.5*h, y + 0.5*h*f(x, y));
	}

	return 0;
};

// Declaration for an RungeKuttaSolve ODE solver
int RungeKuttaSolve(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." << std::endl;
		return 0;
	}
	double h = (b - a) / (steps - 1); //calculating step size h
	double x = a;
	MVector k1, k2, k3, k4;

	for (int i = 0; i < steps; i++)
	{
		x = a + i*h;
		k1 = f(x, y);
		k2 = f(x + (h / 2), y + (h / 2)*k1);
		k3 = f(x + (h / 2), y + (h / 2)*k2);
		k4 = f(x + h, y + h*k3);
		y = y + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);
	}

	return 0;
};

int EulerSolveToFile(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." << std::endl;
		return 0;
	}
	double h = (b - a) / (steps - 1); //calculating step size h
	double x = a;

	std::ofstream ESFile;
	ESFile.open("EulerSolve values.txt");
	if (!ESFile) return 1;

	ESFile.width(10); ESFile << "i";
	ESFile.width(10); ESFile << "x";
	ESFile.width(10); ESFile << "Y\n";

	for (int i = 0; i < steps; i++)
	{
		x = a + i*h;
		y = y + h*f(x, y);

		ESFile.width(10); ESFile << i;
		ESFile.width(10); ESFile << x;
		ESFile.width(10); ESFile << y << "\n";

	}

	ESFile.close();

	return 0;
};

int MidpointSolveToFile(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." << std::endl;
		return 0;
	}
	double h = (b - a) / (steps - 1); //calculating step size h
	double x = a;

	std::ofstream MPSFile;
	MPSFile.open("MidPointSolve values.txt");
	if (!MPSFile) return 1;

	MPSFile.width(10); MPSFile << "i";
	MPSFile.width(10); MPSFile << "x";
	MPSFile.width(10); MPSFile << "Y" << "\n";

	for (int i = 0; i < steps; i++)
	{
		x = a + i*h;
		y = y + h*f(x + 0.5*h, y + 0.5*h*f(x, y));

		MPSFile.width(10); MPSFile << i;
		MPSFile.width(10); MPSFile << x;
		MPSFile.width(10); MPSFile << y << "\n";

	}

	MPSFile.close();

	return 0;
};

int RungeKuttaSolveToFile(int steps, double a, double b, MVector &y, MFunction &f)
{
	if (steps <= 1)
	{
		std::cout << "Error: Step size must be a positive integer greater than 1." << std::endl;
		return 0;
	}
	double h = (b - a) / (steps - 1); //calculating step size h
	double x = a;
	MVector k1, k2, k3, k4;

	std::ofstream RKSFile;
	RKSFile.open("RungaKuttaSolve values.txt");
	if (!RKSFile) return 1;

	RKSFile.width(10); RKSFile << "i";
	RKSFile.width(10); RKSFile << "x";
	RKSFile.width(10); RKSFile << "Y" << "\n";

	for (int i = 0; i < steps; i++)
	{
		x = a + i*h;
		k1 = f(x, y);
		k2 = f(x + (h / 2), y + (h / 2)*k1);
		k3 = f(x + (h / 2), y + (h / 2)*k2);
		k4 = f(x + h, y + h*k3);
		y = y + (h / 6)*(k1 + 2 * k2 + 2 * k3 + k4);

		RKSFile.width(10); RKSFile << i;
		RKSFile.width(10); RKSFile << x;
		RKSFile.width(10); RKSFile << y << "\n";

	}

	RKSFile.close();

	return 0;
};

#endif;