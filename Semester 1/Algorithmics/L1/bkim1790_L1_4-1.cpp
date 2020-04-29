// bkim1790_L1_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristóf
511
Írjunk algoritmust, amely kiszámítja egy személy ideális testsúlyát!

*/

#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

void idealisSuly(string nem, double magassag, int eletkor)
{
	double s;
	if (nem=="ferfi")
	{
		s = 50.0 + 0.75*(magassag - 150.0) + (eletkor - 20.0) / 40.0;
	}
	else if(nem=="no")
	{
		s = 0.9*(50.0 + 0.75*(magassag - 150.0) + (eletkor - 20.0) / 40.0);
	}

	cout << "Idealis testsuly: " << s;
}


int main()
{
	string nem;
	double magassag;
	int eletkor;

	cout << "nem=";
	cin >> nem;
	cout << "magassag=";
	cin >> magassag;
	cout << "eletkor=";
	cin >> eletkor;

	idealisSuly(nem, magassag, eletkor);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
