/*
Bauer Kristof
511
Adott n programozó fizetése. Válogassuk szét őket a fizetésük alapján. Az első csoportba azok kerülnek, akiknek a fizetésük nagyobb mint 1000 EUR, a másodikba a megmaradtak közül azok, akiknek a fizetése nagyobb mint 700 EUR, a harmadikban maradnak a többiek (a sorrend nem fontos). Törekedjünk egyetlen tömbbel dolgozni.
*/


#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int fizetesek[], int &n)
{
	ifstream file;
	file.open("bkim1790_L4_4.txt");

	if (file.is_open())
	{
		file >> n;

		for (int i = 0; i < n; i++)
		{
			file >> fizetesek[i];
			cout << fizetesek[i] << " ";
		}
		cout << endl;
	}
}

void kiir(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
		arr[i] = -1;
	}
	cout << endl;
}

void szetvalogat(int x[], int n, int &db, int tulajd) 
{
	int e = 0;
	int u = n-1;
	int seged = x[e];

	while (e < u) 
	{
		while ((e < u) && (x[u]<tulajd)) 
		{
			u--;
		}

		if (e < u)
		{
			x[e] = x[u];
			e++;
		}

		while ((e < u) && (x[e]>=tulajd))
			{
			e++;
			}

		if (e < u) 
			{
				x[u] = x[e];
				u--;
			}
		}

	x[e] = seged;

	if (x[e]>=tulajd)
		db = e + 1;
	else
		db = e;
}

int main()
{
	int fiz[200], n,brk,meddig;


	beolvas(fiz, n);
	szetvalogat(fiz, n, meddig, 1000);
	kiir(fiz, meddig);
	szetvalogat(fiz, n, meddig, 700);
	kiir(fiz, meddig);
	szetvalogat(fiz, n, meddig, 0);
	kiir(fiz, meddig);
	cin >> brk;
	return 0;
}