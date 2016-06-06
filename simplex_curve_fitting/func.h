//func.h
#ifndef FUNC_H
#define FUNC_H
#include <cmath>
#include "container.h"

namespace Simp {
	const char r_filename[] = "output.txt";
	const int num_data_point = 190;
	const double dt = 0.02;
	vvector read_data_from_file(num_data_point);
	const int degree = 5;		//number of variables in your function 
	const int max_count = 1000;	//maxium times for searching numerical analysis method
	const int sol_count = 5;	//number of searching solutions
	const double random_range = 5.0; //for initial guess value, if negative, means matrix includes negative member
	const double alpha = 1.0;	//constant for numerical analysis method
	const double beta = 0.5;	//constant for numerical analysis method
	const double gama = 2.0;	//constant for numerical analysis method
	const double epsilon = 1.0E-30;
	const double mu = 1.0;
}


objtype func(vvector& x) //this is your test function
{
	double tmp;
	vvector out(Simp::num_data_point);
	for (int i = 1; i <= Simp::num_data_point; i++) {
		double t = Simp::dt * double(i);
		tmp = x[1] * exp(-x[2]*t) * cos(x[3]*t + x[4]) + x[5]
			- Simp::read_data_from_file[i];
		out[i] = tmp;
	}
	return normVector(out);
}
#endif
