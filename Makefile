all : 
	make -C gtk/
	make -C mysql/
	make -C tcpip/
	make -C src/
	make -C OBJS/

PHONY : clean

clean :
	rm OBJS/*.o MAINOBJ/*.o *.x

ls :
	echo $(EXE)
