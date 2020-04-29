/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely kiszámítja az n-edik Fibonacci-számot.
*/

#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int &n)
{
	ifstream file;
	file.open("bkim1790_L5_6.txt");
	if (file.is_open())
	{
		file >> n;
	}

}

int fibo(int n) 
{
	if (n == 1) return 1;
	else if (n == 2) return 1;
	else return fibo(n - 2) + fibo(n - 1);
}



int main()
{
	int n;
	beolvas(n);
	cout << fibo(n) << endl;
	system("PAUSE");
	return 0;

}