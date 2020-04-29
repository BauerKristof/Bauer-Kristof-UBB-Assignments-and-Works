#!/bin/bash

#Nev: Bauer Kristof
#Csoport:511
#Felhasznalo:bkim1790

if [ $# -le 0 ]
then
 echo Hasznalat $0 "fileok"
fi

for i
do
	 if [ ! -f $i ]
	 then
 	echo "Nincs ilyen file"
 	exit 1
	 fi
done


for i
do

LEGHOSSZABB=`awk '
BEGIN{max=-1;} 
 (NF>max){ max=NF;}
END{
print max;}
' $i`
printf "ALLOMANY= "$i"\n"
printf "LEGHOSSZABB SZO= "$LEGHOSSZABB"\n"

awk '
BEGIN {
    if (width == 0) width = 80
}

NF <= 1 { print }

NF > 1 {
    nbchar = 0
    for (i = 1; i <= NF; i++) {
        nbchar += length($i)
    }
    nbspc = width - nbchar
    spcpf = int(nbspc / (NF - 1))
    for (i = 1; i < NF; i++) {
        printf $i
        spaces = (NF == 2 || i == NF - 1) ? nbspc : spcpf
        if (spaces < 1) spaces = 1
        for (j = 0; j < spaces; j++) {
            printf " "
        }
	ossz+=nbspc;
        nbspc -= spaces
    }
    print $NF
}


END{
	printf "Osszesen %d szokozt szurtunk be\n",ossz;
}
' $*

done
