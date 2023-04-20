all : obj obj/main.o main

obj:
	mkdir -p obj


obj/main.o : src/main.cpp
	g++ -c -Iinclude src/main.cpp -o obj/main.o

main :
	g++ obj/main.o -o lab-11_vector

clean :
	rm -rf obj/
	rm lab-11_int-vector