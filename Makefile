all : 
	make -C gtk/
	make -C mysql/
	make -C server/
	make -C src/
	make -C MAINOBJ/

PHONY : clean

clean :
	rm OBJS/*.o MAINOBJ/*.o *.x

ls :
	echo $(EXE)
