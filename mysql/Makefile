CC = g++
C_OPTION = -g -c -std=c++11 -fmax-errors=3
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

LIB = -L/usr/local/lib -L/usr/lib
INC = /usr/local/include
	
#sql : $(OBJ)
#	$(CC) -o sql $(OBJ) $(LIB) -lmysqlcppconn 

%.o : %.cc %.h
	$(CC) $(C_OPTION) $< -I$(INC)

clean :
	rm *.o 
