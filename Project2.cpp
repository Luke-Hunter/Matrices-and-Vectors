#include "mmatrix.h"
#include "advection.h"
#include <cmath>
#include <fstream>

int main()
{
	double pi = 4 * atan(1);
	int N = 100; // number of elements
	double x = 0; // initial x
	double h = 2 * pi / N; // step size

	AdvectionElement* e = new AdvectionElement[N];

	// for loop to set the initial conditions and neighbour values for the elements
	// sine-wave initial conditions
	for (int i = 0; i < N; i++)
	{
		e[i].X[0] = x;
		e[i].X[1] = x + h;
		e[i].U[0] = 1.5 + sin(e[i].X[0]);
		e[i].U[1] = 1.5 + sin(e[i].X[1]);

		if (i > 0) { e[i].Left_neighbour_pt = &e[i - 1]; }
		if (i < N - 1) { e[i].Right_neighbour_pt = &e[i + 1]; }
		if (i == 0) { e[i].Left_neighbour_pt = &e[N - 1]; }
		if (i == N - 1) { e[i].Right_neighbour_pt = &e[0]; }

		x += h;
	}

	double dt = 1.0/900.0; // size of timestep, change this to change the resolution
	int n = 900; // number of timesteps taken, change this to change the total time taken
	// note that n*dt is the total time taken

	// for loop to progress time
	for (int j = 0; j < n; j++)
	{

		AdvectionElement* tempe = new AdvectionElement[N];

		// for loop to calculate values
		for (int i = 0; i < N; i++)
		{
			tempe[i] = e[i];
			tempe[i].timestep(dt);

		}

		// for loop to then set the values
		for (int i = 0; i < N; i++)
		{
			e[i] = tempe[i];
		}

	}

	std::ofstream efile;
	efile.open("edt900.txt");


	double maxerror = 0;
	for (int i = 0; i < N; i++)
	{
		double trueU = 1.5 + sin(e[i].interpolated_x(0) - n*dt);
		double approxU = e[i].interpolated_u(0);
		double error = std::abs(trueU - approxU);

		if (error > maxerror)
		{
			maxerror = error;
		}


	}

	efile.width(20); efile.precision(8); efile << n;
	efile.width(20); efile.precision(8); efile << maxerror << "\n";


	std::ofstream file;
	file.open("Advection sine time 1 resolution 0.001.txt");

	if (!file)
	{
		std::cout << "Error: could not open file successfully." << std::endl;
		return 1;
	}

	// writing results out to file so that a graph can be made
	for (int i = 0; i < N; i++)
	{
		file.width(20); file.precision(8); file << e[i].interpolated_x(0);
		file.width(20); file.precision(8); file << e[i].interpolated_u(0) << std::endl;
	}

	file.close();

	return 0;
}


/* Square-wave initial condition

// for loop to set the initial conditions and neighbour values for the elements
// square-wave initial conditions
for (int i = 0; i < N; i++)
{
e[i].X[0] = x;
e[i].X[1] = x + h;

if (x <= 1.0)
{
e[i].U[0] = 1;
e[i].U[1] = 1;
}

else
{
e[i].U[0] = 0;
e[i].U[1] = 0;
}

if (i > 0) { e[i].Left_neighbour_pt = &e[i - 1]; }
if (i < N - 1) { e[i].Right_neighbour_pt = &e[i + 1]; }
if (i == 0) { e[i].Left_neighbour_pt = &e[N - 1]; }
if (i == N - 1) { e[i].Right_neighbour_pt = &e[0]; }

x += h;
}

*/

/* Sine-wave initial conditions

// for loop to set the initial conditions and neighbour values for the elements
// sine-wave initial conditions
for (int i = 0; i < N; i++)
{
e[i].X[0] = x;
e[i].X[1] = x + h;
e[i].U[0] = 1.5 + sin(e[i].X[0]);
e[i].U[1] = 1.5 + sin(e[i].X[1]);

if (i > 0) { e[i].Left_neighbour_pt = &e[i - 1]; }
if (i < N - 1) { e[i].Right_neighbour_pt = &e[i + 1]; }
if (i == 0) { e[i].Left_neighbour_pt = &e[N - 1]; }
if (i == N - 1) { e[i].Right_neighbour_pt = &e[0]; }

x += h;
}

*/


/* Faulty code

#include "mmatrix.h"
#include "advection.h"
#include <fstream>
#include <cmath>

int main()
{
double pi = 4 * atan(1);
int N = 100; // number of elements
double x = 0; // initial x
double h = 2 * pi / N; // step size


AdvectionElement* e = new AdvectionElement[N];

// for loop to set the neighbour values for the elements
for (int i = 0; i < N; i++)
{
e[i].X[0] = x;
e[i].X[1] = x + h;
e[i].U[0] = 1.5 + sin(e[i].X[0]);
e[i].U[1] = 1.5 + sin(e[i].X[1]);

if (i > 0)
{
e[i].Left_neighbour_pt = &e[i - 1];
}
if (i < N - 1)
{
e[i].Right_neighbour_pt = &e[i + 1];
}
if (i == 0)
{
e[i].Left_neighbour_pt = &e[N - 1];
}
if (i == N - 1)
{
e[i].Right_neighbour_pt = &e[0];
}

x += h;
}


double dt = 0.01; // size of timestep, change this to change the resolution
int n = 0; // number of timesteps taken, change this to change the total time taken
// note that n*dt is the total time taken

// for loop to progress time
for (int j = 0; j < n; j++);
{
AdvectionElement* tempe = new AdvectionElement[N];

// for loop to calculate values
for (int k = 0; k < N; k++)
{
tempe[k] = e[k];
tempe[k].timestep(dt);
}

// for loop to then set the values
for (int l = 0; l < N; l++)
{
e[l] = tempe[l];
}

}



std::ofstream file;
file.open("Advection sine time 0.txt");
if (!file) // error check to make sure file opens successfully
{
std::cout << "Error: file could not open successfully." << std::endl;
return 1;
}


// writing results out to file so that a graph can be made
for (int m = 0; m < N; m++)
{
file.width(15); file.precision(8); file << e[m].interpolated_x(0);
file.width(15); file.precision(8); file << e[m].interpolated_u(0) << "\n";
}


file.close();

return 0;
}

*/



/* Advection sin test

std::ofstream file;
file.open("Advection sin test200.txt");
if (!file) return 1;

file.width(10); file << "x0";
file.width(10); file << "x1";
file.width(10); file << "u0";
file.width(10); file << "u1";
file.width(10); file << "xmid";
file.width(10); file << "umid\n";

double N = 200.0;
double pi = 3.141;
AdvectionElement a;

for (int i = 0; i < N; i++)
{
a.X[0] = (i/N)*2*pi;
a.X[1] = ((i+1)/N)*2*pi;
a.U[0] = 1.5 + sin(a.X[0]);
a.U[1] = 1.5 + sin(a.X[1]);
double xmid = a.interpolated_x(0);
double umid = a.interpolated_u(0);

file.width(10); file << a.X[0];
file.width(10); file << a.X[1];
file.width(10); file << a.U[0];
file.width(10); file << a.U[1];
file.width(10); file << xmid;
file.width(10); file << umid << "\n";

}

file.close();


*/