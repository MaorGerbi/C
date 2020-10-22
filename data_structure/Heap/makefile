# this is my target---------
TARGET = Heap.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ../include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = HeapTest.c Heap.c ../Vector/Vector.c 

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  

HeapTest.o: HeapTest.c Heap.h
	$(CC) $(CFLAGS) -c HeapTest.c  

Heap.o: Heap.c Heap.h
	$(CC) $(CFLAGS) -c Heap.c  

Vector.o: Vector.c ../includ/Vector.h
	$(CC) $(CFLAGS) -c Vector.c  

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
