CC = g++
CXX = $(CC)
CFLAGS = -ansi -pedantic -Wall -g
CFLAGS += -pthread # ? #
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
SOURCES_NEEDED = thread.cpp mutex.cpp guard.cpp rendezvous.cpp condition_variable.cpp is_arrived.cpp publisher.cpp event.cpp smoke_sensore.cpp agent_details.cpp key.cpp aaa_key.cpp sss_key.cpp sas_key.cpp ass_key.cpp saa_key.cpp aas_key.cpp key_protocol.cpp subscribe_details.cpp event_lut.cpp subscriber.cpp sprinx_controller.cpp controller_agent.cpp event_handler.cpp agent_details.cpp subscriber.cpp dequeuer.cpp geter.cpp extract_handles.cpp  distributor.cpp central_hub.cpp 
# add private source for this target
SOURCES_MINE = insert_and_delivery_events.cpp

TARGET = insert_and_delivery_events

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
