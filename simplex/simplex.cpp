#include "math_vector.h"
#include "math_matrix.h"
#include "func.h"
#include <cstdlib>
#include <ctime>

namespace {
	const int& N = Simp::degree;
}

vvector getFx(mmatrix& M, objtype (*func)(vvector&))
{
	vvector out(N+1);
	vvector tmp_point;
	for (int i = 1; i <= N + 1; i++) {
		tmp_point = Math::pick_point(M, i);
		out[i] = func(tmp_point);
	}
	return out;
}

int main()
{
	srand(time(NULL));
	
	mmatrix M(N+1, N);	//存放X1~Xn+1個點的矩陣 
	vvector xb(N);		//存放Xb = (1/n) * sigma(1..N+1 expect xh, xi)
	objtype Fxb;		//存放func(Xb) 
	vvector Fx(N+1);	//存放矩陣內N+1個點的 F(Xi)的值
	int ixh, ixl; 		//index for F(xh), F(xl)
	vvector xh, xl;		//存放xh 和 xl 兩個點 
	objtype Fxh, Fxl;	//存放func(xh), func(xl) 
	objtype Q = 100;		//Q = sigma(1..N+1 , (F(xi) - F(xl))^2)
	int Qcount = 0;		//魂圈跑的次數 
	
	M.rand_member(Simp::random_range);
	Fx = getFx(M, func);
	
	
	while (Qcount < Simp::max_count) {
		vvector xr;
		objtype Fxr;
		vvector xc;
		objtype Fxc;
		vvector xe;
		objtype Fxe;
		
		//找xh 
		ixh = Fx.find_max_index();
		Fxh = Fx[ixh];
		xh = pick_point(M, ixh);
		//找xl 
		ixl = Fx.find_min_index();
		Fxl = Fx[ixl];
		xl = pick_point(M, ixl);
		//找xb 
		xb = Math::get_Xb(M, ixh);
		Fxb = func(xb);
		//
		Q = 0;
		for (int i = 1; i <= N + 1; i++) {
			Q += (Fx[i] - Fxl)*(Fx[i] - Fxl);
		}
		Qcount++;
		if (Q < 2*Simp::epsilon) break;
		//找xr 
		xr = xb + Simp::alpha * (xb - xh);
		Fxr = func(xr);
		if (Fxr > Fxh) {
			xc = xb + Simp::beta * (xh - xb);
			Fxc = func(xc);
			if (Fxc < Fxh) {
				M.replace_point(ixh, xc);
				Fx[ixh] = Fxc;
			}
			else {
				vvector tmp;
				for (int i = 1; i <= N+1; i++) {
					tmp = pick_point(M, i);
					tmp += xl;
					tmp /= 2;
					M.replace_point(i, tmp);
				}
				Fx = getFx(M, func);
			}
		}
		else
		{
			if (Fxr > Fxl) {
				M.replace_point(ixh, xr);
				Fx[ixh] = Fxr;
			}
			else { 
				xe = xb + Simp::gama * (xr - xb);
				Fxe = func(xe);
				if (Fxe > Fxl) {
					M.replace_point(ixh, xr);
					Fx[ixh] = Fxr;
				}
				else {
					M.replace_point(ixh, xe);
					Fx[ixh] = Fxe;
				}
			}
		}
	}
	
	std::cout << "Qcount = " << Qcount << std::endl; 
	xl.display();
	
	return 0;
}
