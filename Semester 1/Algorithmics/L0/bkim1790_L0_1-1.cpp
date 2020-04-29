// bkim1790_L0_1.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*Hallgató neve: Bauer Kristóf
Csoport:511
Írjatok fel egy számot négyzetszámok összegeként.*/


#include "pch.h"
#include <iostream>

using namespace std;

void negyzetSzam(int x);

int main()
{
	int x;
	cout << "x";
	cin >> x;
	negyzetSzam(x);
}

void negyzetSzam(int x)
{
	int y = 0;
	while (x > 0)
	{
		y = trunc(sqrt(x));
		cout << y << "^2 ";
		x = int(x - y * y);
	}
}
