all: p02
p02: clean main.o utility.o
	g++ -o p02 main.o utility.o
main.o: main.cpp
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
clean:
	rm -f *.o
	