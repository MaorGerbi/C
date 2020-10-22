# this is my target					/* Update the out file name */
TARGET = Client.out				


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)			/* Compiler flags */
CFLAGS = -ansi -pedantic -Wall -Werror -g		
	
# Include directory						/* Relative to the Makefile location */
INC_DIR = ../include 					 

CFLAGS += -I$(INC_DIR)


# All .c files in this directory are my sources	 /* All the files to be compiled */
SOURCES = Client.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources /* if cant find the h fime - write: "INC_DIR*/
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  

Client.o: Client.c
	$(CC) $(CFLAGS) -c Client.c  

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	  
	
