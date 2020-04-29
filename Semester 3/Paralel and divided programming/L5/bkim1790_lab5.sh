#!/bin/bash

#last -f wtimpnemtomm | grep "`date +%b`"
honap=`date +%b`
nap=$1
ido1=$2
ido2=$3

ora1=`echo $ido1|cut -d":" -f 1`
perc1=`echo $ido1|cut -d":" -f 2`
ora2=`echo $ido2|cut -d":" -f 1`
perc2=`echo $ido2|cut -d":" -f 2`
ok=0


#| grep "`date + %b`" | sed 's/ \+/ /g'
last -f wtmp_2016dec|grep "`date +%b`"|sed 's/ \+/ /g'|grep -v "reboot"|grep -v "no logout"|grep -v "down"|grep -v "still"  > temp.txt
while IFS= read -r line; do
    FELHASZNALO=`echo $line | cut -d' ' -f1`
    FELHNAP=`echo $line | cut -d' ' -f6`
    FELHONAP=`echo $line | cut -d' ' -f5`

    KEZDIDO=`echo $line | cut -d' ' -f7`
    BEFIDO=`echo $line |cut -d' ' -f9 `
    
    kezdidora=`echo $KEZDIDO | cut -d':' -f1`
    kezdidoperc=`echo $KEZDIDO | cut -d':' -f2`

    befidora=`echo $BEFIDO | cut -d':' -f1`
    befidoperc=`echo $BEFIDO | cut -d':' -f2`

    if [ "$nap" == "$FELHNAP" ]
    then
	    if [ "$honap" == "$FELHONAP" ]
            then

      if [ "$kezdidora" -gt "$befidora" ]
  then
    ok=0
    exit 0
  fi

  if [ "$ora1" -eq "$kezdidora" ]
  then
    if [ "$perc1" -le "$kezdidoperc" ]
    then
      if [ "$ora2" -gt "$befidora" ]
      then
        ok=1
      elif [ "$ora2" -eq "$befidora" ]
      then
        if [ "$perc2" -ge "$befidoperc" ]
        then
          ok=1
        fi
      else
        ok=0
      fi
    fi
  else
    if [ "$ora1" -lt "$kezdidora" ]
    then
      if [ "$ora2" -gt "$befidora" ]
      then
        ok=1
      elif [ "$ora2" -eq "$befidora" ]
      then
        if [ "$perc2" -ge "$befidoperc" ]
        then
          ok=1
        fi
      else
        ok=0
      fi
    else
      ok=0
    fi
  fi

  if [ "$ok" -eq "1" ]
  then
    echo $FELHASZNALO
  fi
 fi
fi
done < temp.txt

rm temp.txt
