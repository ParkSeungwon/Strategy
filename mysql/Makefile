CFLAG = -g -c -std=c++11 -fmax-errors=3
INCLUDE = -I../
CC = g++
OBJ = $(patsubst %.cc, ../OBJS/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, ../MAINOBJ/%.o, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

../OBJS/%.o : %.cc 
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@

../MAINOBJ/%.o : %.cpp
	$(CC) $(INCLUDE) $(CFLAG) $< -o $@

