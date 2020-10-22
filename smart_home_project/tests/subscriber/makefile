CC = g++
CXX = $(CC)
CFLAGS = -ansi -pedantic -Wall -Werror -g
CFLAGS += -pthread
CFLAGS += -MMD -MP
# c++
CXXFLAGS = $(CFLAGS) -std=c++11
# c pre processor
INC_DIR = ../../include
INL_DIR = ../../inl
SRC_DIR = ../../src

CPPFLAGS += -I$(INC_DIR) -I$(INL_DIR)
LDLIBS = -ldl
LDFLAGS = 

# add shared sources that we depend on
SOURCES_NEEDED = event.cpp agent_details.cpp event_lut.cpp event_key.cpp subscriber.cpp sprinx_controller.cpp event_handler.cpp controller_agent.cpp

# add private source for this target
SOURCES_MINE = subscriber_test.cpp
TARGET =  subscriber_test

SOURCES = $(foreach src, $(SOURCES_NEEDED), $(SRC_DIR)/$(src))
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
	$(RM) $(TARGET) *.o $(TARGET) *.d $(SRC_DIR)/*.o
.PHONY: all clean run check grind valgrind helgrind 
	Collapse

DEPEND = $(OBJECTS:.o=.d)

-include $(DEPEND)
