/*Bauer Kristof
511
Egy tolvaj betört egy hentesüzletbe, ahol n áru közül válogat. 
Minden árunak ismeri a súlyát és az értékét. Mivel a hátizsákjába legtöbb S súly fér, szeretne úgy válogatni,
hogy a nyeresége maximális legyen. (Ha egy áru nem fér be egészében a hátizsákba, a tolvaj nem vághat le belőle.)
*/

#include <iostream>
#include <fstream>

using namespace std;

struct targy
{
	float suly, ertek,egysegar;
	int sorszam;
};


void beolvas(int & n, targy aru[], float & S) 
{
	ifstream be("bkim1790_L8_7.txt");
	be >> n>> S;
	for (int i = 1; i <= n; i++) 
	{
		be >> aru[i].ertek >> aru[i].suly;
		aru[i].sorszam = i;
		aru[i].egysegar=aru[i].ertek / aru[i].suly;
	}
}

void valogat(int n, targy aru[], float S) 
{
	float osszsuly= 0;	

	int i = 1;
	while ((i <= n) and (osszsuly <= S)) 
	{
		if (aru[i].suly+osszsuly <= S) 
		{
			cout << aru[i].sorszam << " ";
		   osszsuly += aru[i].suly;
		}
		i++; 						
	}
}


int oszd(targy x[100], int b, int j)
{
	targy d;
	d.suly = x[b].suly;
	d.ertek = x[b].ertek;
	d.egysegar = x[b].egysegar;
	d.sorszam = x[b].sorszam;
	int k = b;

	while (b < j)
	{
		while ((b < j) && (x[j].egysegar <= d.egysegar))
		{
			j--;
		}

		x[k].suly = x[j].suly;
		x[k].ertek = x[j].ertek;
		x[k].egysegar = x[j].egysegar;
		x[k].sorszam = x[j].sorszam;
		k = j;

		while ((b < j) && (x[b].egysegar >= d.egysegar))
		{
			b++;
		}
		x[k].suly = x[b].suly;
		x[k].ertek = x[b].ertek;
		x[k].egysegar = x[b].egysegar;
		x[k].sorszam = x[b].sorszam;
		k = b;
	}
	x[k].suly = d.suly;
	x[k].ertek = d.ertek;
	x[k].egysegar = d.egysegar;
	x[k].sorszam = d.sorszam;
	return k;

}

void quick(targy x[100], int bal, int jobb)
{
	int kozep;
	if (bal < jobb)
	{
		kozep = oszd(x, bal, jobb);
		quick(x, bal, kozep - 1);
		quick(x, kozep + 1, jobb);
	}
}


int main() 
{
	targy aru[20];
	int n;
	float S;


	beolvas(n, aru, S);
	quick(aru, 1, n);
	valogat(n, aru, S);

	system("pause");
	return 0;
}
