/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

struct lista
{
	int elemszam = 0;
	int elemek[9];
};


void beolvas(int &m, int &n, int mat[][11], int ertek[][11])
{
	ifstream file;
	file.open("be.txt");

	if (file.is_open())
	{
		file >> m;
		int csp1, csp2, ert;

		while (file >> csp1 >> csp2 >> ert)
		{
			++n;
			//		cout << "N= " << n << " CSP1= " << csp1 << " CSP2= " << csp2 << " ERTEK= "<<ert<<endl;
			ertek[csp1][csp2] = ert;
			ertek[csp2][csp1] = ert;
			mat[csp1][csp2] = 1;
			mat[csp2][csp1] = 1;

		}
		cout << endl;
	}
}

void alakit_szom_inc(int id[][11], int mat[][11], int m, int n)
{
	int el = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (i > j)
			{
				if (mat[i][j] == 1)
				{
					++el;
					id[i][el] = 1;
					id[j][el] = 1;
				}
			}
		}
	}
}

void alakit_inc_szom(int id[][11], int szomszed[][11], int m, int n)
{
	int el1 = 0, el2 = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{

			if (id[j][i] == 1)
			{
				if (el1 == 0)
				{
					el1 = j;
				}
				else { el2 = j; }
			}
		}
		szomszed[el1][el2] = 1;
		szomszed[el2][el1] = 1;
		el1 = 0;
		el2 = 0;
	}
}

void alakit_szom_list(int szomszed[][11], lista list[], int m)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (szomszed[i][j] == 1)
			{
				list[i].elemszam = list[i].elemszam + 1;
				list[i].elemek[list[i].elemszam] = j;
			}
		}
	}

}

void alakit_list_szom(lista list[], int szomszed[][11], int m)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= list[i].elemszam; j++)
		{
			szomszed[i][list[i].elemek[j]] = 1;
		}
	}
}


void kiirlist(lista list[], int m)
{
	cout << endl;
	for (int i = 1; i <= m; i++)
	{
		cout << i << ": ";

		for (int j = 1; j <= list[i].elemszam; j++)
		{
			cout << list[i].elemek[j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void kiir(int mat[][11], int m, int n)
{
	cout << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void inic(int mat[][11], int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			mat[i][j] = 0;
		}
	}
}

void regularis(int graf[][11], int m)
{
	int r = 0, foksz = 0;
	bool regularis = true;

	for (int i = 1; i <= m; i++)
	{
		if (graf[1][i] == 1) { ++r; }
	}

	for (int i = 2; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (graf[i][j] == 1)
			{
				foksz++;
			}
		}
		if (foksz != r) { regularis = false; }
		foksz = 0;
	}

	if (regularis == false)
	{
		cout << "A graf nem regularis" << endl;
	}
	else
	{
		cout << "A graf regularis" << endl;
	}
}

void izolalt(int graf[][11], int m)
{
	int foksz = 0;
	int db = 0;
	cout << "Az izolalt csomopontok a grafban: ";

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (graf[i][j] == 1)
			{
				foksz++;
			}
		}
		
		if (foksz == 0) 
		{
			cout << i << " "; 
			db++;
		}
		foksz = 0;
	}

	if (db == 0)
	{
		cout << "Nincs egy izolalt pont sem" << endl;
	}
}

void warshall(int ert[][11], int tavolsagi[][11], int m)
{
	cout << endl;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			tavolsagi[i][j] = ert[i][j];
		}
	}

	int min = INT_MAX / 2;
	for (int k = 1; k <= m; k++)
	{
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (tavolsagi[i][j] < (tavolsagi[i][k] + tavolsagi[k][j]))
				{
					min = tavolsagi[i][j];
				}
				else
				{
					min = tavolsagi[i][k] + tavolsagi[k][j];

				}

				tavolsagi[i][j] = min;

			}
		}
	}

	cout << "Tavolsagi matrix" << endl;
	kiir(tavolsagi, m, m);

}

void osszefuggo(int tavolsagi[][11], int m)
{
	bool osszefuggo = true;

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (tavolsagi[i][j] == INT_MAX / 2)
			{
				osszefuggo = false;
			}
		}
	}

	if (osszefuggo == true)
	{
		cout << "A graf osszefuggo" << endl;
	}
	else
	{
		cout << "A graf nem osszefugoo" << endl;
	}
}



int main()
{
	int szomszed[11][11], id[11][11], ertek[11][11], tavolsagi[11][11];

	int m = 0, n = 0;

	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			szomszed[i][j] = 0;
			id[i][j] = 0;

			if (i == j)
			{
				ertek[i][j] = 0;
			}
			else  ertek[i][j] = INT_MAX / 2;
		}
	}

	beolvas(m, n, szomszed, ertek);
	//cout << "Csomopontok szama= " << m << " Elek szama= " << n << endl;
	cout << "Az ertek matrix";
	kiir(ertek, m, m);
	cout << "Szomszedsagi matrix";
	kiir(szomszed, m, m);

	cout << "Szomszedsagi matrix->Incidencia matrix";
	alakit_szom_inc(id, szomszed, m, n);
	kiir(id, m, n);

	cout << "Incidencia matrix -> Szomszedsagi matrix";
	inic(szomszed, m, m);
	alakit_inc_szom(id, szomszed, m, n);
	kiir(szomszed, m, m);

	cout << "Szomszedsagi matrix -> Lista";
	lista *list = new lista[m + 1];
	alakit_szom_list(szomszed, list, m);
	kiirlist(list, m);

	cout << "Lista -> Szomszedsagi matrix";
	inic(szomszed, m, m);
	alakit_list_szom(list, szomszed, m);
	kiir(szomszed, m, m);
	delete[] list;

	regularis(szomszed, m);
	izolalt(szomszed, m);
	warshall(ertek, tavolsagi, m);
	osszefuggo(tavolsagi, m);

	system("pause");
	return 0;
}