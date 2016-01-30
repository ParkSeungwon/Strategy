CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

gtkmmCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)
	
all : $(OBJ)
	make -C gtk/

test : test.cc
	g++ -g -std=c++11 -fmax-errors=5 -o test test.cc
	
%.o : %.cc 
	$(CC) $(C_OPTION) $<

clean :
	rm *.o test
