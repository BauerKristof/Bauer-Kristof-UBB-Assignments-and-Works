#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

int const maxDim = 200;
int const maxTav = INT_MAX;

struct csp
{
	int x, y;
};

void beolvas(int & n, int t[][maxDim]) 
{
	ifstream file;
	file.open("graf.txt");
	if (file.is_open())
	{
		n = 0;
		csp szamTomb[200];
		int sorszam, X, Y;
		while (file >> sorszam >> X >> Y)
		{
			szamTomb[sorszam].x = X;
			szamTomb[sorszam].y = Y;
		}

		n = sorszam;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				t[i][j] = 0;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				t[i][j] = sqrt((szamTomb[j].x - szamTomb[i].x)*(szamTomb[j].x - szamTomb[i].x) + (szamTomb[j].y - szamTomb[i].y)*(szamTomb[j].y - szamTomb[i].y));
				t[j][i] = sqrt((szamTomb[j].x - szamTomb[i].x)*(szamTomb[j].x - szamTomb[i].x) + (szamTomb[j].y - szamTomb[i].y)*(szamTomb[j].y - szamTomb[i].y));
			}
		}

	}
}

int legkozelebbi(int i, int n, bool latogatott[], int t[][maxDim])
{
	int minimumIndex; //i-hez legkozelebbi csomopont ami meg nem latogatott
	int minimumTavolsag = maxTav;
	for (int j = 1; j <= n; j++)
		if (latogatott[j] && t[i][j] < minimumTavolsag) 
		{
			minimumTavolsag = t[i][j];
			minimumIndex = j;
		}
	return minimumIndex;
}

int korHossza(int cspvaros, int n, bool latogatott[], int t[][maxDim], int kor[]) 
{
	int tav;

	for (int i = 1; i <= n; i++)
	{
		latogatott[i] = true;
	}

	kor[1] = cspvaros;    					
	latogatott[cspvaros] = false;				 
	tav = 0;
	
	for (int i = 2; i <= n; i++) 
	{
		kor[i] = legkozelebbi(kor[i - 1], n, latogatott, t);
		latogatott[kor[i]] = false;
		//ADD HOSSZA A KOV.VAROS HOSSZAT A KORTAVHOZ!!!!
		tav = tav + t[kor[i - 1]][kor[i]];
	}
	return tav + t[kor[n]][cspvaros]; 
}

int legrovidebbHamilton(int n, bool megNincs[], int t[][maxDim], int minKor[])
{

	int tav;
	int minTav = maxTav;
	int kor[maxDim];

	//MINDEN csp-ra megnez kor!!!
	for (int k = 1; k <= n; k++) {	
		tav = korHossza(k, n, megNincs, t, kor);
		if (tav < minTav) {
			minTav = tav;					
			for (int i = 1; i <= n; i++)			      //megjegyez minutas kor
				minKor[i] = kor[i];
		}
	}
	return minTav;
}

void kiIr(int n, int minTav, int minKor[]) 
{
	cout << "A legrovidebb kor hossza = " << minTav;
	cout << " amely athalad a ";
	for (int k = 1; k <= n; k++)
		cout << minKor[k] << " ";
	cout << minKor[1] << " varosokon. " << endl;
}

int main() {

	int n, minTav;
	int t[maxDim][maxDim]; 
	int minKor[maxDim];
	bool megNincs[maxDim];

	beolvas(n, t);
	minTav = legrovidebbHamilton(n, megNincs, t, minKor);
	kiIr(n, minTav, minKor);
	system("pause");
}