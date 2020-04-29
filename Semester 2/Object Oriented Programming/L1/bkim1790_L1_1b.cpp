/*Nev:Bauer Kristof
Csoport:511*/

#include <iostream>
#include <fstream>

using namespace std;


void kiir(const int *a, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void spiralSorrend(const int* matrix, int n, int* spiral)
{
	int m = sqrt(n);
	int mat[36][36], K=0,vege=0;

	cout << "A matrix";
	kiir(matrix, n);

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			mat[i][j] = matrix[j + i * m];
		}
	}

	if (m % 2 == 1) vege = m / 2 + 1;
	else vege = m / 2;

	for (int i = 0; i < vege; i++)
	{
		for (int j = i; j < m - i; j++)
		{

			spiral[K] = mat[i][j];
			K++;

		}

		for (int j = i + 1; j < m - i - 1; j++)
		{
			spiral[K] = mat[j][m - i - 1];
			K++;
		}

		for (int j = m - i - 1; j > i; j--)
		{
			spiral[K] = mat[m - i - 1][j];
			K++;
		}

		for (int j = (m- i)-1; j > i; j--)
		{
			spiral[K] = mat[j][i];
			K++;
		}
	}

	cout << "Spiralisan";
	kiir(spiral, K);


}


int main()
{
	int n=9;
	const int matrix[] = { 1,2,3,4,5,6,7,8,9 };
	int* spiral=new int[n];

	spiralSorrend(matrix, n, spiral);
	delete[] spiral;
	
	system("pause");
	return 0;
}