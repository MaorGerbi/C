# this is my target
TARGET = DLL.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ./ 
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = DLL.c DLLTest.c
         
# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  

DLLTest.o: DLLTest.c DLL.h
	$(CC) $(CFLAGS) -c DLLTest.c  

DLL.o: DLL.c DLL.h
	$(CC) $(CFLAGS) -c DLL.c  
           

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
