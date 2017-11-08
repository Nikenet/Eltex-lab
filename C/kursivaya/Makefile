CC=gcc
CFLAGS=-g -c -Wall
TARGET=main
SECONDTARGER=client
THRDTARGET=manager

$(TARGET): $(TARGET).o $(SECONDTARGER).o DieWithError.c HandleTCPClient.o HandleTCPManager.o AcceptTCPConnection.o CreateTCPServerSocket.o message.pb-c.c
	$(CC) $(TARGET).o DieWithError.c HandleTCPClient.o HandleTCPManager.o AcceptTCPConnection.o CreateTCPServerSocket.o message.pb-c.c -lprotobuf-c -o server -pthread
	$(CC) $(SECONDTARGER).o DieWithError.c message.pb-c.c -lprotobuf-c -o $(SECONDTARGER)
	$(CC) $(THRDTARGET).o DieWithError.c message.pb-c.c -lprotobuf-c -o $(THRDTARGET)


$(TARGET).o: $(TARGET).c $(SECONDTARGER).c $(THRDTARGET).c
	protoc-c --c_out=. message.proto
	$(CC) $(CFLAGS) HandleTCPClient.c
	$(CC) $(CFLAGS) HandleTCPManager.c
	$(CC) $(CFLAGS) AcceptTCPConnection.c
	$(CC) $(CFLAGS) CreateTCPServerSocket.c
	$(CC) $(CFLAGS) $(TARGET).c
	$(CC) $(CFLAGS) $(SECONDTARGER).c
	$(CC) $(CFLAGS) $(THRDTARGET).c

clean:
	rm -rf server
	rm -rf $(SECONDTARGER)
	rm -rf $(THRDTARGET)
	rm -rf *.o
