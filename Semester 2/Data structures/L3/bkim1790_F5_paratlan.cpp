/*Nev:Bauer Kristof
Csoport:511
Azonostio:bkim1790
Feladat:F5_Paratlan*/

#include <iostream>
#include <fstream>

using namespace std;

ifstream file("tomb.txt");
ofstream file2("output.txt");

int cserekSz = 0;

class Kupac
{
	int n;
	int* kupac;

	int bal_gyerek(int i);
	int jobb_gyerek(int i);
	void kupacol(int i);

public:
	Kupac(int N, int* t);
	~Kupac();
	int torol_maximum();
};

Kupac::Kupac(int N, int* t)
{
	n = N;
	kupac = new int[N];
	for (int i = 0; i < N; i++)
	{
		kupac[i] = t[i];
	}
	for (int i = N / 2; i >= 0; i--)
	{
		kupacol(i);
	}
}

Kupac::~Kupac()
{
	delete[] kupac;
}

int Kupac::bal_gyerek(int i)
{
	int poz = 2 * i + 1;
	if (poz < n)
	{
		return poz;
	}
	else 
	{ 
		return -1; 
	}
}

int Kupac::jobb_gyerek(int i)
{
	int poz = 2 * i + 2;
	if (poz < n)
	{
		return poz;
	}
	else
	{
		return -1;
	}

}

void Kupac::kupacol(int i)
{
	int max = i;
	int bal = bal_gyerek(i);
	int jobb = jobb_gyerek(i);

	if ((kupac[bal] > kupac[max]) && (bal != -1))
	{
		max = bal;
	}

	if ((kupac[jobb] > kupac[max]) && (jobb != -1))
	{
		max = jobb;
	}

	if (max != i)
	{
		cserekSz++;
			
		int csere = kupac[i];
		kupac[i] = kupac[max];
		kupac[max] = csere;

		kupacol(max);
	}
}


int Kupac::torol_maximum()
{
	int csere = kupac[0];
	kupac[0] = kupac[n - 1];
	kupac[n - 1] = csere;
	n--;
	kupacol(0);
	return kupac[n];
}

void KupacRendezes(int n, int*& t)
{
	Kupac heap(n,t);

	for (int i = n - 1; i >= 0; i--)
	{
		t[i] = heap.torol_maximum();
	}
}

void kiir(int x[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << x[i] << endl;
		file2 << x[i] << endl;
	}
}


int main()
{
	if (file.is_open())
	{
		int* szamokTomb;
		int n;
		file >> n;
		szamokTomb = new int[n];
		
		for (int i = 0; i < n; i++)
		{
			file >> szamokTomb[i];
		}

		KupacRendezes(n,szamokTomb);
		kiir(szamokTomb, n);

		cout<< "A rendezesek soran hasznalt cserek szama= " << cserekSz << endl;
		file2 << "A rendezesek soran hasznalt cserek szama= " << cserekSz << endl;
	}

	system("pause");
	return 0;
}