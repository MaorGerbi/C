# this is my target
TARGET = Multicast.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g3 

# Include directory
INC_DIR = ../include

CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = Multicast.c MulticastTest.c 

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) 

Multicast.o: Multicast.c ../include/Multicast.h 
	$(CC) $(CFLAGS) -c Multicast.c  

MulticastTest.o: MulticastTest.c ../include/Multicast.h 
	$(CC) $(CFLAGS) -c MulticastTest.c  




clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	  
	
