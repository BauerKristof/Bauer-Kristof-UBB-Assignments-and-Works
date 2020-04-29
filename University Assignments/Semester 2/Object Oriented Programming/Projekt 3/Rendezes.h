/*
Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790
*/

#pragma once
#include <ctime>

template <class T>
class Rendezes 
{
protected:
	virtual bool kisebb(T a, T b) = 0;
	virtual void csere(T &a, T &b) = 0;
public:
	virtual void rendez(T *tomb, int n) = 0;
};

class Stat {
private:
	unsigned int ido, nHasonlit, nCsere;
	std::clock_t c;

protected:
	void kezd();
	void vege();
	void init();
	void incHasonlit();
	void incCsere();

public:
	Stat();
	unsigned int getIdo();
	unsigned int getHasonlit();
	unsigned int getCsere();
};

void Stat::kezd() 
{
	c = std::clock();
}

void Stat::vege() 
{
	//std::clock_t akt = std::clock();
	//c -= akt;
	//ido = c;
	c = clock() - c;
	ido = (int)((double)(c * 1000)) / CLOCKS_PER_SEC;
}

void Stat::init() 
{
	ido = 0;
	nHasonlit = 0;
	nCsere = 0;
}

void Stat::incHasonlit()
{
	nHasonlit++;
}

void Stat::incCsere() 
{
	nCsere++;
}

Stat::Stat() 
{
	init();
	c = 0;
}

unsigned int Stat::getIdo() 
{
	return ido;
}

unsigned int Stat::getHasonlit() 
{
	return nHasonlit;
}

unsigned int Stat::getCsere() 
{
	return nCsere;
}

template <class T>
class BuborekosRendezes : public Rendezes<T> {
protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool BuborekosRendezes<T>::kisebb(T a, T b) {
	if (a < b) return true;
	else return false;
}

template <class T>
void BuborekosRendezes<T>::csere(T &a, T &b) {
	T csereSzam = a;
	a = b;
	b = csereSzam;
}

template <class T>
void BuborekosRendezes<T>::rendez(T *tomb, int n) {
	int nn = n - 1;
	bool rendben = false;

	while (!rendben) {
		rendben = true;
		
		for (int i = 0; i < nn; i++)
		{
			if (kisebb(tomb[i + 1], tomb[i]))
			{
				csere(tomb[i], tomb[i + 1]);
				rendben = false;
			}
		}

		nn--;
	}
}
template <class T>
class BuborekosRendezesT : public BuborekosRendezes<T>, public Stat {
protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool BuborekosRendezesT<T>::kisebb(T a, T b) {
	incHasonlit();
	bool ks = BuborekosRendezes<T>::kisebb(a, b);
	return ks;
}


template <class T>
void BuborekosRendezesT<T>::csere(T &a, T &b) {
	incCsere();
	BuborekosRendezes<T>::csere(a, b);
}

template <class T>
void BuborekosRendezesT<T>::rendez(T *tomb, int n) {
	kezd();
	BuborekosRendezes<T>::rendez(tomb, n);
	vege();
}

template <class T>
class QuickSort : public Rendezes<T> {
private:
	void qsort(T* a, int bal, int jobb);
	int particional(T *a, int bal, int jobb);

protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);
};

template <class T>
bool QuickSort<T>::kisebb(T a, T b) {
	if (a < b) return true;
	else return false;
}

template <class T>
void QuickSort<T>::csere(T &a, T &b) {
	T segedSzam = a;
	a = b;
	b = segedSzam;
}

template <class T>
int QuickSort<T>::particional(T* a, int bal, int jobb) {
	int l = bal;
	int r = jobb;
	int v = 0;

	while (l < r) 
	{
		if (kisebb(a[r], a[l])) 
		{
			csere(a[l], a[r]);
			v = 1 - v;
		}
		l += v;
		r = r - 1 + v;
	}
	
	return l;
}

template<class T>
void QuickSort<T>::qsort(T* a, int bal, int jobb) {
	if (bal < jobb) 
	{
		int m = particional(a, bal, jobb);
		qsort(a, bal, m);
		qsort(a, m + 1, jobb);
	}
}

template <class T>
void QuickSort<T>::rendez(T* tomb, int n){
	qsort(tomb, 0, n-1);
}

template <class T>
class QuickSortT : public QuickSort<T>, public Stat {

protected:
	bool kisebb(T a, T b);
	void csere(T &a, T &b);

public:
	void rendez(T *tomb, int n);

};

template <class T>
bool QuickSortT<T>::kisebb(T a, T b) {
	incHasonlit();
	bool ks = QuickSort<T>::kisebb(a, b);
	return ks;
}

template <class T>
void QuickSortT<T>::csere(T &a, T &b) {
	incCsere();
	QuickSort<T>::csere(a, b);
}

template <class T>
void QuickSortT<T>::rendez(T *tomb, int n) 
{
	kezd();
	QuickSort<T>::rendez(tomb, n);
	vege();
}

