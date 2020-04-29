/*
Bauer Kristof
511
7. Egy kiállítási csarnokot le fognak fedni előre gyártott műanyaglapokkal. Előbb felosztották 
a csarnok alapját négyzet alakú felületekre úgy, hogy a csarnok belsejében található oszlop pontosan egy ilyen négyzetnyi helyet foglaljon el. 
A műanyaglapok alakja olyan, hogy három ilyen négyzetet fednek majd le.
*/


#include <iostream>
#include <fstream>

using namespace std;

int n, csarnok[100][100],x,y;


void inicializal()
{
	n = pow(2, n);
	x--;
	y--;
	csarnok[x][y] = 2;
}

void beolvas()
{
	ifstream file;
	file.open("bkim1790_L7_7.txt");
	
	if (file.is_open())
	{
		file >> n;

		file >> x;
		file >> y;
		inicializal();
	}
}


void feloszt(int balx,int baly, int jobbx, int jobby)
{

	int i = balx;
	int j = baly;
	int elem = 0;
	
	while (!elem && i <= jobbx)
	{
		while  (!elem && j <= jobby)
		{
			if (csarnok[i][j] != 0)
			{
				elem = 1;
			}
			j++;
		}
		i++;
	}
	
	i--;
	j--;

	int kozepx = (balx + jobbx) / 2;
	int kozepy = (baly + jobby) / 2;

	if (kozepx >= i && kozepy >= j)
	{
	csarnok[kozepx + 1][kozepy]++;
	csarnok[kozepx][kozepy + 1]++;
	csarnok[kozepx + 1][kozepy + 1]++;

	cout << "(" << kozepx + 2 << "," << kozepy + 2 << ") ";
	cout << "(" << kozepx + 1 << "," << kozepy + 2 << ") ";
	cout << "(" << kozepx + 2 << "," << kozepy + 1 << ") ";
	cout << endl;
	}

	else if (kozepx >= i && kozepy < j) 
	{
		csarnok[kozepx + 1][kozepy + 1]++;
		csarnok[kozepx + 1][kozepy]++;
		csarnok[kozepx][kozepy]++;

		cout << "(" << kozepx + 1 << "," << kozepy + 1 << ") ";
		cout << "(" << kozepx + 2 << "," << kozepy + 1 << ") ";
		cout << "(" << kozepx + 2 << "," << kozepy + 2 << ") ";
		cout << endl;
	}

	else if (kozepx < i && kozepy < j)
	{
		csarnok[kozepx + 1][kozepy + 1]++;
		csarnok[kozepx][kozepy + 1]++;
		csarnok[kozepx][kozepy]++;

		cout << "(" << kozepx + 1 << "," << kozepy + 1 << ") ";
		cout << "(" << kozepx + 1 << "," << kozepy + 2 << ") ";
		cout << "(" << kozepx + 2 << "," << kozepy + 2 << ") ";
		cout << endl;
	}


	else if (kozepx < i && kozepy >= j) 
	{
		csarnok[kozepx + 1][kozepy + 1]++;
		csarnok[kozepx][kozepy + 1]++;
		csarnok[kozepx][kozepy]++;

		cout << "(" << kozepx + 1 << "," << kozepy + 1 << ") ";
		cout << "(" << kozepx + 1 << "," << kozepy + 2 << ") ";
		cout << "(" << kozepx + 2 << "," << kozepy + 2 << ") ";
		cout << endl;
	}
}

void illeszt(int balx, int baly, int jobbx, int jobby)
{
	if (jobbx - balx <= 1) 
	{
		feloszt(balx, baly, jobbx, jobby);
	}
	else 
	{
		feloszt(balx, baly, jobbx, jobby);

		int kozepx = (balx + jobbx) / 2;
		int kozepy = (baly + jobby) / 2;

		illeszt(balx, baly, kozepx, kozepy);
		illeszt(kozepx + 1, baly, jobbx, kozepy);
		illeszt(balx, kozepy + 1, kozepx, jobby);
		illeszt(kozepx + 1, kozepy + 1, jobbx, jobby);

	}
}

int main()
{

	beolvas();
	illeszt(0, 0, n - 1, n - 1);
	system("pause");
	return 0;
}