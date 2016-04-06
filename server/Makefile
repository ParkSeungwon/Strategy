CFLAG = -g -std=c++11 
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

all : server client

server : server.cc $(OBJ)
	g++ -o server server.o ../tcpip.o 
	
client : client.cc $(OBJ)
	g++ -o client client.o ../tcpip.o

%.o : %.cc
	$(CC) -c $< $(CFLAG)


clean : 
	rm *.o server client
#	./$@
