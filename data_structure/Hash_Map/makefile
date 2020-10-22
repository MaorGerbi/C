# this is my target
TARGET = HahMap.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g

# Include directory
INC_DIR = ./ 
CFLAGS += -I$(INC_DIR)

# All .c files in this directory are my sources
SOURCES = Hash_Test.c Hash_Map.c ../../List_Itr/List_Itr.c ../../Generic_List/DLL.c
         
# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)  
	
Hash_Test.o: Hash_Test.c Hash_Map.h
	$(CC) $(CFLAGS) -c Hash_Test.c  
	
Hash_Map.c.o: Hash_Map.c Hash_Map.h
	$(CC) $(CFLAGS) -c  Hash_Map.c  

List_Itr.o: ../../List_Itr/List_Itr.c  ../../List_Itr/List_Itr/List_Itr.h
	$(CC) $(CFLAGS) -c List_Itr.c  

DLL.o: ../../Generic_List/DLL.c ../../Generic_List/DLL.h
	$(CC) $(CFLAGS) -c DLL.c            

clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
	
