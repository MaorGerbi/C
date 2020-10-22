# this is my target
TARGET = BST

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR =./
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = BSTtest.c BST.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  

BSTtest.o:BSTtest.c BST.h 
	$(CC) $(CFLAGS) -c BSTtest.c  

BST.o: BST.c BST.h
	$(CC) $(CFLAGS) -c BST.c   


clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
