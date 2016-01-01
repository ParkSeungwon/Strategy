CC = g++
C_OPTION = -g -c -std=c++11
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
	$(CC) $(C_OPTION) -o Weapon.o Weapon.cc
Terrain.o :
test.o :
gtkmap.o :
	$(CC) $(C_OPTION) main.cc $(gtkmmCFLAG) 
blank.o :
