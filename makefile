all: list.o list_test.o
	gcc list.o list_test.o -o target_bin 

	list.o: list.c list.h
		gcc -I . -c list.c 
     		
	list_test: list_test.c list.c
		gcc -I . -c list_test.c
     		
	clean:
		rm -rf *.o
		rm target_bin 
