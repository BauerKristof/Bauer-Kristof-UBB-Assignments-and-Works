/*
Nev: Bauer Kristof
Csoport: 511
*/

#include<iostream> 
#include <list> 
#include <fstream>

using namespace std;

class Graf
{
	list<int> *szom;
	bool **tl;
	int V;
	void MBE(int u, int v);

public:
	Graf(int K);
	void SZB(int s, int k);
	void hozzadEl(int v, int w);
	void tranzLezar();

};

Graf::Graf(int K)
{
	V = K;
	szom = new list<int>[V];

	tl = new bool*[V];
	for (int i = 0; i < V; i++)
	{
		tl[i] = new bool[V];
		memset(tl[i], false, V * sizeof(bool));
	}
}


void Graf::SZB(int s, int k)
{

	bool *latogatott = new bool[V];
	for (int i = 0; i < V; i++)
		latogatott[i] = false;

	list<int> queue;

	latogatott[s] = true;
	queue.push_back(s);

	
	list<int>::iterator i;
	int db = 0;
	while (!queue.empty())
	{
		s = queue.front();
		queue.pop_front();

	
		for (i = szom[s].begin(); i != szom[s].end(); i++)
		{
			if (!latogatott[*i])
			{
				latogatott[*i] = true;
				queue.push_back(*i);
			}
		}

		if (db == k)
		{
			cout << "A kezdopont " << k << ". szomszedja: " << s << endl;
		}

		db++;
	}

	if (db<k)
	{
		cout << "A kezdopontnak nincs " << k << ". szomszedja" << endl;
	}
}


void Graf::MBE(int s, int v)
{
	tl[s][v] = true;

	list<int>::iterator i;
	for (i = szom[v].begin(); i != szom[v].end(); ++i)
		if (tl[s][*i] == false)
			MBE(s, *i);
}

void Graf::tranzLezar()
{
	
	for (int i = 0; i < V; i++)
		MBE(i, i);

	for (int i = 0; i < V-1; i++)
	{
		for (int j = 0; j < V-1; j++)
			cout << tl[i][j] << " ";
		cout << endl;
	}
}

void Graf::hozzadEl(int v, int w)
{
	szom[v].push_back(w);
}

int main()
{
	int n,k;
	ifstream file;
	file.open("graf.txt");
	
	if (file.is_open())
	{
		file >> n;
		Graf g(n+1);
		int csp1, csp2;

		while (file >> csp1 >> csp2)
		{
			cout << csp1 << " " << csp2 << endl;
			g.hozzadEl(csp1, csp2);
		}

		int kezdopont;
		cout << "Valaszd ki a kezdopontot a bejarashoz" << endl;
		cin >> kezdopont;

		cout << "Add meg a k-adik ismerost" << endl;
		cin >> k;
		//a alpont
		g.SZB(kezdopont, k);

		//b. alpont
		cout << endl << "A tranzitiv lezaras matrixa" << endl;
		g.tranzLezar();
	}
	system("pause");
	return 0;
}
