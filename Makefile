all: main

main: main.out
	g++ main.out -o main && echo success

main.out : main.cpp main.h
	g++ -c main.cpp -o main.out && echo success

clean:
	rm  *.txt *.out main