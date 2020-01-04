#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"

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
	const int ID_LENGTH = 13;
	const int SHORT_LINK_LENGTH = 7;
	const int LONG_LINK_LENGTH = 2048;

	char id[ID_LENGTH+1];
	char shortLink[SHORT_LINK_LENGTH+1];
	char longLink[LONG_LINK_LENGTH+1];
	// get id
	int index=0;
	index = getWord(linestr, index, id, ' ');
	// validate id is null terminated, has proper length. handle exception

	// get short link
	index++;
	index = getWord(linestr, index, shortLink, ' ');
	// validate shortLink is null terminated, has proper length. handle exception
		
	// get long link
	index++;
	index = getWord(linestr, index, longLink, '\0');
	// validate longLink is null terminated, has proper length. handle exception

	//cout << "id:" << id << endl;
	//cout << "shortLink:" << shortLink << endl;
	//cout << "longLink:" << longLink << endl;
	urlShort.setId(strtoull(id, NULL, 10));
	urlShort.setShortLink(shortLink);
	urlShort.setLongLink(longLink);

	return;
}

bool isPresentOriginalLink(const string originalLink, URLShortenerFactory &urlShort)
{
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
		// fgets appends \0 character
		// validate linestr is null terminated string. handle exception
		//cout << "linestr is:" << linestr << endl;
		// get originalLink
		getValues(linestr, urlShort);

		if(urlShort.getLongLink() == originalLink)
		{
			result = true;
			break;
		}

		// avoid comparison with \n
		fgets(linestr, 2, fpIn);
	}
	fclose(fpIn);

	return result;
}

bool isPresentShortLink(const string shortenedLink, URLShortenerFactory &urlShort)
{
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
		// fgets appends \0 character
		// validate linestr is null terminated string. handle exception
		//cout << "linestr is:" << linestr << endl;
		// get shortenedLink
		getValues(linestr, urlShort);

		if(urlShort.getShortLink() == shortenedLink)
		{
			result = true;
			break;
		}

		// avoid comparison with \n
		fgets(linestr, 2, fpIn);
	}
	fclose(fpIn);

	return result;
}

unsigned long long int getCurrentRandomId()
{
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
	// fgets appends \0 character
	// validate linestr is null terminated string. handle exception
	string stringResult = linestr;
		
	result = strtoull(stringResult.c_str(), NULL, 10);
	// validate result. handle exception if any.

	return result;
}

void setCurrentRandomId(const unsigned long long int newId)
{
	// we are persisting this id in first line of file, store/update it there.
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
	FILE * fpOut;
	fpOut = fopen("url.txt", "a");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	fputs("\n", fpOut);
	string dbLine = urlShort.to_String();
	cout << "dbLine is:" << dbLine << endl;
	fputs(dbLine.c_str(), fpOut);
	fclose(fpOut);

	return;
}