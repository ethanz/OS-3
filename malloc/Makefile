libmem.so: mem.o
	gcc -shared -o libmem.so mem.o -g

mem.o: mem.c
	gcc -c -fpic mem.c -Wall -Werror -g

clean:
	rm -f libmem.so mem.o
