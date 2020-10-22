# this is my target
TARGET = ServerAppTest.out

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -g3 -std=gnu99

# include directory
INC_DIR = ../include
INC_DIR_DS = ../include/dataStructure

CFLAGS += -I$(INC_DIR)
CFLAGS += -I$(INC_DIR_DS)


# All .c files in this directory are my sources
SOURCES = ServerApp.c  ServerAppTest.c ../UserManager/UserManager.c ../ServerNet/ServerNet.c ../Protocol/Protocol.c ../GroupM/GroupM.c ../Group/Group.c

# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L../staticLiberies -lHashMap -L../staticLiberies -lDLL -L../staticLiberies -lQueue -o $(TARGET) 

ServerApp.o: ServerApp.c ../include/ServerApp.h ../include/Protocol.h ../include/UserManager.h
	$(CC) $(CFLAGS) -c ServerApp.c 

ServerAppTest.o: ServerAppTest.c 
	$(CC) $(CFLAGS) -c ServerAppTest.c 

UserManager.o: UserManager.c 
	$(CC) $(CFLAGS) -c UserManager.c 

ServerNet.o: ServerNet.c ../include/ServerNet.h ../include/dataStructure/list_itr.h ../include/dataStructure/GenDLL.h
	$(CC) $(CFLAGS) -c ServerNet.c  

GroupM.o: GroupM.c ../include/GroupM.h
	$(CC) $(CFLAGS) -c GroupM.c

Group.o: Group.c ../include/Protocol.h
	$(CC) $(CFLAGS) -c Group.c

Protocol.o: Protocol.c ../include/Protocol.h
	$(CC) $(CFLAGS) -c Protocol.c


clean:
	-rm $(TARGET) *.o

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	
