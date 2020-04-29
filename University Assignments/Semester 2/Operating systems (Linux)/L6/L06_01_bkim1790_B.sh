#!/bin/bash

#Nev:Bauer Kristof
#Csoport:511
#Azonosito:bkim1790
#Feladat:B) Asszociatív tömböt használva határozzuk meg és írjuk ki, hogy a hónap elejétõl számítva (a bejelentkezéseket nyilvántartó wtmp állomány kezdetétõl) melyik napon hány bejelentkezés történt, és határozzuk meg, hogy melyik nap volt a legtöbb bejelentkezés.

last | sed 's/  */ /g' | awk '
BEGIN {
	for(i=1; i<=31;i++) x[i]=0 }

	(NR==1){
		if(($1 != "reboot") && ($1!= "wtmp"))
		{
 		honap=$5;
		}
	}

{
	 if(($1 != "reboot") && ($1!= "wtmp"))
                {
		 if($5==honap)
		  {
               	   x[$6]++;
                  }
		}
}

END{
for(i=1; i<=31;i++)
	{	
	print("Az",i,"napon a bejelentkezesek szama: ",x[i]); 
	if(x[i]>max) {maxnap=i; max=x[i];}
        }
   print("A legtobb bejelentkezes az",maxnap,"napon volt, szama:",max);
}
'
