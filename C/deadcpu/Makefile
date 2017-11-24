CC=gcc
CFLAGS=-g -c -Wall
TARGET=deadcpu

$(TARGET): $(TARGET).o
		$(CC) $(TARGET).o -o $(TARGET) -pthread

$(TARGET).o: $(TARGET).c
		$(CC) $(CFLAGS) $(TARGET).c

clean:
		rm -rf $(TARGET)
		rm -rf $(TARGET).o