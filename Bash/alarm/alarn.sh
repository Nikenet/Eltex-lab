#!/bin/bash

function reset(){
	echo "Выберите будильник"
	crontab -l
	read delname
	crontab -l | grep -v $delname | crontab -
}

function create(){
	echo "На какое время вы желаете поставить будильник? (ЧЧ:ММ:<ИМЯ>)"
	read target

	target_h=`echo $target | awk -F: '{print $1}'`
	target_m=`echo $target | awk -F: '{print $2}'`
	name=`echo $target | awk -F: '{print $3}'`

	(crontab -l ; echo "$target_m $target_h * * * mpg321 /home/nikenet/Eltex/Bash/alarm/Gorillaz.mp3 # $name ") | crontab -
}

function status(){
	echo "Статус всех будильников:"
	crontab -l
}

echo "Вы запустили редактор будильника, выберите действие:"
echo "1. Сбросить будильник"
echo "2. Добавить новый будильник"
echo "3. Посмотреть статус текущих будильников"
read doing

case "$doing" in
1) reset;;
2) create;;
3) status;;
esac

exit 0
