#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"
#include "URLShortenerDatabase.hpp"

string decimalToBase62(const unsigned long long int num);

string generateShortLink(const unsigned long long int newId);

void generate(const string originalLink, char * shortenedLink);

void getOriginalLink(const string shortenedLink, char * originalLink);

void urlShortener(string queryType);