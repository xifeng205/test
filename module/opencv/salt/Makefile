
BASE = salt
CC   = gcc
CXX 	 = g++
CFLAGS   = -Wall 
CXXFLAGS = `pkg-config --libs opencv`
INCLUDE  =  `pkg-config --cflags opencv`
TARGET   = $(BASE)
LIBPATH  = 
vpath %.h ./

OBJS     =$(BASE).o 
SRCS     =$(BASE).cpp


all:$(OBJS)
	$(CXX)  -o $(TARGET) $(OBJS)   $(CXXFLAGS) 

$(OBJS):$(SRCS)
	$(CXX)  $(INCLUDE) -c $^

.PHONY:clean
clean:
	rm -f *.o
	rm -f $(TARGET)
