/*
Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;


int main() 
{
	     int n;
		 int sulyozottGraf[20][20];
		 for (int i = 0; i < 20; i++)
		 {
			 for (int j = 0; j < 20; j++)
			 {
				 sulyozottGraf[i][j] = 0;
			 }
		 }

		ifstream file;
		file.open("graf.txt");
		file >> n;
		
		string line;
		while (getline(file, line))
		{
			if (line.length() != 0) { break; }
		}
		int darabSuly=1;
		int suly[30];
		
		istringstream ss(line);
		int num;
		while (ss >> num)
		{
			suly[darabSuly] = num;
			darabSuly++;
		}

		int csp1, csp2;
		for (int i = 1; i < darabSuly; i++)
		{
			file >> csp1 >> csp2;
			sulyozottGraf[csp1][csp2] = suly[i];
		}


		int earliestCompletionTime[20];
		int latestCompletionTime[20];
		int slackTime[20];
		int earliestStartTime[20];
		int latestStartTime[20];

		for (int i = 0; i <= n; i++) 
		{
			earliestCompletionTime[i] = 0; 
			for (int j = 1; j < i; j++) 
			{
				if (sulyozottGraf[j][i] != 0)
					if (earliestCompletionTime[j] + sulyozottGraf[j][i] > earliestCompletionTime[i])  
					{
						earliestCompletionTime[i] = earliestCompletionTime[j] + sulyozottGraf[j][i];
					}
			}
		}


		for (int i = 1; i <= n; i++)
		{
			earliestStartTime[i] = 0;
		}
		earliestStartTime[1] = 1;
		for (int i = 2; i <= n; i++)
		{
			earliestStartTime[i] = earliestCompletionTime[i - 1] + 1;
		}

		for (int i = n; i >= 1; i--)
			latestCompletionTime[i] = earliestCompletionTime[n]; 

		for (int i = n; i >= 1; i--) 
		{
			for (int j = 1; j < i; j++)
			{
				if (sulyozottGraf[j][i] != 0)
					if (latestCompletionTime[i] - sulyozottGraf[j][i] < latestCompletionTime[j])
					{
						latestCompletionTime[j] = latestCompletionTime[i] - sulyozottGraf[j][i];
					}
			}
		}


		for (int i = 1; i <= n; i++)
		{
			latestStartTime[i] = 0;
		}
		
		int task = n;
		for (int i = n; i >=1; i--)
		{
			for (int j = 1; j < n+1; j++)
			{
				if (sulyozottGraf[i][j] != 0)
				{
					if ((latestCompletionTime[i] - sulyozottGraf[i][j] + 1) > latestStartTime[i])
					{
						latestStartTime[task] = latestCompletionTime[i] + sulyozottGraf[i][j] + 1;
						task--;
					}
				}
			}
		}

		for (int i = 0; i <= n; i++) 
		{
			slackTime[i] = latestCompletionTime[i] - earliestCompletionTime[i];
		}

		cout << "--------- Kritikus ut ---------" << endl;
		for (int i = 1; i < n+1; i++)
		{
			if (slackTime[i] == 0) 
			{
				if (i != 0) 
				{
					cout<<i;
					if (i != n) 
					{
						cout<<" ---> ";
					}
				}
			}
		}
		cout << endl;

		cout << "--------- Legkorabbi es legkesobbi befejezes ---------" << endl;
		for (int i = 1; i < n+1; i++) 
		{
			cout << "#" << i <<" folyamatnak"<< endl;
			cout << "Legkorabbi befejezesi ido: " << earliestCompletionTime[i] << " egyseg\t Legkesobbi bejezesi ido: " << latestCompletionTime[i] << " egyseg"<<endl;
		}
		
		cout << endl;

		cout << "--------- Legkorabbi es legkesobbi elkezdes ---------" << endl;
		for (int i = 1; i <= n; i++) {
			cout << "#" << i <<" folyamatnak"<< endl;
			cout << "Legkorabbi elkezdese az " << i << " folyamatnak : " << earliestStartTime[i] << " egyseg \t Legkesobbi elkezdesi ido : " << latestStartTime[i] << " egyseg" << endl;
		}

		cout << endl;
		cout << "--------- Csuszasi ido ---------" << endl;
		for (int i = 1; i < n+1; i++) 
		{
			cout << "Csuszasi ideje a " << i << " folyamatnak: " << slackTime[i] << " egyseg" << endl;
		}

		system("pause");
		return 0;
}