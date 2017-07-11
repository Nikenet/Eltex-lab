CC=gcc
CFLAG=-Wall -g -c

LC=ar
LFLAG=cr

TARGET=main
LIBRARY=count

$(TARGET): $(TARGET).o $(LIBRARY).a
	$(CC) -o $(TARGET) $(TARGET).o -L. -lcount

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAG) $(TARGET).c

$(LIBRARY).a: $(LIBRARY).o
	$(LC) $(LFLAG) lib$(LIBRARY).a $(LIBRARY).o

$(LIBRARY).o: $(LIBRARY).c
	$(CC) $(CFLAG) $(LIBRARY).c

clean:
	rm -rf *.o *.a binary