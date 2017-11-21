from scapy.all import *

a = \
	Ether(src = "00:00:00:00:00:00", dst = "de:ad:be:ee:ee:ef") \
	/ IP(src = "127.0.0.1", dst = "127.0.0.1") \
	/ UDP(sport = 3423, dport = 5342) \
	/ "Hello world!"

sendp(a, iface = "lo")
