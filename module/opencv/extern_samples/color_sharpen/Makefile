
BASE = color_sharpen
CC   = gcc
CXX 	 = g++
CFLAGS   = -Wall 
CXXFLAGS = `pkg-config --libs opencv`
INCLUDE  =  `pkg-config --cflags opencv`
TARGET   = $(BASE)
LIBPATH  =-lpthread 
vpath %.h ./

OBJS     =$(BASE).o 
SRCS     =$(BASE).cpp


all:$(OBJS)
	$(CXX)  -o $(TARGET) $(OBJS)   $(CXXFLAGS) $(LIBPATH)

$(OBJS):$(SRCS)
	$(CXX)  $(INCLUDE) -c $^

.PHONY:clean
clean:
	rm -f *.o
	rm -f $(TARGET)
