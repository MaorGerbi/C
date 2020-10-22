# this is my target
TARGET = GroupM.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g3

# Include directory
INC_DIR = ../include
INC_DIR_DS = ../include/dataStructure

CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(INC_DIR_DS)

# All .c files in this directory are my sources
SOURCES = GroupMTest.c GroupM.c ../Group/Group.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L../staticLiberies -lHashMap -lQueue -o $(TARGET) 

GroupTest.o: GroupMTest.c ../include/GroupM.h
	$(CC) $(CFLAGS) -c GroupMTest.c

GroupM.o: GroupM.c ../include/GroupM.h ../include/Group.h ../include/dataStructure/HashMap.h ../include/dataStructure/GenQueue.h
	$(CC) $(CFLAGS) -c GroupM.c

clean:
	-rm $(TARGET) *.o

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)

