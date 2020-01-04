all: main

main: main.o URLShortener.o URLShortenerDatabase.o 
	g++ -o main main.o URLShortener.o URLShortenerDatabase.o 

main.o: main.cpp
	g++ -c main.cpp

URLShortener.o: URLShortener.cpp
	g++ -c URLShortener.cpp

URLShortenerDatabase.o: URLShortenerDatabase.cpp
	g++ -c URLShortenerDatabase.cpp

clean:
	rm main main.o URLShortener.o URLShortenerDatabase.o