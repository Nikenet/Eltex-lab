TARGET=client
SECTARGET=server
CFLAGS=-g -c -Wall
CC=gcc

$(TARGET): $(TARGET).o $(SECTARGET).o
		$(CC) $(TARGET).o -o $(TARGET)
		$(CC) $(SECTARGET).o -o $(SECTARGET)


$(TARGET).o: $(TARGET).c $(SECTARGET).c
		$(CC) $(CFLAGS) $(TARGET).c
		$(CC) $(CFLAGS) $(SECTARGET).c

clean:
		rm -rf $(TARGET)
		rm -rf $(SECTARGET)
		rm -rf *.o
