CFLAG = -g -c -std=c++11 -fmax-errors=3
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
#EXE = $(patsubst %.cc, %, $(SRC))
all : show 

show : $(OBJ)
	g++ -o show $(OBJ) $(GTKLIB)
	./show &
exe : $(EXE)

%.o : %.cc 
	$(CC) $(GTKCFLAG) $(CFLAG) $<

clean :
	rm *.o
