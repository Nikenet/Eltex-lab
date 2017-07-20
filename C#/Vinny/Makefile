CC=gcc
CFLAGS=-g -c -Wall
TARGET=main

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c

clean:
	rm -rf $(TARGET)
	rm -rf $(TARGET).o