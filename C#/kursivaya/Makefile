CC=gcc
CFLAGS=-g -c -Wall
TARGET=main
SECONDTARGER=client

$(TARGET): $(TARGET).o $(SECONDTARGER).o DieWithError.c HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c
	$(CC) $(TARGET).o DieWithError.c HandleTCPClient.c AcceptTCPConnection.c CreateTCPServerSocket.c -o server -pthread
	$(CC) $(SECONDTARGER).o DieWithError.c -o $(SECONDTARGER)

$(TARGET).o: $(TARGET).c $(SECONDTARGER).c
	$(CC) $(CFLAGS) $(TARGET).c
	$(CC) $(CFLAGS) $(SECONDTARGER).c


clean:
	rm -rf server
	rm -rf $(TARGET).o
	rm -rf $(SECONDTARGER)
	rm -rf $(SECONDTARGER).o
	rm -rf *.o
