# this is my target
TARGET = Protocol.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g

# Include directory
INC_DIR = ../include

CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = ProtocolTest.c Protocol.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

ProtocolTest.o: ProtocolTest.c ../include/Protocol.h
	$(CC) $(CFLAGS) -c ProtocolTest.c

Protocol.o: Protocol.c ../include/Protocol.h
	$(CC) $(CFLAGS) -c Protocol.c

clean:
	-rm $(TARGET) *.o

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)

