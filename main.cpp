#include <iostream>

using namespace std;

#include "URLShortener.hpp"

int main()
{
	const int QUERY_SIZE = 10;
	char queryType[QUERY_SIZE];
	while(true)
	{
		cout << "Enter 'generate' to shorten a URL." << endl;
		cout << "Enter 'getLink' to get original URL." << endl;
		cin.getline(queryType, QUERY_SIZE-1);
		// validate and handle queryType
		urlShortener(queryType);	
	}
	return 0;
}