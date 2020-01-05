all: main

main: main.o URLShortener.o URLShortenerDatabase.o logger.o
	g++ -o main main.o URLShortener.o URLShortenerDatabase.o logger.o 

main.o: main.cpp URLShortener.hpp logger.hpp
	g++ -c main.cpp

URLShortener.o: URLShortener.cpp URLShortener.hpp
	g++ -c URLShortener.cpp

URLShortenerDatabase.o: URLShortenerDatabase.cpp URLShortenerDatabase.hpp
	g++ -c URLShortenerDatabase.cpp

logger.o: logger.cpp logger.hpp
	g++ -c logger.cpp

clean:
	rm main main.o URLShortener.o URLShortenerDatabase.o logger.o