############################# Makefile ##########################
all:
	gcc -c bitStuffing.c -Wall -ggdb
	gcc -o bitStuffing bitStuffing.o -Wall -ggdb

clean:
	rm -rf *.o
mrproper: clean
	rm -rf bitStuffing
