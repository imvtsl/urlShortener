#include <iostream>
#include <algorithm>

using namespace std;

#include "URLShortenerDatabase.hpp"

int getWord(const string linestr, const int startIndex, char * word, const char delimiter)
{
	int lenLine = linestr.size();
	int result = startIndex;
	int index = 0;
	while((linestr[result] != delimiter) && (result <= (lenLine-1)))
	{
		word[index] = linestr[result];
		result++;
		index++;
	}
	word[index] = '\0';

	return result;
}

void getValues(const string linestr, URLShortenerFactory &urlShort)
{
	cerr << "Inside getValues:" << endl;
	cerr << "linestr is:" << linestr << endl;

	const int ID_LENGTH = 13;
	const int SHORT_LINK_LENGTH = 7;
	const int LONG_LINK_LENGTH = 2048;

	char id[ID_LENGTH+1];
	char shortLink[SHORT_LINK_LENGTH+1];
	char longLink[LONG_LINK_LENGTH+1];
	// get id
	int index=0;
	index = getWord(linestr, index, id, ' ');
	cerr << "id is:" << id << endl;
	// validate id is null terminated, has proper length. handle exception

	// get short link
	index++;
	index = getWord(linestr, index, shortLink, ' ');
	cerr << "shortLink is:" << shortLink << endl;
	// validate shortLink is null terminated, has proper length. handle exception
		
	// get long link
	index++;
	index = getWord(linestr, index, longLink, '\0');
	cerr << "longLink is:" << longLink << endl;
	// validate longLink is null terminated, has proper length. handle exception

	urlShort.setId(strtoull(id, NULL, 10));
	urlShort.setShortLink(shortLink);
	urlShort.setLongLink(longLink);

	return;
}

string removeChar(string linestring, char c)
{
	linestring.erase(remove(linestring.begin(), linestring.end(), c), linestring.end());
	return linestring;
}

bool isPresentOriginalLink(const string originalLink, URLShortenerFactory &urlShort)
{
	cerr << "Inside isPresentOriginalLink:" << endl;
	cerr << "originalLink is:" << originalLink << endl;

	bool result = false;
	// check database to see if orginal link is there.
	// if yes update urlShort too.
	FILE * fpIn;
	fpIn = fopen("url.txt", "r");
	if(fpIn==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	const int MAX_DB_LINE_LENGTH = 2070;
	char linestr[MAX_DB_LINE_LENGTH+1];
	while(!feof(fpIn))
	{
		fgets(linestr, MAX_DB_LINE_LENGTH+1, fpIn);
		cerr << "linestr is:" << linestr << endl;
		// validate linestr is null terminated string. handle exception
		// fgets appends \0 character
		// it is also fetching \n, we need to remove it.
		// remove \n from linestr
		string linestring = removeChar(linestr, '\n');
		cerr << "linestring is:" << linestring << endl;
		
		// get originalLink
		getValues(linestring, urlShort);
		cerr << "urlShort.getLongLink() returns:" << urlShort.getLongLink() << endl;

		if(urlShort.getLongLink() == originalLink)
		{
			result = true;
			break;
		}
	}
	fclose(fpIn);

	cerr << "result is:" << boolalpha << result << endl;
	return result;
}

bool isPresentShortLink(const string shortenedLink, URLShortenerFactory &urlShort)
{
	cerr << "Inside isPresentShortLink:" << endl;
	cerr << "shortenedLink is:" << shortenedLink << endl;

	bool result = false;
	// check database to see if orginal link is there.
	// if yes update urlShort too.
	FILE * fpIn;
	fpIn = fopen("url.txt", "r");
	if(fpIn==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	const int MAX_DB_LINE_LENGTH = 2070;
	char linestr[MAX_DB_LINE_LENGTH+1];
	while(!feof(fpIn))
	{
		fgets(linestr, MAX_DB_LINE_LENGTH+1, fpIn);
		cerr << "linestr is:" << linestr << endl;
		// validate linestr is null terminated string. handle exception
		// fgets appends \0 character
		// it is also fetching \n, we need to remove it.
		// remove \n from linestr
		string linestring = removeChar(linestr, '\n');
		cerr << "linestring is:" << linestring << endl;
		
		// get shortenedLink
		getValues(linestring, urlShort);
		cerr << "urlShort.getShortLink() returns:" << urlShort.getShortLink() << endl;

		if(urlShort.getShortLink() == shortenedLink)
		{
			result = true;
			break;
		}
	}
	fclose(fpIn);

	cerr << "result is:" << boolalpha << result << endl;
	return result;
}

unsigned long long int getCurrentRandomId()
{
	cerr << "Inside getCurrentRandomId:" << endl;

	unsigned long long int result;
	// we are persisting this id in first line of file, get that.
	FILE * fpIn;
	fpIn = fopen("currentId.txt", "r");
	if(fpIn==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	const int ID_LENGTH = 13;
	char linestr[ID_LENGTH+1];
	fgets(linestr, ID_LENGTH+1, fpIn);

	cerr << "linestr is:" << linestr << endl;
	// fgets appends \0 character
	// validate linestr is null terminated string. handle exception
	
	string stringResult = linestr;
		
	result = strtoull(stringResult.c_str(), NULL, 10);
	cerr << "result is:" << result << endl;
	// validate result. handle exception if any.

	return result;
}

void setCurrentRandomId(const unsigned long long int newId)
{
	// we are persisting this id in first line of file, store/update it there.

	cerr << "Inside setCurrentRandomId:" << endl;
	cerr << "newId is:" << newId << endl;

	FILE * fpOut;
	fpOut = fopen("currentId.txt", "w+");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	fputs(to_string(newId).c_str(), fpOut);
	fclose(fpOut);
	
	return;
}

void updateDb(URLShortenerFactory &urlShort)
{
	cerr << "Inside updateDb:" << endl;

	FILE * fpOut;
	fpOut = fopen("url.txt", "a");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	string dbLine = urlShort.to_String();
	cerr << "dbLine is:" << dbLine << endl;

	fputs("\n", fpOut);
	fputs(dbLine.c_str(), fpOut);
	fclose(fpOut);

	return;
}