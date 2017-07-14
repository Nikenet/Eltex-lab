#!/bin/bash

function create (){
	
	echo "Введите имя отслеживаемой программы и переодичность (MM:ЧЧ:<ИМЯ>)"
	echo "Для повторения каждые n минут/часов указывать: */n"
	read target
	
	target_m=`echo $target | awk -F: '{print $1}'`
	target_h=`echo $target | awk -F: '{print $2}'`
	name=`echo $target | awk -F: '{print $3}'`	

	(crontab -l ; echo "$target_m $target_h * * * if (( (ps aux | grep $name | wc -l) != 0 )); then $name; fi # $name ") | crontab -
	crontab -l
}

function  edit(){
	crontab -l
	echo "Какую задачу вы бы хотели изменить?"
	read editname
	crontab -l | grep -v $editname | crontab -

	echo "Введите новую переодичность (ММ)"
	echo "Для повторения каждые n минут/часов указывать: */n"
	read edittime
	edittime_m=`echo $edittime | awk -F: '{print $1}'`
	edittime_h=`echo $edittime | awk -F: '{print $2}'`
	
	(crontab -l ; echo "$edittime_m $edittime_h * * * if (( (ps aux | grep $name | wc -l) != 0 )); then $name; fi # $editname ") | crontab -
	crontab -l
}

function  delete (){
	crontab -l
	echo "Какую задачу вы хотели бы удалить?"
	read del

	crontab -l | grep -v $del | crontab -
	crontab -l
}

function status (){
	ps aux
	crontab -l
}

echo "Выберите действие:"
echo "1) Создание новой задачи"
echo "2) Редактирование текущих задач"
echo "3) Удаление задач"
echo "4) Статус текущих задач"
read input

case $input in
	1) create;;
	2) edit;;
	3) delete;;
	4) status;;
esac