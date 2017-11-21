from scapy.all import *

def udp_inspection(pkt):
	eth = pkt.getlayer(Ether)
	udp = pkt.getlayer(UDP)

	print("Got an UDP packet from %s port %d" % (eth.dst, udp.sport))

	if eth.dst != "de:ad:be:ee:ee:ef":
		return

	print(pkt.load)

print("Wait for UDP packets...")

# Wait for UDP packets...
sniff(iface = "lo", filter = "udp", prn = udp_inspection)
