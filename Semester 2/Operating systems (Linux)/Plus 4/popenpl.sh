p=`echo $1 | grep -o "^[0-9]\{2\}"`

honap=`date +"%m"`
case $honap in
  01) honap="Jan";;
  02) honap="Feb";;
  03) honap="Mar";;
  04) honap="Apr";;
  05) honap="May";;
  06) honap="Jun";;
  07) honap="Jul";;
  08) honap="Aug";;
  09) honap="Sep";;
  10) honap="Oct";;
  11) honap="Nov";;
  12) honap="Dec";;
esac

last | grep " $honap $nap" | sort >seged1.tmp

grep -o '^[a-z][a-z][a-z][a-z][0-9][0-9][0-9][0-9]' seged1.tmp | uniq
rm seged1.tmp

exit 0

