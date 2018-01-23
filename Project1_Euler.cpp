#include "ODESolvers.h"
#include <cmath>

int main()
{


	Eqn1p32Derivs f;
	int maxNewtonSteps = 100;
	double guess = -14;
	double tol = 1e-8;
	for (int i = 0; i < maxNewtonSteps; i++)
	{
		MVector y(4);
		// y[0] = y, y[1] = dy/dx, y[2] = Z_1, y[3] = Z_2
		y[0] = 17; y[1] = guess; y[2] = 0.0; y[3] = 1.0;

		RungeKuttaSolve(100, 1.0, 3.0, y, f); // solve IVP

		double phi = y[0] - (14.33333333); // calculate residual
		double phidash = y[2]; // 'Jacobian' phidash = z_1(x=1)

		std::cout << y[0] << std::endl;

		if (std::abs(phi) < tol) break; // exit if converged

		guess -= phi / phidash; // apply newton step
	return 0;
}




	/*
	for (int i = 1; i < 21; i++)
	{
	MVector y(2);
	y[0] = 0;
	y[1] = 1;
	double a = 1.0, b = 3.0;
	Eqn1p32DerivsIVP f;
	int steps = 10 * i;
	MidpointSolve(steps, a, b, y, f);
	std::cout << "For N = " << steps << ", v = " << v << ". Absolute error is " << v - e << std::endl;
	}


	Eqn1p32Derivs f;
	int maxNewtonSteps = 100;
	double guess = -14;
	double tol = 1e-8;
	for (int i = 0; i < maxNewtonSteps; i++)
	{
	MVector y(4);
	// y[0] = y, y[1] = dy/dx, y[2] = Z_1, y[3] = Z_2
	y[0] = 17; y[1] = guess; y[2] = 0.0; y[3] = 1.0;

	RungeKuttaSolve(100, 1.0, 3.0, y, f); // solve IVP

	double phi = y[0] - (14.33333333); // calculate residual
	double phidash = y[2]; // 'Jacobian' phidash = z_1(x=1)

	std::cout << y[0] << std::endl;

	if (std::abs(phi) < tol) break; // exit if converged

	guess -= phi / phidash; // apply newton step

	}


	Eqn1p5Derivs f;
	int maxNewtonSteps = 100;
	double guess = 0;
	double tol = 1e-8;
	for (int i = 0; i<maxNewtonSteps; i++)
	{
	MVector y(4);
	// y[0] = y, y[1] = dy/dx, y[2] = Z_1, y[3] = Z_2
	y[0] = 0; y[1] = guess; y[2] = 0.0; y[3] = 1.0;

	RungeKuttaSolve(100, 0.0, 1.0, y, f); // solve IVP

	double phi = y[0] - 1; // calculate residual
	double phidash = y[2]; // 'Jacobian' phidash = z_1(x=1)

	std::cout << y[0] << std::endl;

	if (std::abs(phi) < tol) break; // exit if converged

	guess -= phi / phidash; // apply newton step

	for (int i = 1; i < 21; i++)
	{
	MVector v(2);
	v[0] = 17;
	v[1] = 1;
	double a = 1.0, b = 3.0;
	FunctionF3 f;
	int steps = i;
	EulerSolve(steps, a, b, v, f);
	std::cout << "For N = " << steps << ", v = " << v << std::endl;
	}

	MVector e(2, 0.5);
	e[1] = 2.71828;

	MVector v(2);
	v[0] = 0;
	v[1] = 1;
	double a = 0.0, b = 1.0;
	FunctionF2 f;
	int steps100 = 100;
	EulerSolveToFile(steps, a, b, v, f);
	MidpointSolveToFile(steps, a, b, v, f);
	RungeKuttaSolveToFile(steps100, a, b, v, f);

	for (int i = 1; i < 21; i++)
	{
		MVector v(2);
		v[0] = 0;
		v[1] = 1;
		double a = 0.0, b = 1.0;
		FunctionF2 f;
		int steps = 10 * i;
		MidpointSolve(steps, a, b, v, f);
		std::cout << "For N = " << steps << ", v = " << v << ". Absolute error is " << v - e << std::endl;
	}

	for (int i = 1; i < 21; i++)
	{
		MVector v(2);
		v[0] = 0;
		v[1] = 1;
		double a = 0.0, b = 1.0;
		FunctionF2 f;
		int steps = 10 * i;
		RungeKuttaSolve(steps, a, b, v, f);
		std::cout << "For N = " << steps << ", v = " << v << ". Absolute error is " << v - e << std::endl;
	}
	*/