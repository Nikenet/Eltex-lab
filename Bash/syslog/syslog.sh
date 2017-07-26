#!/bin/bash

if (($(id -g) != 0)); then
	echo "Запуск возможен только от пользователя root"
	exit 1
fi

echo "Вы запустили loggrubber"
service --status-all
echo "Выберите сервис:"
read target

a=$(ls -la /var/log | grep $target) # проверяем наличие

if (( ${#a} > 0 )); then
	if [[ -d /var/log/$target ]]; then
		cat /var/log/$target/$target.log
		exit 0
	fi

	if [[ -f /var/log/$target.log ]]; then
		cat /var/log/$target.log
		exit 0
	fi
fi

echo "Логи не найдены, поиск в syslog"
echo "С какого числа <YEAR-MONTH-DAY HH:MM:SS>"
read data1
echo "По какое число <YEAR-MONTH-DAY HH:MM:SS>"
read data2

journalctl --since "$data1" --until "$data2" | grep $target