/*
Nev:Bauer Kristof
Csoport:511
*/

#include <iostream>
#include "NagyEgesz.h"
#include <vector>

using namespace std;

NagyEgesz::NagyEgesz() 
{
	szam = new int[1];
	N = 1;
	EloJel = 1;
	szam[0] = 0;
}
NagyEgesz::NagyEgesz(int elojel, int n, const int* szamjegyek) 
{
	EloJel = elojel;
	N = n;
	szam = new int[N];

	for (int i = 0; i < N; i++)
	{

		szam[i] = szamjegyek[i];
	}
}

NagyEgesz::NagyEgesz(const NagyEgesz &n) 
{
	EloJel = n.EloJel;
	N = n.N;
	szam = new int[N];
	for (int i = 0; i < n.N; i++)
	{
		szam[i] = n.szam[i];
	}
}

NagyEgesz::~NagyEgesz() 
{
	delete[] szam;
}

void NagyEgesz::kiir() const
{
	if (EloJel == 1)
	{
		cout << "+";
	}
	else
	{
		cout << "-";
	}

	for (int i = 0; i < N; i++)
	{
		cout << szam[i];
	}
	cout << endl;
}


bool operator>(const NagyEgesz &elsoSzam, const NagyEgesz &masodikSzam)
{
	if (elsoSzam.EloJel > masodikSzam.EloJel) { return true; }
	else if (elsoSzam.EloJel < masodikSzam.EloJel) { return false; }
	else
	{
		if ((elsoSzam.EloJel > 0) && (masodikSzam.EloJel > 0))
		{
			if (elsoSzam.N > masodikSzam.N) { return true; }
			else if (elsoSzam.N < masodikSzam.N) { return false; }
			else ////ha megyezik a szamjegyeik szama
			{
				int i = 0;
				while ((i < elsoSzam.N))
				{
					if (elsoSzam.szam[i] > masodikSzam.szam[i])
					{
						return true;
					}
					else
					{
						if (elsoSzam.szam[i] < masodikSzam.szam[i])
						{
							return false;
						}
					}
					i++;
				}
				return true;

			}
		}
		else
		{
			int i = 0;
			while (i < elsoSzam.N) 
			{
				if (elsoSzam.szam[i] < masodikSzam.szam[i]) 
				{
					return true;
				}
				else 
				{
					if (elsoSzam.szam[i] > masodikSzam.szam[i]) 
					{
						return false;
					}
				}
				i++;
			}
			return true;
		}
	}
}

void NagyEgesz::kerekitSzamra(NagyEgesz &x)
{
	int i = 0;
	while ((i < x.N) && (x.szam[i] == 0))
	{
		i++;
	}

	if (i < x.N)
	{
	
		int *csere = new int[x.N - i];
		int db = 0;

		while (i < x.N)
		{
			csere[db] = x.szam[i];
			db++;
			i++;
		}
		
		delete[] x.szam;
		x.N = db;
		x.szam = new int[db];

		for (int i=0; i < x.N; i++)
		{
			x.szam[i] = csere[i];
		}


	}
	else
	{
		delete[] x.szam;	
		x.EloJel = 1;
		x.N = 1;
		x.szam = new int[1];
		x.szam[0] = 0;
	}
}

