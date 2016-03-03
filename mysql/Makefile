
CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

LIB = /usr/local/lib
INC = /usr/local/include
	
all : $(OBJ)
	
%.o : %.cc %.h
	$(CC) $(C_OPTION) $< -I$(INC)

clean :
	rm *.o 
