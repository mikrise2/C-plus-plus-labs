all : obj obj/minimal_smoke_test.o obj/smoke_test.o

obj :
	mkdir -p obj

obj/minimal_smoke_test.o : tests/minimal_smoke_test.cpp include/linq.hpp
	g++ -Iinclude tests/minimal_smoke_test.cpp -o lab-14_linq-minimal

obj/smoke_test.o : tests/smoke_test.cpp include/linq.hpp
	g++ -Iinclude tests/smoke_test.cpp -o lab-14_linq

clean :
	rm -rf obj/
	rm lab-14_linq