ROOT = $(HOME)/Programming/Strategy
OBJ_DIR = $(ROOT)/OBJS
MAIN_DIR = $(ROOT)/MAINOBJ
CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3 -I$(ROOT)
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(wildcard *.cc))
MAIN_OBJ = $(patsubst %.cpp, $(MAIN_DIR)/%.o, $(wildcard *.cpp))
OBJ_ALL = $(wildcard $(OBJ_DIR)/*.o)
EXE =  $(patsubst $(MAIN_DIR)/%.o, %.x, $(wildcard $(MAIN_DIR)/*.o))
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)
CPPFLAGS = -pedantic
	
all : $(OBJ) $(MAINOBJ) $(EXE)
	make -C gtk/
	make -C mysql/
	make -C server/

second : 

%.x : $(MAIN_DIR)/%.o
	$(CC) -o $@ $< $(OBJ_ALL) -lmysqlcppconn $(gtkmmLIB) 
	
$(OBJ_DIR)/%.o : %.cc 
	$(CC) $(C_OPTION) $< -o $@

$(MAIN_DIR)/%.o : %.cpp 
	$(CC) $(C_OPTION) $< -o $@

clean :
	rm $(OBJ_DIR)/* $(MAIN_DIR)/* *.x

ls :
	echo $(EXE)
