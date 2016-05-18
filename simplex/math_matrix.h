//math_matrix.h
#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
namespace Math {
	template <class T>
	class MathMatrix {
	template <class U> friend MathVector<U> get_Xb(MathMatrix<U>&, int);
	template <class U> friend MathVector<U> pick_point(MathMatrix<U>&, int);
	public:
		MathMatrix<T>& rand_member(int range);
		void replace_point(int, MathVector<T>&);
	
	public:
		MathMatrix() : row(0), col(0), a(NULL) {}
		MathMatrix(int r, int c) : row(r), col(c)
		{
			//build array
			a = new T*[row+1];
			a[0] = new T[(row+1)*(col+1)];
			for (int i = 1; i <= row; i++)
				a[i] = a[i - 1] + col + 1;
		}
		MathMatrix(const MathMatrix& rhs) : row(rhs.row), col(rhs.col)
		{
			//build array
			int member = (row+1)*(col+1);
			a = new T*[row+1];
			a[0] = new T[member];
			for (int i = 1; i <= row; i++)
				a[i] = a[i - 1] + col + 1;
			//copy array data
			for (int i = 0; i < member; i++)
				a[0][i] = rhs.a[0][i];
		}
		MathMatrix& operator = (const MathMatrix& rhs)
		{
			int member = (rhs.row+1)*(rhs.col+1);
			if (row != rhs.row || col != rhs.col) {
				//copy row and col
				row = rhs.row;
				col = rhs.col;
				//destruct matrix data
				if(a != NULL && a[0] != NULL)
				{delete [] a[0];delete [] a;}
				//rebuid array
				a = new T*[row+1];
				a[0] = new T[member];
				for (int i = 1; i <= row; i++)
					a[i] = a[i - 1] + col + 1;
			}
			//copy array data
			for (int i = 0; i < member; i++)
				a[0][i] = rhs.a[0][i];
			return *this;
		}
		~MathMatrix()
		{
			if(a != NULL && a[0] != NULL)
			{delete [] a[0];delete [] a;}
		}
		
	public:
		void display() const;
		T* operator [] (int);
	private:
		int row, col;
		T** a;
	};
	
	using std::cout; using std::endl;
	using std::setw; using std::setprecision; using std::fixed;
	
	template <class T>
	void MathMatrix<T>::display() const
	{
		cout << fixed << setprecision(2);
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= col; j++)
				cout << setw(8) << a[i][j];
			cout << endl;
		}
	}
	
	template<class T>
	T* MathMatrix<T>::operator [] (int index)
	{
		return a[index];
	}

	
	template <class T>
	MathMatrix<T>& MathMatrix<T>::rand_member(int range)
	{
		for(int i = 1; i <= row; i++)
			for(int j = 1; j <= col; j++) {
				T tmp;
				tmp = rand() % abs(range +1);
				tmp += rand() / (double) RAND_MAX;
				if (range < 0 && rand()%2) tmp = -tmp;
				a[i][j] = tmp;
			}
	}
	
	template <class T>
	MathVector<T> get_Xb(MathMatrix<T>& target, int xh)
	{
		MathVector<T> out(target.col);
		for (int i = 1; i <= target.col; i++)
			out[i] = 0;
		
		for (int i = 1; i <= target.col; i++)
			for (int j = 1; j <= target.row; j++)
				if (j != xh)
					out[i] += target[j][i];
		
		for (int i = 1; i <= target.col; i++)
			out[i] /= (target.row - 1);
		return out;
	}
	template <class T>
	MathVector<T> pick_point(MathMatrix<T>& matrix, int index)
	{
		MathVector<T> out(matrix.col);
		for (int i = 1; i <= matrix.col; i++)
			out[i] = matrix[index][i];
		return out;
	}
	template <class T>
	void MathMatrix<T>::replace_point(int index, MathVector<T>& point)
	{
		if(point.get_size() != col) throw "";
		for (int i = 1; i <= col; i++)
			a[index][i] = point[i];
	}
}


#endif
