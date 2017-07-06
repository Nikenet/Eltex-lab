#!/bin/bash
#echo $@; # вывод в stdout до 16(32) аргументов.

read a;
read b;

#echo $(($a+$b)); #последовательно вносим 2 перемененные, затем складываем их.

if [[ $a -lt $b ]]; then
	echo "a < b"
else
	echo "a > b"
fi

for i in 1 2 3 4 5 6 7
do

echo $i;

done

