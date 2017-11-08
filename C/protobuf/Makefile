CC=gcc
CFLAGS=-g -c -Wall 
TARGET=serialize
SUBTARGET=deserialize

$(TARGET): $(TARGET).o $(SUBTARGET).o amessage.pb-c.c
	$(CC) $(TARGET).o amessage.pb-c.c -lprotobuf-c -o $(TARGET)
	$(CC) $(SUBTARGET).o amessage.pb-c.c -lprotobuf-c -o $(SUBTARGET)

$(TARGET).o: $(TARGET).c $(SUBTARGET).c
	protoc-c --c_out=. amessage.proto
	$(CC) $(CFLAGS) $(TARGET).c
	$(CC) $(CFLAGS) $(SUBTARGET).c	

clean:
	rm -rf $(TARGET)
	rm -rf $(TARGET).o
	rm -rf $(SUBTARGET).o
	rm -rf $(SUBTARGET)
	rm -rf amessage.pb-c.c
	rm -rf amessage.pb-c.h