CC=gcc
CFLAGS=-g -c -Wall
TARGET=main
SECONDTARGER=client
THRDTARGET=manager

$(TARGET): $(TARGET).o $(SECONDTARGER).o DieWithError.c HandleTCPClient.c HandleTCPManager.c AcceptTCPConnection.c CreateTCPServerSocket.c
	$(CC) $(TARGET).o DieWithError.c HandleTCPClient.c HandleTCPManager.c AcceptTCPConnection.c CreateTCPServerSocket.c -o server -pthread
	$(CC) $(SECONDTARGER).o DieWithError.c -o $(SECONDTARGER)
	$(CC) $(THRDTARGET).o DieWithError.c -o $(THRDTARGET)
	xterm -geometry 100x70+20+0 &
	xterm -geometry 50x25+650+0 &
	xterm -geometry 50x25+1000+0 &
	xterm -geometry 50x25+650+600 &
	xterm -geometry 50x25+1000+600 &

$(TARGET).o: $(TARGET).c $(SECONDTARGER).c $(THRDTARGET).c
	$(CC) $(CFLAGS) $(TARGET).c
	$(CC) $(CFLAGS) $(SECONDTARGER).c
	$(CC) $(CFLAGS) $(THRDTARGET).c

clean:
	rm -rf server
	rm -rf $(SECONDTARGER)
	rm -rf $(THRDTARGET)
	rm -rf *.o
	rm -rf /tmp/fifo.1
