/*Nev: Bauer Kristof
Csoport:511*/

#include <iostream>

using namespace std;

template <class T, int N>

class Matrix
{
	T *hMatr;
  public:
	  Matrix();
	  Matrix(T *hMatr);
      Matrix(const Matrix &Matr);
	  ~Matrix();
	  Matrix<T,N> szoroz(T skalar);
	  int operator ==(Matrix M2);
	  void kiir();

};

template < class T, int N >
int Matrix < T, N > :: operator ==(Matrix M2)
{
	for (int i = 0; i < N * (N + 1) / 2; i++)
	{
		if (hMatr[i] != M2.hMatr[i])
		{
			return 0;
		}
	}
	return 1;
}

template <class T, int N>
Matrix<T,N> Matrix<T, N>::szoroz(T skalar)
{
	Matrix eredmeny(hMatr);

	for (int i = 0; i < (N*(N + 1) / 2); i++)
	{
	  eredmeny.hMatr[i] *= skalar;
	}
	return eredmeny;
}

template <class T, int N>
Matrix<T,N>::~Matrix()
{
	delete hMatr;
}

template <class T, int N>
Matrix<T, N>::Matrix()
{
	hMatr = new T[(N*(N + 1) / 2)];

	int db = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			if (i == j)
			{
				hMatr[db] = 1;
				db++;
			}
			else if (j > i)
			{
				hMatr[db] = 0;
				db++;
			}
		}
	}
}

template <class T, int N>
Matrix<T, N>::Matrix(T *hMatrix)
{
	hMatr = new T[(N*(N + 1) / 2)];

	for (int i = 0; i < (N*(N+1)/2); i++)
	{

		hMatr[i] = hMatrix[i];
	}
	

}

template < class T, int N >
Matrix < T, N > :: Matrix(const Matrix &Matr)
{

	hMatr = new T[(N*(N + 1) / 2)];

	for (int i = 0; i < (N*(N + 1) / 2); i++)
	{
		hMatr[i] = Matr.hMatr[i];
	}


}



template <class T, int N>
void Matrix<T, N>::kiir()
{
	int db = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			if (i == j)
			{
				cout << hMatr[db] << " ";
				db++;
			}
			else if (j > i)
			{
				cout << hMatr[db] << " ";
					db++;
				
			}
			else 
			{
				cout << "0 ";
			}
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	double t[] = { 1.5,2.3,4.5,6.2,12.5,1.4 };
	Matrix<double, 3>matrix1(t);
	Matrix<double, 3>matr3(matrix1);
	matr3.szoroz(2).kiir();
	matr3.kiir();
	if (matrix1 == matr3)
	{
		cout << "Megegyezik" << endl;
	}
	else
	{
		cout << "Nem egyezik meg" << endl;
	}
		system("pause");
	return 0;
}