/*
Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790
 */
#include <iostream>
#include <string.h>
#include <queue>
#include <fstream>
#include <limits>

using namespace std;

int forras, nyelo;


class FordFulkerson
{
private:
	int n;
	int graf[10][10];

	bool bfs(int potGraf[][10], int s, int t, int szulo[])
	{
		bool lat[10];
		for (int i = 1; i <= n; i++)
		{
			lat[i] = 0;
		}

		queue <int> q;
		q.push(s);
		lat[s] = true;
		szulo[s] = -1;

		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int v = 1; v <= n; v++)
			{
				if (lat[v] == false && potGraf[u][v] > 0)
				{
					q.push(v);
					szulo[v] = u;
					lat[v] = true;
				}
			}
		}
		return (lat[t] == true);
	}

	void dfs(int potGraf[10][10], int s, bool lat[])
	{
		lat[s] = true;
		for (int i = 1; i <= n; i++)
		{
			if (potGraf[s][i] && !lat[i])
			{
				dfs(potGraf, i, lat);
			}
		}
	}

public:
	FordFulkerson();
	int fordFulkerson(int s, int t);
    void minVagat(int s, int t);
	void kiir()
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				cout << graf[i][j] << " ";
			}cout << endl;
		}
		cout << endl;
	}
	
};

FordFulkerson::FordFulkerson()
{
	ifstream file;
	file.open("graf.txt");
	if (file.is_open())
	{
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				graf[i][j] = 0;
			}
		}

		file >> n;
		file >> forras >> nyelo;

		int csp1, csp2, ert;
		while (file >> csp1 >> csp2 >> ert)
		{
			graf[csp1][csp2] = ert;
		}
	}
}

int FordFulkerson::fordFulkerson(int s, int t)
{
	int u, v;
	int potGraf[10][10];
	for (u = 1; u <= n; u++)
	{
		for (v = 1; v <= n; v++)
		{
			potGraf[u][v] = graf[u][v];
		}
	}
	int szulo[10];
	int max_folyam = 0;

    while (bfs(potGraf,s, t, szulo))
	{
		int ut_folyam = INT_MAX;
		for (v = t; v != s; v = szulo[v])
		{
			u = szulo[v];
			ut_folyam = min(ut_folyam, potGraf[u][v]);
		}
		for (v = t; v != s; v = szulo[v])
		{
			u = szulo[v];
			potGraf[u][v] -= ut_folyam;
			potGraf[v][u] += ut_folyam;
		}
		max_folyam += ut_folyam;
	}
	return max_folyam;
}

void FordFulkerson::minVagat(int s, int t)
{
	int u, v;
	int potGraf[10][10];
	for (u = 1; u <= n; u++)
	{
		for (v = 1; v <= n; v++)
			potGraf[u][v] = graf[u][v];
	}

	int szulo[10];
	while (bfs(potGraf, s, t, szulo))
	{
		int ut_folyam = INT_MAX;
		for (v = t; v != s; v = szulo[v])
		{
			u = szulo[v];
			ut_folyam = min(ut_folyam, potGraf[u][v]);
		}
		for (v = t; v != s; v = szulo[v])
		{
			u = szulo[v];
			potGraf[u][v] -= ut_folyam;
			potGraf[v][u] += ut_folyam;
		}
	}

	bool lat[10];
	for (int i = 1; i <= n; i++)
	{
		lat[i] = 0;
	}

	dfs(potGraf, s, lat);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (lat[i] && !lat[j] && graf[i][j])
				cout << i << "->" << j << endl;
		}
	}
	return;
}


int main()
{
	FordFulkerson grafalg;
	grafalg.kiir();
	cout << "A maximalis folyam= " << grafalg.fordFulkerson(forras, nyelo) << endl;
	cout<< "A minimalis vagat "<<endl;
	grafalg.minVagat(forras, nyelo);
	system("pause");
	return 0;

}