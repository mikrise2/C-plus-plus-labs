all: lab-04_intrusive-list

lab-04_intrusive-list : obj obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab-04_intrusive-list
obj :
	mkdir -p obj

obj/clist.o : src/clist.c include/clist.h
	gcc -c -Iinclude src/clist.c -o obj/clist.o

obj/main.o : src/main.c
	gcc -c -Iinclude src/main.c -o obj/main.o

clean :
	rm -rf obj/
	rm lab-04_intrusive-list
