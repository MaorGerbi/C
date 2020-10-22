# this is my target---------
TARGET = Stack.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ../include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = Stack_Test.c Stack.c ../Vector/Vector.c 

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  

Stack_Test.o: Stack_Test.c Stack.h 
	$(CC) $(CFLAGS) -c Stack_Test.c  

Stack.o: Stack.c Stack.h ../include/Vector.h
	$(CC) $(CFLAGS) -c Stack.c  

Vector.o: Vector.c ../includ/Vector.h
	$(CC) $(CFLAGS) -c Vector.c  

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
