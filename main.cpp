#include <iostream>

using namespace std;

#include "URLShortener.hpp"

int main()
{
	char queryType[9];
	while(true)
	{
		cout << "Enter 'generate' to shorten a URL." << endl;
		cout << "Enter 'getLink' to get original URL." << endl;
		cin.getline(queryType, 8);
		urlShortener(queryType);	
	}
	return 0;
}