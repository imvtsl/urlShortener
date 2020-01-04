#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"
#include "URLShortenerDatabase.hpp"

string decimalToBase62(unsigned long long int num);

string generateShortLink(unsigned long long int newId);

void generate(string originalLink, const char * shortenedLink);

void getOriginalLink(string shortenedLink, const char * originalLink);

void urlShortener(string queryType);