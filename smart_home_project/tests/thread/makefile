CC = g++
CXX = $(CC)
CFLAGS = -ansi -pedantic -Wall -Werror -g
CFLAGS += -pthread #ask
# c++
CXXFLAGS = $(CFLAGS) -std=c++03
# c pre processor
INC_DIR = ../../include
INL_DIR = ../../inl
SRC_DIR = ../../src

CPPFLAGS += -I$(INC_DIR) -I$(INL_DIR)
LDLIBS = -ldl
LDFLAGS = 

# add shared sources that we depend on
SOURCES_NEEDED = thread.cpp mutex.cpp guard.cpp rendezvous.cpp is_arrived.cpp condition_variable.cpp

# add private source for this target
SOURCES_MINE = thread_test.cpp
TARGET = thread_test

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src)) -lpthread  
SOURCES += $(SOURCES_MINE)
OBJECTS := $(SOURCES:.cpp=.o)
all : $(TARGET)
$(TARGET):   $(OBJECTS)
run:  $(TARGET)
	./$(TARGET)
check: clean run
grind: valgrind helgrind
valgrind: #memory leak
	valgrind --tool=drd --log-file=logdrd01.txt ./$(TARGET)
helgrind:  #race conditions  
	valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET) 
clean:
	$(RM) $(TARGET) *.o $(SRC_DIR)/*.o
.PHONY: all clean run check grind valgrind helgrind 
	Collapse
