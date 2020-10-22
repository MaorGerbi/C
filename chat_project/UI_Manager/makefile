# this is my target
TARGET = UI.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ../include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = UI_Manager_Test.c UI_Manager.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  
	
 UI_Manager_Test.c.o: UI_Manager.c ../include/UI_Menger.h
	$(CC) $(CFLAGS) -c UI_Menger_Test.c
		
UI_Menger.o: UI_Manager.c ../include/UI_Manager.h
	$(CC) $(CFLAGS) -c UI_Manger.c     

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
