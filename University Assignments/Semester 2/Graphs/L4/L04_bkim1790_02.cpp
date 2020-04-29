/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include <string>
#include <fstream>
#include <limits>


using namespace std;

struct csomopont
{
	char kar;
	int gyakorisag;
	int bal, jobb,os;
	char hufkod[256]; 
};       

class HuffMan
{
	csomopont fa[511];
	int levelek;
	int ord[256][2]; //rendezeskor hasznalat segedtomb
	int freqs[256]; //karakterek gyakorisaga


public:
	HuffMan();
	void beOlvas();
	void huffmanSzamol();
	void kiIr();

};

HuffMan::HuffMan()
{
	for (int i = 0; i < 256; i++)
	{
		freqs[i] = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			fa[i].hufkod[j] = '\0';
		}
	}
}

void HuffMan::beOlvas()
{  
	ifstream file;
	file.open("graf.txt");


	if (file.is_open())
	{

		char c;
		while (file >> c)
		{ 
			freqs[int(c)]++;
		}
	}
}

void HuffMan::huffmanSzamol()
{
	levelek = 0;
	for (int i = 0; i < 256; i++)
	{
		if (freqs[i])
		{
			fa[levelek].kar = i;
			fa[levelek].gyakorisag = freqs[i];
			fa[levelek].bal = -1;
			fa[levelek].jobb = -1;
			fa[levelek].os = -1;
			levelek++;
		}
	}
	
	for (int i = levelek; i < 2 * levelek - 1; i++)
	{
		fa[i].os = -1;
	}


	int min1, min2;
	int glmin;


	for (int i = 0; i < levelek - 1; i++)
	{
		glmin = INT_MAX;

		for (int j = 0; j < levelek + i; j++)
		{
			if ((fa[j].os < 0) && (glmin > fa[j].gyakorisag))
			{
				glmin = fa[j].gyakorisag;
				min1 = j;
			}
		}

		glmin = INT_MAX;
		for (int j = 0; j < levelek + i; j++)
		{
			if ((j != min1) && (fa[j].os < 0) && (glmin > fa[j].gyakorisag))
			{
				glmin = fa[j].gyakorisag;
				min2 = j;
			}
		}
		fa[levelek + i].gyakorisag = fa[min1].gyakorisag + fa[min2].gyakorisag; //uj elem
		fa[levelek + i].bal = min1; fa[levelek + i].jobb = min2;
		fa[min1].os = levelek + i; fa[min2].os = levelek + i;
	}
}

void HuffMan::kiIr()
{
	int j, k;
	char bitkod[256];

	for (int i = 0; i < levelek; i++) //A fabol a huffman kod eloalilitasa
	{
		j = i;
		bitkod[0] = 0;

		while (fa[j].os >= 0)
		{
			k = j;
			j = fa[j].os;

			if (fa[j].bal == k)
			{
				strcat_s(bitkod, "0");
			}
			else { strcat_s(bitkod, "1"); }
		}

		k = strlen(bitkod);
		for (j = 0; j < k; j++)
		{
			fa[i].hufkod[j] = bitkod[k - 1 - j];
		}   //kod visszallitasa

		ord[i][1] = 256 * k + fa[i].kar;
		ord[i][0] = i;
	}

	for (int i = 0; i < levelek - 1; i++) //rendezes
	{
		for (j = i + 1; j < levelek; j++)
		{
			if (ord[i][1] > ord[j][1])
			{
				k = ord[i][0]; ord[i][0] = ord[j][0]; ord[j][0] = k;
				k = ord[i][1]; ord[i][1] = ord[j][1]; ord[j][1] = k;
			}
		}
	}

	for (int i = 0; i < levelek; i++)
	{
		cout << char(fa[ord[i][0]].kar) << " : " << fa[ord[i][0]].hufkod << endl;
	}

}

int main() 
{
	HuffMan kodolas;
	kodolas.beOlvas();
	kodolas.huffmanSzamol();
	kodolas.kiIr();
	system("pause");
	return 0;
}