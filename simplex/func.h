//func.h
#ifndef FUNC_H
#define FUNC_H
#include <cmath>
typedef double objtype;	//input and output value data type
typedef Math::MathVector<objtype> vvector;
typedef Math::MathMatrix<objtype> mmatrix;

namespace Simp {
	const int degree = 1;		//number of variables in your function 
	const int max_count = 1000;	//maxium times for trying numerical analysis method
	const int random_range = 100; //for initial guess value, if negative, means matrix includes negative member
	const double alpha = 1.0;	//constant for numerical analysis method
	const double beta = 0.5;	//constant for numerical analysis method
	const double gama = 2.0;	//constant for numerical analysis method
	const double epsilon = 1.0E-16;
}

inline
objtype func(vvector& x) //this is your test function
{
	return fabs(1 + 0.06 * x[1] - pow(1.0225, x[1]));
	//return pow(x[1]-2,2)/(1+pow(x[1]-2,2)) + pow(x[2]-3,4)/(1+pow(x[2]-3,4));
	//return pow(xi[1]-xi[2], 4) + pow(xi[1]*xi[1]+xi[2]-2, 2) +pow(xi[1]*xi[2]-1, 2);
	//return fabs(-20.0*exp(-0.1)*sqrt(xi[1]*xi[1]+xi[2]*xi[2]) - exp(0.5*(cos(2*3.14*xi[1])+cos(2*3.14*xi[2]))));
}
#endif
