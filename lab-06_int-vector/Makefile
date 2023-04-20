all : obj obj/my_vector.o obj/main.o main

obj :
	mkdir -p obj

obj/my_vector.o: src/my_vector.cpp include/my_vector.hpp
	g++ -c -Iinclude src/my_vector.cpp -o obj/my_vector.o

obj/main.o : src/main.cpp
	g++ -c -Iinclude src/main.cpp -std=c++2a -o obj/main.o

main :
	g++ obj/my_vector.o obj/main.o -o lab-06_int-vector

clean :
	rm -rf obj/
	rm lab-06_int-vector
