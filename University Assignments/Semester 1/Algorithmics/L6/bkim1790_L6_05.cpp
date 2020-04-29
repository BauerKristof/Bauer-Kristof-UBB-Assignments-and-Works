/*
Bauer Kristof
511
Egy n  n méretű sakktáblán az (x, y) helyen található egy futár és az (x0, y0) helyen egy ló. A lónak el kell jutnia erről a helyről az (x1, y1) helyre, anélkül, hogy egy bizonyos négyzetre többször lépne illetve, hogy olyan helyen állna meg, ahonnan a futár kiütheti. Írjuk ki a ló útvonalait! A ló nem ütheti le a futárt!

*/

#include <iostream>
#include <fstream>


using namespace std;

struct bejart 
{
	int i;
	int j;
};

bejart elemek[100];

int n, futi, futj, loi, loj, celi, celj;
int matrix[100][100];

int sor[] = { 1,1,-1,-1,2,2,-2,-2 };
int oszlop[] = {2,-2,2,-2,1,-1,1,-1};


void beolvas()
{
	ifstream file;
	file.open("bkim1790_L6_05.txt");

	if (file.is_open())
	{
		file >> n;
		file >> futi >> futj;
		file >> loi >> loj;
		file >> celi >> celj;
	}


}

void nullaz()
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}



void futar()
{
	for (int i = 1; i <=n; i++) 
	{
		for (int j = 1; j<=n; j++) 
		{
			if (i + j == futi + futj) matrix[i][j] = 1;
			if (n - i + j == n - futi + futj) matrix[i][j] = 1;
		}
	}
}

bool jo(int x, int y)
{
	if (x <=0 || y <=0 || x > n || y > n)
	{
		return false;
	}
	else return true;
}

void kiirat(int m)
{
	for (int l = 1; l <= m; l++)
	{
		cout << elemek[l].i << " " << elemek[l].j << endl;
	}
	cout << endl;
}

void back(int x, int y, int k) 
{
	if ((x == celi) && (y == celj)) 
	{
		kiirat(k);
	}
	else 
	{
		matrix[x][y] = 1;
		for (int i = 0; i <8; i++) 
		{
			x = x+ sor[i];
			y = y+ oszlop[i];

			if ( (matrix[x][y] == 0) && (jo(x,y)==true) )
			{
				elemek[k].i = x;
				elemek[k].j = y;
				back(x, y, k + 1);
			}
			x = x - sor[i];
			y = y - oszlop[i];
		}
		matrix[x][y] = 0;
		
	}
}


int main()
{
	beolvas();
	nullaz();
	futar();

	int lepes = 1;
	matrix[loi][loj] = 1;
	
	back(loi, loj, lepes);
	system("pause");

	return 0;
}
