

webstore:	Main.o
	g++	Main.o	-o webstore

Main.o:
	g++ -std=c++11	-c Main.cpp -o Main.o

