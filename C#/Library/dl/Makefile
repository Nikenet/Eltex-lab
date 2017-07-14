CC=gcc
CFLAG=-Wall -g -c

TARGET=main
LIBRARY=count

$(TARGET): $(TARGET).o $(LIBRARY).so
	$(CC) -o $(TARGET) $(TARGET).o -ldl

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAG) $(TARGET).c

$(LIBRARY).so: $(LIBRARY).o
	$(CC) -shared -o lib$(LIBRARY).so $(LIBRARY).o

$(LIBRARY).o: $(LIBRARY).c
	$(CC) $(CFLAG) -fPIC $(LIBRARY).c

clean:
	rm -rf *.o *.a $(TARGET) lib$(LIBRARY).so
