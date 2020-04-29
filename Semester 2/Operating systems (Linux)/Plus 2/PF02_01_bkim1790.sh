#!/bin/bash

#Nev: Bauer Kristof
#Csoport:511
#Felhasznalo: bkim1790
#Pf02_01-es feladat

if [ $# -le 1 ]
then echo Hasznalat: $0 Prefixallomany Allomanyok
 exit 1
fi

ALLOMANY=$1
shift

for i in $*
do
         for j in `grep [0-9][0-9][0-9][0-9].* -o "$ALLOMANY"`
	 do #megvannak a telefonszamok

	  for k in `grep -wo "$j\*[0-9]\{6\}" "$i"`
                do
                echo "$k" >> "tel_$i"
                done

	  for k in `grep -wo "$j\.[0-9]\{6\}" "$i"`
               do
                echo "$k" >> "tel_$i"
	 	done


	  for k in `grep -wo "$j\-[0-9]\{6\}" "$i"`
                do	
               echo "$k" >> "tel_$i"
       		done

	 
	 for k in `grep -wo "$j[0-9]\{6\}" "$i"`
	 	do
		echo "$k" >> "tel_$i"
		done

   done
   echo "---------------------------"
 echo "A feldolgozott allomany: " "tel_$i"
 cat "tel_$i"
   
done 
