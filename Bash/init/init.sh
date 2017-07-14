#/bin/bash

function create (){
	service --status-all
	echo "Введите имя отслеживаемого сервиса и переодичность (MM:<ИМЯ>)"
	read target
	
	target_m=`echo $target | awk -F: '{print $1}'`
	name=`echo $target | awk -F: '{print $2}'`

	service $name start
	(crontab -l ; echo "$target_m * * * * service $name start # $name ") | crontab -
	crontab -l
}

function  edit(){
	crontab -l
	echo "Какую задачу вы бы хотели изменить?"
	read editname
	crontab -l | grep -v $editname | crontab -

	echo "Введите новую переодичность (ММ)"
	read edittime
	crontab -l

	service $editname start
	(crontab -l ; echo "$edittime * * * * service $editname start # $editname ") | crontab -
}

function  delete (){
	crontab -l
	echo "Какую задачу вы хотели бы удалить?"
	read del

	crontab -l | grep -v $del | crontab -
	crontab -l
}

function status (){
	service --status-all
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
