#!/bin/bash

#Nev:Bauer Kristof
#Csoport:511
#Azonosito:bkim1790
#A parancssorban megadott állományok soraiból törölje ki a második és negyedik szót. A szavak csak betűket és számjegyeket tartalmaznak, az elválsztó karakter pedig a szóköz.

if [ $# -lt 1 ]
then echo Hasznalat: $0 Allomanynev
 exit 1
fi



for i in $*
do
	sed -Ei "s/[^ ]+ *//4" "$i"
	 sed -Ei "s/[^ ]+ *//2" "$i"
done   

