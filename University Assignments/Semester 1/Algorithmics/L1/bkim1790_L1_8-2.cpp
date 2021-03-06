// bkim1790_L1_8.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Számítsuk ki, hány napot éltünk a mai nappal bezárólag!
*/


#include "pch.h"
#include <iostream>

using namespace std;

int szokoEv(int a, int b);
int calcHonap(int honap);
void calcOssz(int elsoE, int elsoH, int elsoN, int masodikE, int masodikH, int masodikN);


int main()
{
	int elsoEv, elsoHonap, elsoNap,
	masodikEv, masodikHonap, masodikNap;

	cout << "Add meg az elso datumot (1999 05 04 pl)" << endl;
	cin >> elsoEv >> elsoHonap >> elsoNap;

	cout << "Add meg a masodik datumot (2011 06 04 pl)" << endl;
	cin >> masodikEv >> masodikHonap >> masodikNap;

	calcOssz(elsoEv, elsoHonap, elsoNap, masodikEv, masodikHonap, masodikNap);




	return 0;
}


int calcHonap(int honap)
{

	int napokHonapban[] = {31,28,31,30,31,30,31,31,30,31,30,31 };
	int sum = 0;

	for (int i = 0; i < honap - 1; i++)
	{
		sum = sum + napokHonapban[i];
	}

	return sum;

}

int szokoEv(int e, int m)
{
	double x, y;
	x = e / 4 - e / 100 + e / 400;
	y = m / 4 - m / 100 + m / 400;

	if (((e % 4 == 0) && (e % 100 != 0)) || (e % 400 == 0))
	{
		return y - x + 1;
	}

	else return y - x;

}


void calcOssz(int elsoE, int elsoH, int elsoN, int masodikE, int masodikH, int masodikN)
{
	int osszEv = 0;
	int osszHonap = 0;
	osszEv = (masodikE - elsoE) * 365 + szokoEv(elsoE, masodikE);
	osszHonap = calcHonap(masodikH) - calcHonap(elsoH);
	int osszNap = 1 + masodikN - elsoN + osszHonap + osszEv;

	cout << osszNap<< " nap"<<endl;

}