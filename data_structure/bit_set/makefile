# this is my target
TARGET =bit_set.out


# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -g

# Include directory

INC_DIR += include

CFLAGS += -I $(INC_DIR)


# All .c files in this directory are my sources
SOURCES =  bit_set_test.cpp

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.cpp=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC)  -o $(TARGET) $(OBJECTS)

bit_set_test.o: bit_set_test.cpp bit_set.hpp
	$(CC) $(CFLAGS) -c bit_set_test.cpp
	
#bit_set.o: bit_set.cpp bit_set.hpp
#	$(CC) $(CFLAGS) -c bit_set.cpp


clean:
	-rm $(TARGET) *.o

run:  $(TARGET)

	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
