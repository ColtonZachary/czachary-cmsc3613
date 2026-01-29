all: p01
p01: clean main.o utility.o 
	g++ -o p01 main.o utility.o 
main.o: main.cpp
	g++ -c -g main.cpp
utility.o: utility.cpp
	g++ -c -g utility.cpp
clean:
	rm -f *.o
run: p01
	./p01