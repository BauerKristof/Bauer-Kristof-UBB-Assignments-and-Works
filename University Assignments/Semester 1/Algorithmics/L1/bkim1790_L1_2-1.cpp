// bkim1790_L1_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Olvassunk be a billentyűzetről három egész számot. Írjuk ki őket növekvő sorrendben!

*/

#include "pch.h"
#include <iostream>

using namespace std;

void sortNumb(int a, int b, int c)
{
	int segedValtozo=0;

	if (a > b)
	{
		segedValtozo = a;
		a = b;
		b = segedValtozo;
	}

	if (b > c)
	{
		segedValtozo = b;
		b = c;
		c = segedValtozo;
	}


	if (a > b)
	{
		segedValtozo = a;
		a = b;
		b = segedValtozo;
	}

	cout << a << "," << b << "," << c << endl;
}

int main()
{
	int x, y, z;
	cout << "x"; cin >> x;
	cout << "y"; cin >> y;
	cout << "z"; cin >> z;
	sortNumb(x, y, z);
}