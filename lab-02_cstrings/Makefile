all : obj obj/str.o obj/test_str.o obj/test.o test

obj :
	mkdir -p obj

obj/str.o : src/str.c include/str.h
	gcc -c -Iinclude src/str.c -o obj/str.o

obj/test.o : src/test.c
	gcc -c -Iinclude src/test.c -o obj/test.o

obj/test_str.o: src/test_str.c include/test_str.h
	gcc -c -Iinclude src/test_str.c -o obj/test_str.o
test :
	gcc obj/str.o obj/test_str.o obj/test.o -o lab-02_cstrings

clean :
	rm -rf obj/
	rm  lab-02_cstrings