#!/bin/bash

if (($(id -g) != 0)); then
	echo "Запуск возможен только от пользователя root"
	exit 1
fi
echo ""
echo "Поиск установленных пакетов"
echo ""

rm -rf /tmp/pacagelist.txt
rm -rf /tmp/needtofirewall.txt
rm -rf firewall.conf

apt list | grep установ | cut -d"/" -f1 > /tmp/pacagelist.txt
cat /tmp/pacagelist.txt | grep -v lib | tee /tmp/pacagelist.txt

echo ""
echo "Поиск совпадений с list.txt"
echo ""

cat /tmp/pacagelist.txt | while read line
do
	cat list.txt | grep $line 
done | tee /tmp/needtofirewall.txt

echo ""
echo "Формирование правил для iptables"
echo ""

cat /tmp/needtofirewall.txt| while read line
do
	pac=`echo $line | awk '{print $2}'`
	fstpac=`echo $pac | awk -F/ '{print $1}'`
	scndpac=`echo $pac | awk -F/ '{print $2}'`
	echo "-A INPUT -p $scndpac -m $scndpac --dport $fstpac -j ACCEPT"
	iptables -A INPUT -p $scndpac -m $scndpac --dport $fstpac -j ACCEPT
done

echo "-A INPUT -p tcp -m tcp -j DROP"
echo "-A INPUT -p udp -m udp -j DROP"
iptables -A INPUT -p tcp -m tcp -j DROP
iptables -A INPUT -p udp -m udp -j DROP

echo ""
echo "Правила сохранены"
echo ""

rm -rf /tmp/pacagelist.txt
rm -rf /tmp/needtofirewall.txt

iptables -L

echo ""
echo "Завершение работы"
echo ""
