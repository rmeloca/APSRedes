############################# Makefile ##########################
all:
	gcc -c bitStuffing.c -Wall -ggdb
	gcc -o bitStuffing bitStuffing.o -Wall -ggdb
	
	gcc -c byteStuffing.c -Wall -ggdb
	gcc -o byteStuffing byteStuffing.o -Wall -ggdb
	
	gcc -c byteCounting.c -Wall -ggdb
	gcc -o byteCounting byteCounting.o -Wall -ggdb
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf bitStuffing
