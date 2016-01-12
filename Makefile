CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3
OBJ = Util.o Unit.o Weapon.o Waypoint.o time.o Terrain.o map.o point.o bitmap.o blank.o

gtkmmCFLAG = $(shell pkg-config gtkmm-3.0 --cflags)
gtkmmLIB = $(shell pkg-config gtkmm-3.0 --libs)
	
all : $(OBJ)

test : test.cc
	g++ -g -std=c++11 -fmax-errors=5 -o test test.cc
	
main.o : main.cpp
	$(CC) $(C_OPTION) main.cpp $(gtkmmCFLAG) 
gtkmain.o : gtkmain.cpp
	$(CC) $(C_OPTION) gtkmain.cpp $(gtkmmCFLAG)
time.o : time.cc time.h
	$(CC) $(C_OPTION) time.cc
Util.o : Util.cc Util.h
	$(CC) $(C_OPTION) Util.cc
Unit.o : Unit.cc Unit.h
	$(CC) $(C_OPTION) Unit.cc
Waypoint.o : Waypoint.cc Waypoint.h
	$(CC) $(C_OPTION) Waypoint.cc
point.o : point.cpp point.hpp
	$(CC) $(C_OPTION) point.cpp
bitmap.o : bitmap.cc bitmap.h
	$(CC) $(C_OPTION) bitmap.cc
map.o : map.cc map.h
	$(CC) $(C_OPTION) map.cc
Weapon.o : Weapon.cc Weapon.h
	$(CC) $(C_OPTION) Weapon.cc
Terrain.o : Terrain.cc Terrain.h
	$(CC) $(C_OPTION) Terrain.cc
test.o : test.cc
	$(CC) $(C_OPTION) test.cc
gtkmap.o : 
	$(CC) $(C_OPTION) main.cc $(gtkmmCFLAG) 
blank.o : blank.cc
	$(CC) $(C_OPTION) blank.cc  
cout.o : cout.cc cout.h
	$(CC) $(C_OPTION) cout.cc
