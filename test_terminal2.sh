echo -en "\E[H\E[2J"
echo -en "\E[10;5H"
echo -en "\E(0"
echo -en "lqqqqqqqqk"

for (( a = 11; a < 19; a++ ))
do
echo -en "\E[$a;5H"
echo -en "x        x"
done

echo -en "\E[19;5H"
echo -en "mqqqqqqqqj"
echo -en "\E[11;8Haaaa"
echo -en "\E[12;8Ha  a"
echo -en "\E[13;8H   a"
echo -en "\E[14;8H  a "
echo -en "\E[15;8H a  "
echo -en "\E[16;8Ha   "
echo -en "\E[17;8Ha   "
echo -en "\E[18;8Haaaa"
echo -en "\E(B"
echo -en "\E[20;0H"