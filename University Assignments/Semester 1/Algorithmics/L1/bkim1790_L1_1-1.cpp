// bkim1790_L1_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Adott két egész szám, cseréljük fel őket segédváltozó használata nélkül és írjuk ki az új sorrendben!*/

#include "pch.h"
#include <iostream>

using namespace std;

void felcserel(int a, int b)
{
	a = a + b;
	b = a - b;
	a = a - b;
	cout << "x=" << a << endl;
	cout << "y=" << b << endl;
}


int main()
{
	int x, y;
	cout << "x=";
	cin >> x;
	cout << "y=";
	cin >> y;
	felcserel(x, y);

	return 0;

}