#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"

int getWord(const string linestr, const int startIndex, char * word, const char delimiter);

void getValues(const string linestr, URLShortenerFactory &urlShort);

bool isPresentOriginalLink(const string originalLink, URLShortenerFactory &urlShort);

bool isPresentShortLink(const string shortenedLink, URLShortenerFactory &urlShort);

unsigned long long int getCurrentRandomId();

void setCurrentRandomId(const unsigned long long int newId);

void updateDb(URLShortenerFactory &urlShort);