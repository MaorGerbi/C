# this is my target
TARGET = ServerNet.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g

# Include directory
INC_DIR = ../include
INC_DIR_DS = ../include/dataStructure

CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(INC_DIR_DS)

# All .c files in this directory are my sources
SOURCES = ServerNet.c ServerNetTest.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -lDLL -L../Lib -o $(TARGET)

ServerNetTest.o: ServerNetTest.c $(INC_DIR)/ServerNet.h
	$(CC) $(CFLAGS) -c ServerNetTest.c

ServerNet.o: ServerNet.c ../include/ServerNet.h ../include/dataStructure/list_itr.h ../include/dataStructure/GenDLL.h
	$(CC) $(CFLAGS) -c ServerNet.c

clean:
	-rm $(TARGET) *.o

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)


