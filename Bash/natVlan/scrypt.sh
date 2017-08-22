#!/bin/bash

#включаем форвардинг
echo 1 > /proc/sys/net/ipv4/ip_forward

#чистим фаервол
iptables -F
iptables -t nat -F
iptables -t mangle -F
iptables -X

# разрешаем сразу все
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT

# Разрешаем доступ из внутренней сети наружу
iptables -A FORWARD -i enp6s0 -o ppp0 -j ACCEPT

# Разрешаем доступ снаружи во внутреннюю сеть
iptables -A FORWARD -i enp6s0 -o eth1 -j ACCEPT

# Маскарадинг
iptables -t nat -A POSTROUTING -o ppp0 -s 192.168.0.1/24 -j MASQUERADE