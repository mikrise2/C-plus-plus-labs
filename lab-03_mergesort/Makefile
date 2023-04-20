all: lab-03_mergesort

lab-03_mergesort : obj obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab-03_mergesort
obj :
	mkdir -p obj

obj/mergesort.o : src/mergesort.c include/mergesort.h
	gcc -c -Iinclude src/mergesort.c -o obj/mergesort.o

obj/main.o : src/main.c
	gcc -c -Iinclude src/main.c -o obj/main.o

clean :
	rm -rf obj/
	rm lab-03_mergesort