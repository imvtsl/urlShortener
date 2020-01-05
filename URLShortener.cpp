#include <iostream>
#include <cstring>

using namespace std;

#include "URLShortener.hpp"

string decimalToBase62(const unsigned long long int num)
{
	cerr << "Inside decimalToBase62:" << endl;
	cerr << "num is:" << num << endl;

	const string RESULT_NUM_0 = "0";
	if(num == 0)
		return RESULT_NUM_0;

	const int BASE = 62;
	const char base62Digits[BASE] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	unsigned long long int temp = num;
	string result;
	
	while(temp!=0)
	{
		char c = base62Digits[temp%BASE];
		// insert at front
		result.insert(0, 1, c);
		temp = temp/BASE;
	}
	// append null terminated character
	result.push_back('\0');
	cerr << "result is:" << result << endl;
	
	return result;
}

string generateShortLink(const unsigned long long int newId)
{
	return(decimalToBase62(newId));
}

void generate(const string originalLink, char * shortenedLink)
{
	cerr << "inside generate:" << endl;
	cerr << "originalLink is:" << originalLink << endl;

	// validate and handle originalLink
	URLShortenerFactory urlShort;
	unsigned long long int id;
	unsigned long long int newId;
	// check if corresponding entry for originalLink exists. if yes, return that.
	// else create a new entry and return that.
	if(isPresentOriginalLink(originalLink, urlShort))
	{
		cout << "The shortened URL already exists." << endl;
	}
	else
	{
		id = getCurrentRandomId();
		// validate if we have reached limit
		newId = id+1;
		urlShort.setId(newId);
		urlShort.setLongLink(originalLink);
		urlShort.setShortLink(generateShortLink(newId));
		setCurrentRandomId(newId);
		updateDb(urlShort);
	}
	string temp = urlShort.getShortLink();
	strncpy(shortenedLink, temp.c_str(), temp.size()+1);
	return;
}

void getOriginalLink(const string shortenedLink, char * originalLink)
{
	cerr << "inside getOriginalLink:" << endl;
	cerr << "shortenedLink is:" << shortenedLink << endl;

	// validate and handle originalLink
	// check if corresponding entry for shortenedLink exists. if yes, return that.
	// else return null.
	URLShortenerFactory urlShort;
	string temp;
	if(isPresentShortLink(shortenedLink, urlShort))
	{
		temp = urlShort.getLongLink();
		strncpy(originalLink, temp.c_str(), temp.size()+1);
	}
	return;
}

void urlShortener(string queryType)
{
	cerr << "inside urlShortener:" << endl;
	cerr << "queryType is:" << queryType << endl;

	// validate and handle queryType
	const int SHORT_LINK_LENGTH = 7;
	const int ORIGINAL_LINK_LENGTH = 2048;

	char shortenedLink[SHORT_LINK_LENGTH+1];
	char originalLink[ORIGINAL_LINK_LENGTH+1] = "";
	//cout << "queryType is:" << queryType << endl;
	if(queryType == "generate")
	{
		cerr << "inside if generate:" << endl;
		//cerr << "queryType is:" << queryType << endl;
		
		cin.getline(originalLink, ORIGINAL_LINK_LENGTH);
		cerr << "originalLink is:" << originalLink << endl;
		// validate and handle originalLink
		
		generate(originalLink, shortenedLink);
		
		//append domain name to shortenedLink.
		string result = "vat.sl/";
		result.append(shortenedLink);
		cout << "Shortened URL is:" << result << endl;
	}
	else if(queryType == "getLink")
	{
		cerr << "inside getLink:" << endl;

		cin.getline(shortenedLink, SHORT_LINK_LENGTH);
		cerr << "shortenedLink is:" << shortenedLink << endl;
		// validate and handle originalLink

		getOriginalLink(shortenedLink, originalLink);
		// null check on char array
		if(originalLink[0] == '\0')
			cout << "Original URL does not exist in database." << endl;
		else
			cout << "Original URL is:" << originalLink << endl;
	}
	return;
}