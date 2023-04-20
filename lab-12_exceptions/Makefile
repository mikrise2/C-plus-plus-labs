all : obj obj/matrix.o obj/main.o main

obj :
	mkdir -p obj

obj/main.o : src/main.cpp
	g++ -c -Iinclude src/main.cpp -std=c++2a -o obj/main.o

obj/matrix.o: src/matrix.cpp include/matrix.h
	g++ -c -Iinclude src/matrix.cpp -std=c++2a -o obj/matrix.o

main :
	g++ obj/matrix.o obj/main.o -o lab-12_exceptions

clean :
	rm -rf obj/
	rm lab-12_exceptions
