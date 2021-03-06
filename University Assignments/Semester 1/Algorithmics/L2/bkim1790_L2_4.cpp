// bkim1790_L2_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Írjunk algoritmust, amely megadja a Fibonacci-sorozat egy adott számnál kisebb elemeinek számát!
*/

#include <iostream>
#include <fstream>

using namespace std;

int beolvas()
{
	ifstream file;
	file.open("bkim1790_L2_4.txt");

	int n;
	if (file.is_open())
	{
		file >> n;
	}
	file.close();
	return n;
}

void fibo(int n)
{
	int a = 0;
	int b = 1;
	int c = a + b;
	int db = 1;


	while (c < n)
	{
		a = b;
		b = c;
		c = a + b;
		db++;
	}

	cout << db<< " darab kisebb elem van a Fibonacci-sorozatban, mint " << n;
}

int main()
{
	int n = beolvas();
	fibo(n);
	
	return 0;
}
