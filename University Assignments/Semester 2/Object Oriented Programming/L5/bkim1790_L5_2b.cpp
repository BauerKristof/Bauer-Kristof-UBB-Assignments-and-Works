/*
Bauer Kristof
Csoport:511
*/

#include <iostream>
using namespace std;
template < class T>

T Fibonacci(int sorszam, T elso,T masodik)
{
	T f1 = elso;
	T f2 = masodik;
	T f3 = 0;

	int db = 2;
	while (db < sorszam)
	{
		f3 = f1 + f2;
		f1 = f2;
		f2 = f3;
		db++;
	}
	return f3;
}
int main()
{
	cout << Fibonacci(6, 0, 1) << endl;
		cout << Fibonacci(6, 0.0, 1.0) << endl;
	system("pause");

	return 0;
}
