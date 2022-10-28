CC = g++
CFLAGS  = -Wall -Werror
TARGET = MSH
SRC_DIR = src/
 
all: clean main run

main: main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o
	
main.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)main.cc

run: 
	./MSH

clean:
	$(RM) $(TARGET)	*.o
