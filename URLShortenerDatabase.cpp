#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"

int getWord(char linestr[2071], int startIndex, char word[14], char delimiter)
{
	int result = startIndex;
	int index = 0;
	while(linestr[result] != delimiter)
	{
		word[index] = linestr[result];
		result++;
		index++;
	}
	word[index] = '\0';

	return result;
}

void getValues(char linestr[2071], URLShortenerFactory &urlShort)
{
	char id[14];
	char shortLink[8];
	char longLink[2049];
	// get id
	int index=0;
	index = getWord(linestr, index, id, ' ');
	
	// get short link
	index++;
	index = getWord(linestr, index, shortLink, ' ');
		
	// get long link
	index++;
	index = getWord(linestr, index, longLink, '\n');
	

	cout << "id:" << id << endl;
	cout << "shortLink:" << shortLink << endl;
	cout << "longLink:" << longLink << endl;
	urlShort.setId(strtoull(id, NULL, 10));
	urlShort.setShortLink(shortLink);
	urlShort.setLongLink(longLink);

	return;
}

bool isPresentOriginalLink(string originalLink, URLShortenerFactory &urlShort)
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
	char linestr[2071];
	while(!feof(fpIn))
	{
		fgets(linestr, 2071, fpIn);
		cout << "linestr is:" << linestr << endl;
		// get originalLink
		getValues(linestr, urlShort);

		if(urlShort.getLongLink() == originalLink)
		{
			result = true;
			break;
		}

		// avoid comparison with \n
		fgets(linestr, 2071, fpIn);
	}
	fclose(fpIn);

	return result;
}

bool isPresentShortLink(string shortenedLink, URLShortenerFactory &urlShort)
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
	char linestr[2071];
	while(!feof(fpIn))
	{
		fgets(linestr, 2071, fpIn);
		cout << "linestr is:" << linestr << endl;
		// get shortenedLink
		getValues(linestr, urlShort);

		if(urlShort.getShortLink() == shortenedLink)
		{
			result = true;
			break;
		}

		// avoid comparison with \n
		fgets(linestr, 2071, fpIn);
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
	char linestr[14];
	fgets(linestr, 14, fpIn);
	string stringResult = linestr;
		
	result = strtoull(stringResult.c_str(), NULL, 10);
		
	return result;
}

void setCurrentRandomId(unsigned long long int newId)
{
	// we are persisting this id in first line of file, store/update it there.
	return;
}

void updateDb(URLShortenerFactory &urlShort)
{
	FILE * fpOut;
	fpOut = fopen("urls.txt", "a");
	if(fpOut==NULL)
	{
		cout << "couldn't open file" << endl;
		// throw exception
		//return (-1);
	}
	
	fputs("\n", fpOut);
	fputs(urlShort.to_String().c_str(), fpOut);
	fclose(fpOut);
	return;
}