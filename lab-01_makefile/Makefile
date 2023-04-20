all : obj obj/io.o obj/util.o obj/algorithm.o obj/main.o main

obj :
	mkdir -p obj

obj/algorithm.o : src/algorithm.c include/algorithm.h
	gcc -c -Iinclude src/algorithm.c -o obj/algorithm.o

obj/io.o : src/io.c include/io.h
	gcc -c -Iinclude src/io.c -o obj/io.o

obj/util.o : src/util.c include/util.h
	gcc -c -Iinclude src/util.c -o obj/util.o

obj/main.o : src/main.c
	gcc -c -Iinclude src/main.c -o obj/main.o

main :
	gcc obj/algorithm.o obj/io.o obj/util.o obj/main.o -o lab-01_makefile

clean :
	rm -rf obj/
	rm lab-01_makefile