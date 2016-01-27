CFLAG = -g -c -std=c++11 -fmax-errors=3
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
POBJ = $(wildcard ../*.o)

all : show 

show : $(OBJ)
	g++ -o show $(OBJ) $(POBJ) $(GTKLIB) 
#./show

%.o : %.cc 
	$(CC) $(GTKCFLAG) $(CFLAG) $<

clean :
	rm *.o
