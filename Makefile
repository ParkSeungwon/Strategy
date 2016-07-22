CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3 -pedantic
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
MYOBJ = $(wildcard mysql/*.o)

gtkmmCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)
	
all : $(OBJ)
	make -C gtk/
	make -C mysql/
	make -C server/
	make test

test : test.cpp $(OBJ)
	g++ -g -std=c++11 -fmax-errors=5 -o test test.cpp $(OBJ) $(MYOBJ) -lmysqlcppconn
	
%.o : %.cc 
	$(CC) $(C_OPTION) $<

clean :
	rm *.o test
