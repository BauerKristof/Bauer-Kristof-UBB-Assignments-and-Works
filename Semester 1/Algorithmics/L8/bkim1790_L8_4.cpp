/*
Bauer Kristof
511
Állapítsuk meg Kruskal algoritmusának egy változatával, hogy egy adott, nem irányított gráf összefüggő-e vagy sem.
*/

#include <iostream>
#include <fstream>

using namespace std;

struct el 
{
	int x;
	int y;
	float koltseg;
};

void beolvas(int & n, int & m, el elek[]) 
{
	ifstream be("bkim1790_L8_4.txt");
	be >> n;
	be >> m;

	for (int i = 1; i <= m; i++)
	{
		be >> elek[i].x;
		be >> elek[i].y;
		be >> elek[i].koltseg;
	}
}



int oszd(el x[100], int b, int j)
{
	el d;
	d.x = x[b].x;
	d.y = x[b].y;
	d.koltseg = x[b].koltseg;
	int k = b;

	while (b < j)
	{
		while ((b < j) && (x[j].koltseg >= d.koltseg))
		{
			j--;
		}

		x[k].x = x[j].x;
		x[k].y = x[j].y;
		x[k].koltseg = x[j].koltseg;
		k = j;

		while ((b < j) && (x[b].koltseg <= d.koltseg))
		{
			b++;
		}
		x[k].x = x[b].x;
		x[k].y = x[b].y;
		x[k].koltseg = x[b].koltseg;
		k = b;
	}
	x[k].x = d.x;
	x[k].y = d.y;
	x[k].koltseg = d.koltseg;
	return k;

}

void quick(el x[100], int bal, int jobb)
{
	int kozep;
	if (bal < jobb)
	{
		kozep = oszd(x, bal, jobb);
		quick(x, bal, kozep - 1);
		quick(x, kozep + 1, jobb);
	}
}


bool Kruskal(int n, int m, el elek[], int kivalasztva[], float & osszKoltseg) 
{

	int L[20];							
	int id;

	for (int i = 1; i <= n; i++)
		L[i] = i;

	int i = 0;
	osszKoltseg = 0;

	int j = 1;
	while ((j <= m) && (i < n - 1))
	{
		if (L[elek[j].x] != L[elek[j].y]) 
		{
			i++;
			kivalasztva[i] = j;  
			osszKoltseg += elek[j].koltseg;
			id = L[elek[j].y];
			for (int k = 1; k <= n; k++)
				if (L[k] == id)
					L[k] = L[elek[j].x];
		}
		j++;
	}
	return i == n - 1;
}

int main() 
{

	int n, m;						
	el elek[20];				
	int kivalasztva[20];		
	float osszKoltseg;

	beolvas(n, m, elek);
	quick(elek, 1, m);
	if (Kruskal(n, m, elek, kivalasztva, osszKoltseg))
		cout << "A graf osszefuggo" << endl;
	else
		cout << "Az eredeti graf nem osszefuggo!" << endl;
	system("pause");

}

