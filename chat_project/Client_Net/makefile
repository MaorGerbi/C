# this is my target
TARGET = clientN.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ../include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = ClientN_Test.c Client_Net.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  
	
ClientN_Test.o: ClientN_Test.c ../include/Client_Net.h
	$(CC) $(CFLAGS) -c ClientN_Test.c
		
Client_Net.o: Client_Net.c ../include/Client_Net.h
	$(CC) $(CFLAGS) -c Client_Net.c    

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
