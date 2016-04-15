CFLAG = -g -std=c++11 
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

all : server.x client.x

server.x : server.cc ../tcpip.cc $(OBJ)
	g++ -o server.x server.o ../tcpip.o 
	
client.x : client.cc ../tcpip.cc $(OBJ)
	g++ -o client.x client.o ../tcpip.o

%.o : %.cc
	$(CC) -c $< $(CFLAG)


clean : 
	rm *.o server.x client.x
#	./$@
