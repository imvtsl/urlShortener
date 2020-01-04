#include <iostream>

using namespace std;

#include "URLShortenerFactory.hpp"
#include "URLShortenerDatabase.hpp"

string decimalToBase62(unsigned long long int num)
{
	const char base62Digits[62] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	unsigned long long int temp = num;
	string result;
	if(num == 0)
		return "0";
	while(temp!=0)
	{
		char c = base62Digits[temp%62];
		result.insert(0, 1, c);
		temp = temp/62;
	}
	return result;
}

string generateShortLink(unsigned long long int newId)
{
	return(decimalToBase62(newId));
}

void generate(string originalLink, const char * shortenedLink)
{
	//string result;
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
		newId = id+1;
		urlShort.setId(newId);
		urlShort.setLongLink(originalLink);
		urlShort.setShortLink(generateShortLink(newId));
		setCurrentRandomId(newId);
		updateDb(urlShort);
	}
	shortenedLink = (urlShort.getShortLink()).c_str();
	return;
}

void getOriginalLink(string shortenedLink, const char * originalLink)
{
	//string result = NULL;
	// check if corresponding entry for shortenedLink exists. if yes, return that.
	// else return null.
	URLShortenerFactory urlShort;
	if(isPresentShortLink(shortenedLink, urlShort))
		originalLink = (urlShort.getLongLink()).c_str();
	return;
}

void urlShortener(string queryType)
{
	//URLShortener urlShort;

	char shortenedLink[8];
	char originalLink[2049];
	if(queryType == "generate")
	{
		cin.getline(originalLink, 2048);
		generate(originalLink, shortenedLink);
		//append domain name to shortenedLink.
		string result = "vat.sl/";
		result.append(shortenedLink);
		cout << "Shortened URL is:" << result << endl;
	}
	else if(queryType == "getLink")
	{
		cin.getline(shortenedLink, 7);
		getOriginalLink(shortenedLink, originalLink);
		if(originalLink == NULL)
			cout << "Original URL does not exist in database.";
		else
			cout << "Original URL is:" << originalLink << endl;
	}
	return;
}