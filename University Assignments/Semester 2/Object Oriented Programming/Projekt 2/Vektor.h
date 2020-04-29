/*Nev:Bauer Kristof
Csoport:511
Felhasznalo:bkim1790*/


#pragma once
#include <cmath>

template<class T>
class RitkaVektor;

template<class T>
class Vektor
{
private:
	T*  m_t;
	int m_dim;

public:
	Vektor(){}
	Vektor(int dim);
	Vektor(T *t, int dim);
	Vektor(const Vektor&);
    ~Vektor();

	Vektor operator+(const Vektor&);
	Vektor operator-(const Vektor&);
	double operator*(const Vektor&);
	double operator~();
	double operator%(const Vektor&);
	T      operator[](int) const;
	operator RitkaVektor<T>();

};

template<class T>
Vektor<T>::Vektor(int dim)
{
	m_dim = dim;
	m_t = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
	{
		m_t[i] = 1;
	}
}

template<class T>
Vektor<T>::Vektor(T *t, int dim)
{
	m_dim = dim;
	m_t = new T[m_dim];

	for (int i = 0; i < m_dim; i++)
	{
		m_t[i] = t[i];
	}
}

template<class T>
Vektor<T>::Vektor(const Vektor& V)
{
	m_dim = V.m_dim;
	m_t = new T[m_dim];

	for (int i = 0; i < m_dim; i++)
	{
		m_t[i] = V.m_t[i];
	}
}

template<class T>
Vektor<T>::~Vektor() 
{
	delete[] m_t;
}

template <class T>
Vektor<T> Vektor<T>::operator+(const Vektor &v)
{
	if (m_dim != v.m_dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}
	
	T *x = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
	{
		x[i] = m_t[i] + v.m_t[i];
	}
	Vektor eredmeny(x, m_dim);
	delete[] x;
	return eredmeny;
}

template <class T>
Vektor<T> Vektor<T>::operator-(const Vektor &v)
{
	if (m_dim != v.m_dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	T *x = new T[m_dim];
	for (int i = 0; i < m_dim; i++)
	{
		x[i] = m_t[i] - v.m_t[i];
	}

	Vektor eredmeny(x, m_dim);
	delete[] x;
	return eredmeny;
}

template <class T>
double Vektor<T>::operator*(const Vektor& v)
{
	if (m_dim != v.m_dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	double szorzat=0.0;
	for (int i = 0; i < m_dim; i++)
	{
		szorzat += m_t[i] * v.m_t[i];
	}

	return szorzat;

}

template <class T>
double Vektor<T>::operator~()
{
	double norma = 0.0;

	for (int i = 0; i < m_dim; i++)
	{
		norma += m_t[i] * m_t[i];
	}

	norma=sqrt(norma);
	return norma;
}

template <class T>
double Vektor<T>::operator%(const Vektor& v)
{
	if (m_dim != v.m_dim)
	{
		throw "HIBA: Elter a vektorok merete";
	}

	double tavolsag = 0.0;
	for (int i = 0; i < m_dim; i++)
	{
		tavolsag +=(m_t[i] - v.m_t[i]) * (m_t[i] - v.m_t[i]);
	}
	return sqrt(tavolsag);
}

template <class T>
T Vektor<T>::operator[](int poz) const
{
	if ((poz < 0) || (poz >= m_dim))
	{
		throw "HIBA: Nincs ilyen elem";
	}
	else return m_t[poz];
}

template <class T>
Vektor<T>::operator RitkaVektor<T>() 
{
	return RitkaVektor<T>(m_t, m_dim);
}
