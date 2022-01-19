all: main.o
	g++ main.cpp -o main.cgi

main.o:
	g++ -c main.cpp -o main.o

.PHONY: clean
clean:
	rm main.cgi *.o