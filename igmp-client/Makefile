CC=gcc
CFLAGS=-g -c -Werror
TARGET=querygenerator
SECONDTARGET=client

$(TARGET): $(TARGET).o $(SECONDTARGET).o
		$(CC) $(TARGET).o -o $(TARGET)
		$(CC) $(SECONDTARGET).o -o $(SECONDTARGET) -lpthread

$(TARGET).o: $(TARGET).c $(SECONDTARGET).c
		$(CC) $(CFLAGS) $(TARGET).c
		$(CC) $(CFLAGS) $(SECONDTARGET).c

clean:
		rm -rf $(TARGET)
		rm -rf $(TARGET).o
		rm -rf $(SECONDTARGET)
		rm -rf $(SECONDTARGET).o
		