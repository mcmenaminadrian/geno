geno: geno.o
	g++ -g -o geno geno.o
geno.o: geno.cpp geno.hpp creature.hpp
	g++ -c geno.cpp -o geno.o
