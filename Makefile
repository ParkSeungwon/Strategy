CC = g++
C_OPTION = -g -c
OBJ = main.o  gtkmain.o #Util.o Unit.o Weapon.o 

gtkmmCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)
	
war : $(OBJ)
	$(CC) -o war $(OBJ) $(gtkmmLIB)
test : test.cc
	g++ test.cc -o test `pkg-config gtkmm-3.0 --cflags --libs`
	
main.o : main.cpp
	$(CC) $(C_OPTION) main.cpp $(gtkmmCFLAG) 
gtkmain.o : gtkmain.cpp
	$(CC) $(C_OPTION) gtkmain.cpp $(gtkmmCFLAG)
time.o :
Util.o :
Unit.o :
Weapon.o :
Terrain.o :
test.o :
gtkmap.o :
	$(CC) $(C_OPTION) main.cc $(gtkmmCFLAG) 
blank.o :