NagyEgesz NagyEgesz::osszead(const NagyEgesz& x)
{
	int c = 0;

	int *elsoszam, *masodikszam;
	elsoszam = new int[N];
	masodikszam = new int[x.N];

	for (int i = N - 1; i >= 0; i--)
	{
		elsoszam[c] = szam[i];
		c++;
	}

	c = 0;
	for (int i = x.N - 1; i >= 0; i--)
	{
		masodikszam[c] = x.szam[i];
		c++;
	}

	if (((EloJel > 0) && (x.EloJel > 0)) || ((EloJel < 0) && (x.EloJel < 0)))
	{
		if (N >= x.N)
		{
			int *eredmeny = new int[N + 1];
			int maradek = 0;
			int i;
			for (i = 0; i < x.N; i++)
			{
				int reszOsseg = elsoszam[i] + masodikszam[i] + maradek;
				if (reszOsseg >= 10)
				{
					maradek = 1;
					reszOsseg -= 10;
				}
				else
				{
					maradek = 0;
				}
				eredmeny[i] = reszOsseg;
			}


			for (int i = N - 1; i >= x.N; i--)
			{
				if ((maradek == 1) && (i==x.N))
				{
					eredmeny[i] = elsoszam[i] + maradek;
					maradek = 0;
				}
				else
				{
					eredmeny[i] = elsoszam[i];
				}
			}

			int *vegeredmeny = new int[N + 1];
			int c = 0;
		
			if ((maradek == 1) && (N == x.N))
			{
				vegeredmeny[0] = 1;
				c = 1;

				for (int i = N - 1; i >= 0; i--)
				{
					vegeredmeny[c] = eredmeny[i];
					c++;
				}

				NagyEgesz vegeredmenySzam(EloJel, N+1, vegeredmeny);
				delete[] vegeredmeny;
				delete[] eredmeny;
				delete[] elsoszam;
				delete[] masodikszam;
				return vegeredmenySzam;
			}
			else
			{
				for (int i = N - 1; i >= 0; i--)
				{
					vegeredmeny[c] = eredmeny[i];
					c++;
				}

				NagyEgesz vegeredmenySzam(EloJel, N, vegeredmeny);
				delete[] vegeredmeny;
				delete[] eredmeny;
				delete[] elsoszam;
				delete[] masodikszam;
				return vegeredmenySzam;
			}
		}
		else
		{
			int *eredmeny = new int[x.N + 1];
			int maradek = 0;
			for (int i = 0; i < N; i++)
			{
				int reszOsseg = elsoszam[i] + masodikszam[i] + maradek;
				if (reszOsseg >= 10)
				{
					maradek = 1;
					reszOsseg -= 10;
				}
				else
				{
					maradek = 0;
				}
				eredmeny[i] = reszOsseg;
			}

			for (int i = x.N - 1; i >= N; i--)
			{
				eredmeny[i] = masodikszam[i];
			}


			int *vegeredmeny = new int[x.N + 1];
			int c = 0;
			for (int i = x.N - 1; i >= 0; i--)
			{
				vegeredmeny[c] = eredmeny[i];
				c++;
			}
			NagyEgesz vegeredmenySzam(x.EloJel, x.N, vegeredmeny);
			delete[] vegeredmeny;
			delete[] eredmeny;
			delete[] elsoszam;
			delete[] masodikszam;
			return vegeredmenySzam;
		}
	}


	else if (((EloJel > 0) && (x.EloJel < 0)) || ((EloJel < 0) && (x.EloJel > 0)))
	{
			if (NagyEgesz(1, N, szam) > NagyEgesz(1, x.N, x.szam))
			{
				for (int i = 0; i < x.N; i++)
				{
					if (elsoszam[i] - masodikszam[i] < 0)
					{
						elsoszam[i + 1]--;
						elsoszam[i] += 10;
					}
					elsoszam[i] -= masodikszam[i];
				}

				int* eredmeny;
				eredmeny = new int[N];

				for (int i = 0; i < N; i++)
				{
					eredmeny[i] = elsoszam[N - i - 1];
				}

				delete[] elsoszam;
				delete[] masodikszam;

				NagyEgesz vegeredmenySzam(EloJel, N, eredmeny);
				delete[] eredmeny;
				kerekitSzamra(vegeredmenySzam);
				return vegeredmenySzam;
			}
			
			else //ELSO<=MASODIK
			{
				bool ok = true; //ELSO<MASODIK ERTEKBEN
				int elo = x.EloJel;
				if (x.N == N)  //ELSO==MASODIK
				{
					int i = 0;
					while (i < N)
					{
						if (szam[i] > x.szam[i])
						{
							ok = false;
							break;
						}
						else
						{
							break;
						}
						i++;
					}

					if (ok == false) //ELSO>MASODIK
					{
						elo = EloJel;
						int *cserel = new int[x.N];
						for (int i = 0; i < x.N; i++)
						{
							cserel[i] = elsoszam[i];
							elsoszam[i] = masodikszam[i];
						}

						for (int i = 0; i < x.N; i++)
						{
							masodikszam[i] = cserel[i];
						}
						delete[] cserel;
					}
				}
			

				for (int i = 0; i < N; i++)
					{
						if (masodikszam[i] - elsoszam[i] < 0)
						{
							masodikszam[i + 1]--;
							masodikszam[i] += 10;
						}
						masodikszam[i] -= elsoszam[i];
					}

					int* eredmeny;
					eredmeny = new int[x.N];

					for (int i = 0; i < x.N; i++)
					{
						eredmeny[i] = masodikszam[x.N - i - 1];
					}

					delete[] elsoszam;
					delete[] masodikszam;
					NagyEgesz potSzam(elo, x.N, eredmeny);
					kerekitSzamra(potSzam);
					delete[] eredmeny;
					return potSzam;
			}
		}
}

