CFLAG = -g -c -std=c++11 -fmax-errors=3
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
MLIB = -L/usr/local/lib -L/usr/lib
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
POBJ = $(wildcard ../*.o)
MOBJ = $(wildcard ../mysql/*.o)

all : show 

show : $(OBJ) $(POBJ) $(MOBJ)
	g++ -o show $(OBJ) $(POBJ) $(MOBJ) $(GTKLIB) -lmysqlcppconn
#./show

%.o : %.cc 
	$(CC) $(GTKCFLAG) $(CFLAG) $<

clean :
	rm *.o
