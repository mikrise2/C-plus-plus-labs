all: lab-05_c-io

lab-05_c-io : obj obj/clist.o obj/point_list.o obj/main.o
	gcc obj/clist.o obj/point_list.o obj/main.o -o lab-05_c-io
obj :
	mkdir -p obj

obj/point_list.o: src/point_list.c include/point_list.h
	gcc -c -Iinclude src/point_list.c -o obj/point_list.o

obj/clist.o : src/clist.c include/clist.h
	gcc -c -Iinclude src/clist.c -o obj/clist.o

obj/main.o : src/main.c
	gcc -c -Iinclude src/main.c -o obj/main.o

clean :
	rm -rf obj/
	rm lab-05_c-io
