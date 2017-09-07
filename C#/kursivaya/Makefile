CC=gcc
CFLAGS=-g -c -Wall
TARGET=main
SECONDTARGER=client
THRDTARGET=manager

$(TARGET): $(TARGET).o $(SECONDTARGER).o DieWithError.c HandleTCPClient.c HandleTCPClientTwo.c AcceptTCPConnection.c CreateTCPServerSocket.c
	$(CC) $(TARGET).o DieWithError.c HandleTCPClient.c HandleTCPClientTwo.c AcceptTCPConnection.c CreateTCPServerSocket.c -o server -pthread
	$(CC) $(SECONDTARGER).o DieWithError.c -o $(SECONDTARGER)
	$(CC) $(THRDTARGET).o DieWithError.c -o $(THRDTARGET)

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
