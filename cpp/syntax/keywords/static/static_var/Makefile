
BASE = static_var
CC   = gcc
CXX 	 = g++
CFLAGS   = -Wall 
CXXFLAGS = `pkg-config --libs opencv`
INCLUDE  =  `pkg-config --cflags opencv`
TARGET   = $(BASE)
LIBPATH  = 
vpath %.h ./

OBJS     =$(BASE).o pt1.o pt2.o
SRCS     =$(BASE).cpp pt1.cpp pt2.cpp


all:$(OBJS)
	$(CXX)  -o $(TARGET) $(OBJS)   $(CXXFLAGS) 

$(OBJS):$(SRCS)
	$(CXX)  $(INCLUDE) -c $^

.PHONY:clean
clean:
	rm -f *.o
	rm -f $(TARGET)