NagyEgesz NagyEgesz::kivon(const NagyEgesz& x)
{
	NagyEgesz potSzam(-x.EloJel, x.N, x.szam);
	return this->osszead(potSzam);
}

NagyEgesz NagyEgesz::szoroz(const NagyEgesz& x)
{
		int sHossz1 = 0, sHossz2 = 0;
		vector<int> eredmeny(N + x.N, 0);
	
		for (int i = N - 1; i >= 0; i--)
		{
			int maradek = 0;
			sHossz2 = 0;         

			for (int j = x.N - 1; j >= 0; j--)
			{
				int ossz = szam[i]*x.szam[j] + eredmeny[sHossz1 + sHossz2] + maradek;
				maradek = ossz / 10;
				eredmeny[sHossz1 + sHossz2] = ossz % 10;
				sHossz2++;
			}

			if (maradek > 0)
			{
				eredmeny[sHossz1 + sHossz2] += maradek;
			}
			sHossz1++;
		}

		int hossz = eredmeny.size() - 1;
		while (hossz >= 0 && eredmeny[hossz] == 0)
		{
			hossz--;
		}

		if (hossz == -1)
		{
			return NagyEgesz();
		}
		else
		{
			int *segedTomb = new int[hossz + 1];
			int k = 0;
			while (hossz >= 0)
			{
				segedTomb[k] = eredmeny[hossz];
				hossz--;
				k++;
			}

			NagyEgesz potSzam(EloJel*x.EloJel, k, segedTomb);
			delete[] segedTomb;
			return potSzam;
		}
}

NagyEgesz NagyEgesz::oszt(const NagyEgesz& x)
{
	if (x.szam[0] == 0)
	{
		throw NullavalValoOsztas();
	}

	NagyEgesz osztandoSzam(1, N, szam);
	NagyEgesz osztoSzam(1, x.N, x.szam);

	bool nagyobbSzam;
	if (osztandoSzam > osztoSzam)
	{
		nagyobbSzam = true;
	}
	else
	{
		nagyobbSzam = false;
	}

	if (nagyobbSzam == false)
	{
		return NagyEgesz();
	}

	int *vegeredmeny = new int[osztandoSzam.N];
	int vSzamlalo = 0;

	for (int i = 0; i < osztandoSzam.N; i++)
	{
		vegeredmeny[i] = 0;
	}

	int k = x.N;
	NagyEgesz segedSzam;
	int *segedTomb;

	while (k <= N || nagyobbSzam)
	{
		segedTomb = new int[osztandoSzam.N];

		for (int i = 0; i < osztoSzam.N; i++)
		{
			segedTomb[i] = osztoSzam.szam[i];
		}

		for (int i = osztoSzam.N; i < osztandoSzam.N; i++)
		{
			segedTomb[i] = 0;
		}

		if (osztandoSzam.N == segedSzam.N)
		{
			delete[] segedSzam.szam;
			segedSzam.EloJel = 1;
			segedSzam.N = osztandoSzam.N - 1;
			segedSzam.szam = new int[segedSzam.N];
			for (int i = 0; i < segedSzam.N; i++)
			{
				segedSzam.szam[i] = segedTomb[i];
			}
		}
		else
		{
			segedSzam.EloJel = 1;
			segedSzam.N = osztandoSzam.N;
			delete[] segedSzam.szam;
			segedSzam.szam = new int[segedSzam.N];
			for (int i = 0; i < segedSzam.N; i++)
			{
				segedSzam.szam[i] = segedTomb[i];
			}
		}

		delete[] segedTomb;

		while (osztandoSzam > segedSzam)
		{
			NagyEgesz szamol = osztandoSzam.kivon(segedSzam);

			delete[] osztandoSzam.szam;
			osztandoSzam.EloJel = szamol.EloJel;
			osztandoSzam.N = szamol.N;
			osztandoSzam.szam = new int[osztandoSzam.N];
			for (int i = 0; i < osztandoSzam.N; i++)
			{
				osztandoSzam.szam[i] = szamol.szam[i];
			}
			vegeredmeny[vSzamlalo]++;

		}


		vSzamlalo++;
		kerekitSzamra(osztandoSzam);
		if (osztandoSzam > osztoSzam)
		{
			nagyobbSzam = true;
		}
		else
		{
			nagyobbSzam = false;
		}

		k++;
	}

	NagyEgesz seged(EloJel * x.EloJel, vSzamlalo, vegeredmeny);
	kerekitSzamra(seged);
	delete[] vegeredmeny;
	return seged;
}