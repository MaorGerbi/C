# this is my target
TARGET = UserManagerTest.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g3 -std=gnu99

# Include directory
INC_DIR = ../include
INC_DIR_DS = ../include/dataStructure

CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(INC_DIR_DS)


# All .c files in this directory are my sources
SOURCES = UserManager.c  UserManagerTest.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L. -lHashMap -o $(TARGET) 

UserManager.o: UserManager.c ../include/UserManager.h
	$(CC) $(CFLAGS) -c UserManager.c 

UserManagerTest.o: UserManagerTest.c 
	$(CC) $(CFLAGS) -c UserManagerTest.c   




clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	  
	
