#!/bin/bash

echo "Введите путь"
read a;

echo "Введите количество начальных папок"
read b;

echo "Введите количество папок в папках"
read c;

echo "Введите количество файлов в конечных папках "
read d;

cd $a;

for (( i = 0; i < $b; i++ )); do

	mkdir $i;
	cd $i;
	
		for (( j = 0; j < $c; j++ )); do
		
			mkdir $j
			cd $j
			
				for (( k = 0; k < $d; k++ ));
								
				do

					touch $k
					
				done
			cd ..
		done
	cd ..
done