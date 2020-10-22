# this is my target
TARGET = Group.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g

# Include directory
INC_DIR = ../include

CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = GroupTest.c Group.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

GroupTest.o: GroupTest.c ../include/Group.h
	$(CC) $(CFLAGS) -c GroupTest.c

Group.o: Group.c ../include/Group.h
	$(CC) $(CFLAGS) -c Group.c

clean:
	-rm $(TARGET) *.o

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)

