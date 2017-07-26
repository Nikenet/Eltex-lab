CC=gcc
CFLAGS=-g -c -Wall
TARGET=main

$(TARGET): $(TARGET).o
	$(CC) $(TARGET).o -o $(TARGET)
	touch tmp.txt

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c

clean:
	rm -rf $(TARGET)
	rm -rf $(TARGET).o
	rm -rf tmp.txt