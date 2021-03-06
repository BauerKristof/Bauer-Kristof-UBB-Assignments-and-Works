// bkim1790_L1_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Egy téglalap alakú kertet drótkerítéssel szeretnénk bekeríteni. Ismerjük a kert hosszát, szélességét, valamint a rendelkezésre 
álló drót hosszát. Számítsuk ki mennyi drót marad a kert bekerítése után, illetve mennyi drót szükséges még a kert bekerítéséhez.

*/

#include "pch.h"
#include <iostream>

using namespace std;

void drotSzamol(double h, double sz,double d)
{
	double kerulet = 2 * (h + sz);
	if (kerulet > d)
	{
		cout << kerulet - d << " hosszusagu drot szukseges meg" << endl;
	}
	else
	{
		cout << d - kerulet << " hosszusagu drot maradt" << endl;
	}
}

int main()
{
	double h, sz, d;

	cout << "h=" << endl;
	cin >> h;
	cout << "sz=" << endl;
	cin >> sz;
	cout << "d=" << endl;
	cin >> d;

	drotSzamol(h, sz, d);
	return 0;
}
