// bkim1790_L1_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Számítsuk ki egy háromszög területét, ha ismerjük oldalainak a hosszát!
*/

#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;




void haromszogTerulet(double a, double b, double c)
{

	double p, terulet;
	p = (a + b + c) / 2;
	terulet = sqrt(p*(p - a)*(p - b)*(p - c));
	cout << "A haromszog terulete: " << terulet;

}



int main()
{
	double a, b, c;
	cout << "a";
	cin >> a;
	cout << "b";
	cin >> b;
	cout << "c";
	cin >> c;

	haromszogTerulet(a, b, c);
}