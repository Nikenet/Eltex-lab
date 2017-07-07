#!/bin/bash

echo "Укажите путь"
read path;

declare -a mass

echo "Что удалять?"
read -a mass

echo elements in massive ${#mass[*]}
 

for (( i = 0; i < ${#mass[*]}; i++ )); do
	echo del ${mass[$i]}
	rm -rf ${mass[$i]}
done





