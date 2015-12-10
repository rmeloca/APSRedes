############################# Makefile ##########################
all:
	gcc -c bitStuffing.c -Wall -ggdb
	gcc -o bitStuffing bitStuffing.o -Wall -ggdb
	
	gcc -c byteStuffing.c -Wall -ggdb
	gcc -o byteStuffing byteStuffing.o -Wall -ggdb
	
	gcc -c byteCounting.c -Wall -ggdb
	gcc -o byteCounting byteCounting.o -Wall -ggdb
	
	gcc -c info_raw_ip.c -Wall -ggdb
	gcc -o desfragmentador info_raw_ip.o -Wall -ggdb
	
clean:
	rm -rf *.o
mrproper: clean
	rm -rf bitStuffing byteStuffing byteCounting desfragmentador
