CFLAG = -g -c -std=c++11 -fmax-errors=3
GTKCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
GTKLIB = $(shell pkg-config gtkmm-3.0 --libs)
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
POBJ = $(wildcard ../*.o)

all : show 

<<<<<<< HEAD
show : $(OBJ)
	g++ -o show $(OBJ) $(GTKLIB) ../file.o
=======
show : $(OBJ) $(POBJ)
	g++ -o show $(OBJ) $(POBJ) $(GTKLIB) 
#./show
>>>>>>> rerere

%.o : %.cc 
	$(CC) $(GTKCFLAG) $(CFLAG) $<

clean :
	rm *.o
