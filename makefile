all: main

main: main.o URLShortener.o URLShortenerDatabase.o 
	g++ -o main main.o URLShortener.o URLShortenerDatabase.o 

main.o: main.cpp URLShortener.hpp logger.hpp
	g++ -c main.cpp

URLShortener.o: URLShortener.cpp URLShortener.hpp
	g++ -c URLShortener.cpp

URLShortenerDatabase.o: URLShortenerDatabase.cpp URLShortenerDatabase.hpp
	g++ -c URLShortenerDatabase.cpp

clean:
	rm main main.o URLShortener.o URLShortenerDatabase.o