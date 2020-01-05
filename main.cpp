#include <iostream>
#include <fstream>

using namespace std;

#include "URLShortener.hpp"
#include "logger.hpp"

int main()
{
	// redirect cerr to log.txt
	fstream file; 
    file.open("log.txt", ios::out);
    streambuf * stream_buffer_cerr = redirectCerrToFile(file, cerr);

    const int QUERY_SIZE = 10;
	char queryType[QUERY_SIZE];

	while(true)
	{
		cout << "Enter 'generate' to shorten a URL." << endl;
		cout << "Enter 'getLink' to get original URL." << endl;
		cin.getline(queryType, QUERY_SIZE-1);
		cerr << endl << "inside main:" << endl;
		cerr << "queryType is:" << queryType << endl;
		// validate and handle queryType

		urlShortener(queryType);	
	}

	// redirect cerr back to console
	redirectCerrToConsole(cerr, stream_buffer_cerr);
	file.close();

	return 0;
}