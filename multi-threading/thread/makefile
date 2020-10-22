# this is my target
TARGET = thread_test.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -g -Wall -Werror

# Include directory
INC_DIR = ./include
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = thread_test.cpp thread.cpp
# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.cpp=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lpthread  
		
thread_test.o : thread_test.cpp mu_test.h thread.hpp
	$(CC) $(CFLAGS) -c  thread_test.cpp
				
thread.o : thread.cpp thread.hpp
	$(CC) $(CFLAGS) -c  thread.cpp
	
clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
