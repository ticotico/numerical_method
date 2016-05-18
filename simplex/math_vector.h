//math_vector.h
#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H
#include <iostream>
#include <iomanip>
namespace Math {
	namespace {const double epsilon = 1.0e-16;}
	
	template <class T>
	class MathVector {
	template <class U> friend MathVector<U> operator* (const MathVector<U>&, U);
	template <class U> friend MathVector<U> operator* (U, const MathVector<U>&);
	public:
		int find_max_index();
		int find_min_index();
	public:
		MathVector() : size(0), a(NULL) {}
		MathVector(int n) : size(n)
		{
			a = new T[size+1];
		}
		MathVector(int n, T* ina) : size(n)
		{
			a = new T[size+1];
			//no check ina size here
			for (int i = 1; i <= size; i++)
				a[i] = ina[i - 1];
		}
		MathVector(const MathVector& rhs) : size(rhs.size)
		{
			a = new T[size+1];
			for(int i = 1; i <= size; i++)
				a[i] = rhs.a[i];
		}
		MathVector& operator =(const MathVector& rhs)
		{
			if (size != rhs.size) {
				size = rhs.size;
				if(a != NULL) delete [] a;
				a = new T[size+1];
			}
			for (int i = 1; i <= size; i++)
				a[i] = rhs.a[i];
		}
		~MathVector()
		{
			if (a != NULL) delete [] a;
		}
	public:
		T& operator[] (int index) {return a[index];}
		MathVector& operator += (const MathVector&);
		MathVector& operator -= (const MathVector&);
		MathVector& operator *= (T);
		MathVector& operator /= (T);
		MathVector operator + (const MathVector&) const;
		MathVector operator - (const MathVector&) const;
		MathVector operator / (T) const;
		void display() const;
		int get_size() const {return size;}
		
	private:
		int size;
		T* a;
	};
	
	template <class T>
	MathVector<T>& MathVector<T>::operator += (const MathVector& rhs)
	{
		if (size != rhs.size) throw "";
		for (int i = 1; i<= size; i++)
			a[i] += rhs.a[i];
		return *this;
	}
	
	template <class T>
	MathVector<T>& MathVector<T>::operator -= (const MathVector& rhs)
	{
		if (size != rhs.size) throw "";
		for (int i = 1; i<= size; i++)
			a[i] -= rhs.a[i];
		return *this;
	}
	
	template <class T>
	MathVector<T>& MathVector<T>::operator *= (T rhs)
	{
		for (int i = 1; i <= size; i++)
			a[i] *= rhs;
		return *this;
	}
	
	template <class T>
	MathVector<T>& MathVector<T>::operator /= (T rhs)
	{
		if (rhs <= epsilon) throw "";
		for (int i = 1; i <= size; i++)
			a[i] /= rhs;
		return *this;
	}
	
	template <class T>
	MathVector<T> MathVector<T>::operator + (const MathVector<T>& rhs) const
	{
		if (size != rhs.size) throw "";
		MathVector<T> tmp(size);
		for (int i = 0; i <= size; i++)
			tmp.a[i] = a[i] + rhs.a[i];
		return tmp;
	}
	
	template <class T>
	MathVector<T> MathVector<T>::operator - (const MathVector<T>& rhs) const
	{
		if (size != rhs.size) throw "";
		MathVector<T> tmp(size);
		for (int i = 0; i <= size; i++)
			tmp.a[i] = a[i] - rhs.a[i];
		return tmp;
	}
	
	template <class T>
	MathVector<T> operator * (const MathVector<T>& lhs, T rhs)
	{
		MathVector<T> tmp(lhs.size);
		for (int i = 1; i <= lhs.size; i++)
			tmp.a[i] = lhs.a[i] * rhs;
		return tmp;
	}
	
	template <class T>
	MathVector<T> operator * (T lhs, const MathVector<T>& rhs)
	{
		MathVector<T> tmp(rhs.size);
		for (int i = 1; i <= rhs.size; i++)
			tmp.a[i] = rhs.a[i] * lhs;
		return tmp;
	}
	
	template <class T>
	MathVector<T> MathVector<T>::operator / (T rhs) const
	{
		if (rhs <= epsilon) throw "";
		MathVector<T> tmp(size);
		for (int i = 0; i <= size; i++)
			tmp.a[i] = a[i] / rhs;
		return tmp;
	}
	
	template <class T>
	int MathVector<T>::find_max_index()
	{
		int max = 1;
		for (int i = 2; i <= size; i++) {
			if (a[max] < a[i]) max = i;
		}
		return max;
	}
	
	template <class T>
	int MathVector<T>::find_min_index()
	{
		int min = 1;
		for (int i = 2; i <= size; i++) {
			if (a[min] > a[i]) min = i;
		}
		return min;
	}
	
	using std::cout; using std::endl;
	using std::setw; using std::setprecision; using std::fixed;
	
	template <class T>
	void MathVector<T>::display() const
	{
		cout << fixed << setprecision(2);
		for (int i = 1; i <= size; i++)
			cout << setw(8) << a[i];
		cout << endl;
	}
}

#endif
