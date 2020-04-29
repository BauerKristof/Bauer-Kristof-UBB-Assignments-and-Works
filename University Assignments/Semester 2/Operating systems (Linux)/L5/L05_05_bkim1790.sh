#!/bin/bash

#Nev:Bauer Kristof
#Csoport:511
#Azonosito:bkim1790
#A parancssorban megadott állományokból töröljön ki minden olyan szót, amely legalább egy számjegyet tartalmaz.

if [ $# -lt 1 ]
then echo Hasznalat: $0 Allomanynev
 exit 1
fi


for i in $*
do

	sed -ri 's/[^ ]*[0-9][^ ]*//g' $i
done
