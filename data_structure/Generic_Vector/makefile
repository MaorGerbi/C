# this is my target---------
TARGET = vector.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g

# Include directory
INC_DIR = ../include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = Vector.c VectorTest.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  
	
VectorTest.o: VectorTest.c Vector.c $(INC_DIR)/Vector.h $(INC_DIR)/ADTDefs.h
	$(CC) $(CFLAGS) -c VectorTest.c
		
Vector.o: Vector.c $(INC_DIR)/Vector.h $(INC_DIR)/ADTDefs.h
	$(CC) $(CFLAGS) -c Vector.c    

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
