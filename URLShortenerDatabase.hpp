#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"

int getWord(char linestr[2071], int startIndex, char word[14], char delimiter);

void getValues(char linestr[2071], URLShortenerFactory &urlShort);

bool isPresentOriginalLink(string originalLink, URLShortenerFactory &urlShort);

bool isPresentShortLink(string shortenedLink, URLShortenerFactory &urlShort);

unsigned long long int getCurrentRandomId();

void setCurrentRandomId(unsigned long long int newId);

void updateDb(URLShortenerFactory &urlShort);