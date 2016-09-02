ROOT = $(HOME)/Programming/Strategy
OBJ_DIR = $(ROOT)/OBJS
MAIN_DIR = $(ROOT)/MAINOBJ
CFLAG = -g -c -std=c++11 -fmax-errors=3
INCLUDE = -I$(ROOT)
CC = g++
OBJ = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, $(MAIN_DIR)/%.o, $(wildcard *.cpp))

all : $(OBJ) $(MAIN_OBJ)

$(OBJ_DIR)/%.o : %.cc 
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

$(MAIN_DIR)/%.o : %.cpp
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $< -o $@

