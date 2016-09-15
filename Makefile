all : 
	make -C gtk/
	make -C src/
	make -C OBJS/

PHONY : clean

clean :
	rm OBJS/*.o OBJS/*.x *.x

ls :
	echo $(EXE)
