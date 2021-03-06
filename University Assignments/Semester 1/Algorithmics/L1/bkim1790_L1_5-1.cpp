// bkim1790_L1_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Írjunk algoritmust az ax2 + bx + c = 0 valós együtthatójú egyenlet megoldására!
*/

#include "pch.h"
#include <iostream>

using namespace std;

void szamolEgyenlet(double a, double b, double c)
{
	double delta;
	delta = double(pow(b, 2)) - 4 * a*c;

	if (delta < 0) {
		cout << "Nincs valos megoldas";
	}

	else
	{
		double x1 = 0.0, x2 = 0.0;
		x1 = (-b - sqrt(delta)) / (2.0 * a);
		x2 = (-b + sqrt(delta)) / (2.0 * a);

		cout << "Megoldasok: " << x1 << ", " << x2 << endl;

	}


}

int main()
{
	double a, b, c;

	cout << "a" << endl;
	cin >> a;

	cout << "b" << endl;
	cin >> b;

	cout << "c" << endl;
	cin >> c;
	szamolEgyenlet(a, b, c);
	return 0;
}
