# this is my target
TARGET = shared_pointer.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -g

# Include directory

INC_DIR += include

CFLAGS += -I $(INC_DIR)


# All .c files in this directory are my sources
SOURCES =  test_shared_pointer.cpp

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.cpp=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC)  -o $(TARGET) $(OBJECTS)

test_shared_pointer.o: test_shared_pointer.cpp shared_pointer.hpp
	$(CC) $(CFLAGS) -c test_shared_pointer.cpp
	
#bit_set.o: bit_set.cpp bit_set.hpp
#	$(CC) $(CFLAGS) -c bit_set.cpp


clean:
	-rm $(TARGET) *.o

run:  $(TARGET)

	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
