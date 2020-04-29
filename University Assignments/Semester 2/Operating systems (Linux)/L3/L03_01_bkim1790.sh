#!/bin/bash

#Nev: Bauer Kristof
#Azonosito: bkim1790
#Csoport: 511

#Határozzuk meg a linux.scs.ubbcluj.ro szerverről az összes diák felhasználót, akinek van weblapja, tudva, hogy a személyes directory-k évfolyamonként és csoportonként vannak elrendezve a /home/scs directory-ban. (Egy felhasználónak van saját weblapja, ha a személyes katalógusában van egy mások által is elérhető "public_html" directory.)



if [ $# -ge 2 ]
then echo Hasznalat: $0 "-v"
 exit 1
fi

for i in `find /home/scs -name "public_html" 2>/dev/null`
do
CSOP=`echo $i|cut -d'/' -f6`
FELHASZNALO=`echo $i|cut -d'/' -f7`
j=$(echo $CSOP | grep gr)
#Mivel voltak olyan felhasznalok akik nem diakok voltak, azaz nem volt gr azonositojuk a grep ures stringet adna ra, igy ki tudom ejteni oket
if [ -n "$j" ]; then
	grep $FELHASZNALO /etc/passwd | cut -d':' -f5	
        echo "$FELHASZNALO"
	if [ "$1" = "-v" ]; then
	 if [ "$CSOP" = "gr511" ]
		then echo -n "Csoporttars"
		else echo $CSOP
	 fi
	fi
	
	SZAK=`echo $FELHASZNALO|cut -c3-4`

	case $SZAK in
		im) echo "informatika magyar vonal";;
		ir) echo "informatika román vonal";;
		ie) echo "informatika angol vonal";;
		ig) echo "informatika német vonal";;
		am) echo "matinfo magyar vonal";;
		ar) echo "matinfo roman vonal";;
		ae) echo "matinfo angol vonal";;
		mm) echo "matematika magyar vonal";;
		mr) echo "matematika román vonal";;
		*)  echo "mesteris";;
	esac
fi
done
 
