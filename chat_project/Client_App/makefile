# this is my target
TARGET = client.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g 

# Include directory
INC_DIR = ../include
INC_DIR_DS = ../include/dataStructure

CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(INC_DIR_DS)

# All .c files in this directory are my sources
SOURCES = Client_App_Test.c Client_App.c ../Client_Net/Client_Net.c ../Protocol/Protocol.c ../Multicast/Multicast.c ../UI_Manager/UI_Manager.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L../staticLiberies -lDLL -o $(TARGET)  

Client_App_Test.o: Client_App_Test.c ../include/Client_App.h
	$(CC) $(CFLAGS) -c Client_App_Test.c
	
Client_App.o: Client_App.c ../include/Client_App.h ../include/Client_Net.h ../include/Protocol.h ../include/Multicast.h ../include/UI_Manager.h
	$(CC) $(CFLAGS) -c Client_App.c
		
Client_Net.o: Client_Net.c ../include/Client_Net.h
	$(CC) $(CFLAGS) -c Client_Net.c

Protocol.o: Protocol.c ../include/Protocol.h
	$(CC) $(CFLAGS) -c Protocol.c
	
Multicast.o: Multicast.c ../include/Multicast.h
	$(CC) $(CFLAGS) -c Multicast.c      

UI_Manager.0: UI_Manager.c ../include/UI_Manager.h
	$(CC) $(CFLAGS) -c UI_Manager.c
	
clean:
	-rm $(TARGET) *.o 

run:  $(TARGET)
	./$(TARGET)

gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
