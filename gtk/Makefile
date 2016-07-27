ROOT = $(HOME)/Programming/Strategy
CFLAG = -g -c -std=c++11 -fmax-errors=3
INCLUDE = -I$(ROOT)
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags) #-I$(ROOT)
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
MLIB = -L/usr/local/lib -L/usr/lib
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
POBJ = $(wildcard ../*.o)
MOBJ = $(wildcard ../mysql/*.o)

all : show.x 

show.x : $(OBJ) $(POBJ) $(MOBJ)
	g++ -o show.x $(OBJ) $(POBJ) $(MOBJ) $(GTKLIB) -lmysqlcppconn
#./show

%.o : %.cc 
	$(CC) $(GTKCFLAG) $(INCLUDE) $(CFLAG) $<

clean :
	rm *.o show.x
