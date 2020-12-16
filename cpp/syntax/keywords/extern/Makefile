
BASE = extern
CC   = gcc
CXX 	 = g++
CFLAGS   = -Wall 
CXXFLAGS = `pkg-config --libs opencv`
INCLUDE  =  `pkg-config --cflags opencv`
TARGET   = $(BASE)
LIBPATH  = 
vpath %.hpp ./

OBJS     =$(BASE).o add.o 
SRCS     =$(BASE).cpp add.cpp


all:$(OBJS)
	$(CXX)  -o $(TARGET) $(OBJS)   $(CXXFLAGS) 

$(OBJS):$(SRCS)
	$(CXX)  $(INCLUDE) -c $^

.PHONY:clean
clean:
	rm -f *.o
	rm -f $(TARGET)
