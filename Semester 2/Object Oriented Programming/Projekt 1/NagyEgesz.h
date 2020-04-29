/*
Nev:Bauer Kristof
Csoport:511
*/

#pragma once

class NagyEgesz 
{
	int EloJel, N;
	int *szam;

	friend bool operator>(const NagyEgesz &, const NagyEgesz &);
	void kerekitSzamra(NagyEgesz&);

public:
	class NullavalValoOsztas {};
	NagyEgesz();
	NagyEgesz(int elojel, int n, const int* szamjegyek);
	NagyEgesz(const NagyEgesz&);
	~NagyEgesz();
	
	void kiir() const; 
	NagyEgesz osszead(const NagyEgesz&);
	NagyEgesz kivon(const NagyEgesz&);
	NagyEgesz szoroz(const NagyEgesz&);
	NagyEgesz oszt(const NagyEgesz&);
};