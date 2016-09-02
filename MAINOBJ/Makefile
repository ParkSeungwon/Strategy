CC = g++
OBJ = $(wildcard ../OBJS/*.o)
EXE = $(patsubst %.o, ../%.x, $(wildcard *.o))
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)

all : $(EXE)

../%.x : %.o $(OBJ)
	$(CC) $< -o $@ $(OBJ) -lmysqlcppconn $(gtkmmLIB)


