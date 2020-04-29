// bkim1790_L1_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Számítsuk ki hány szökőév volt/lesz két különböző évszám között!
*/

#include "pch.h"
#include <iostream>

using namespace std;

int szokoEv(int e, int m)
{
	double x, y;
	x = e/4 - e/100 + e/400;
	y = m/4 - m/100 + m/400;
	
	if (((e % 4 == 0) && (e % 100 != 0)) || (e % 400 == 0))
	{
		return y - x + 1;
	}
	else return y - x;

}

int main()
{
	int elso, masodik;
	cout << "elso=";
	cin >> elso;

	cout << "masodik=";
	cin >> masodik;

	cout << szokoEv(elso, masodik) << " szokoev" << endl;

	return 0;
}