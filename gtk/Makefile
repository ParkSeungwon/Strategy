CFLAG = -g -c -std=c++11 -fmax-errors=1
INCLUDE = -I../ -I../src
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags) #-I$(ROOT)
CC = g++
OBJ = $(patsubst %.cc, ../OBJS/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../OBJS/%.x, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../OBJS/%.o : %.cc 
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

../OBJS/%.x : %.cpp
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

