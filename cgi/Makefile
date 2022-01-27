# cgi scripts

all: main.o get.o
	g++ main.cpp -o main.cgi
	g++ get.o -o get.cgi
	g++ getwp.cpp -o getwp.cgi
	g++ sed.cpp -o sed.cgi

main.o:
	g++ -c main.cpp -o main.o

get.o:
	g++ -c get.cpp -o get.o



.PHONY: clean
clean:
	rm *.cgi *.o