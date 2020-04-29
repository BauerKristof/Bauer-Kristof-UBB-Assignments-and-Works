//Bauer Kristof
//bkim1790
//511
//F6 - paratlan

#include <iostream>

using namespace std;

struct Csomopont
{
	int info=0;
	Csomopont* bal=NULL;
	Csomopont* jobb=NULL;

	Csomopont(int info) : info(info), bal(NULL), jobb(NULL) {}
};


class BinarisFa
{
	Csomopont* gyoker;

	void destruktorTorol(Csomopont *csomopont)
	{
		if (!csomopont)
		{
			return;
		}

		Csomopont * jelenlegi = csomopont;
		Csomopont * baloldali = csomopont->bal;
		Csomopont * jobboldali = csomopont->jobb;
		delete(jelenlegi);
		destruktorTorol(baloldali);
		destruktorTorol(jobboldali);
	}

	void inOrder(Csomopont* csomopont)
	{
		if (!csomopont)
		{
			return;
		}


		inOrder(csomopont->bal);
		cout << csomopont->info <<" ";
		inOrder(csomopont->jobb);
	}

	void Beszuras(int ertek, Csomopont*& csomopont)
	{
		if (csomopont == NULL) 
		{
			csomopont = new Csomopont(ertek);
		}
		else 
		{
			if (ertek < csomopont->info) 
			{
				this->Beszuras(ertek, csomopont->bal);
			}
			else if (ertek > csomopont->info) 
			{
				this->Beszuras(ertek, csomopont->jobb);
			}
			else 
			{
				cout << "HIBA: Letezik mar az ertek" <<endl;
			}
		}
	}

	bool Kereses(int ertek, Csomopont*& csomopont) 
	{
		if (csomopont == NULL) 
		{
			return false;
		}
		else if (ertek == csomopont->info) 
		{
			return true;
		}
		else if (ertek < csomopont->info) 
		{
			return this->Kereses(ertek, csomopont->bal);
		}
		else 
		{
			return this->Kereses(ertek, csomopont->jobb);
		}
	}

	void Torles(int ertek, Csomopont*& csomopont) 
	{
		if (csomopont == NULL) 
		{
			cout << "HIBA: Nincs ilyen erteku elem" << endl;
		}
		else if (ertek == csomopont->info) 
		{
			Csomopont* seged = NULL;
			if (csomopont->bal == NULL && csomopont->jobb == NULL)
			{
				seged = csomopont;
				csomopont = NULL;
			}
			else if (csomopont->bal != NULL && csomopont->jobb == NULL)
			{
				seged = csomopont;
				csomopont = csomopont->bal;

			}
			else if (csomopont->bal == NULL && csomopont->jobb != NULL) 
			{
				seged = csomopont;
				csomopont = csomopont->jobb;
			}
			else 
			{
				Csomopont*& minCsomopont = this->minKeres(csomopont->jobb);
				csomopont->info = minCsomopont->info;
				this->Torles(minCsomopont->info, minCsomopont);
			}
			if (seged != NULL) delete seged;

		}
		else if (ertek < csomopont->info) 
		{
			this->Torles(ertek, csomopont->bal);
		}
		else 
		{
			this->Torles(ertek, csomopont->jobb);
		}
	}


	Csomopont*& minKeres(Csomopont*& csomopont)
	{
		if (csomopont == NULL)
		{
			cout << "HIBA:Nem talaltam meg a minimum erteket";
		}
		else if (csomopont->bal == NULL)
		{
			return csomopont;
		}
		else
		{
			return this->minKeres(csomopont->bal);
		}
	}


	public:
		BinarisFa();
		BinarisFa(Csomopont*);
		~BinarisFa();
		
		void Kiiras();
		void Beszuras(int);
		void Kereses(int);
		void Torles(int);
};


BinarisFa::BinarisFa()
{
	gyoker=NULL;
}

BinarisFa::BinarisFa(Csomopont* gyokerCsp)
{
	gyoker=gyokerCsp;
}

BinarisFa::~BinarisFa()
{
	destruktorTorol(gyoker);
}

void BinarisFa::Kiiras()
{
	inOrder(gyoker);
	cout << endl;
}

void BinarisFa::Beszuras(int x) 
{
	if (gyoker == NULL) 
	{
		this->gyoker = new Csomopont(x);
	}
	else 
	{
		this->Beszuras(x, this->gyoker);
	}
}

void BinarisFa::Kereses(int x) 
{
	if (Kereses(x, this->gyoker) == true)
	{
		cout << "A binaris keresofa tartalmazza a "<< x<<" erteket" << endl;
	}
	else
	{
		cout << "A binaris keresofa nem tartalmazza a "<<x<<" erteket" << endl;
	}
}

void BinarisFa::Torles(int x) 
{
	this->Torles(x, this->gyoker);
}


int main() 
{
	Csomopont* valami=NULL;
	
	BinarisFa binFa(valami);

	binFa.Beszuras(5);
	binFa.Beszuras(4);
	binFa.Beszuras(6);
	binFa.Kiiras();
	binFa.Torles(4);
	binFa.Kiiras();
	binFa.Kereses(4);
	binFa.Kereses(6);

	system("pause");
	return 0;
}
