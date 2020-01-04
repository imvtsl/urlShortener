#ifndef URLSHORTENERFACTORY_HPP
#define URLSHORTENERFACTORY_HPP

#include <iostream>

using namespace std;

class URLShortenerFactory
{
private:
	unsigned long long int Id;
	string shortLink;
	string longLink;

public:
	unsigned long long int getId()
	{
	 	return Id;
	}
	void setId(unsigned long long int id)
	{
		Id = id;
	}
	string getLongLink()
	{
		return longLink;
	}
	void setLongLink(string originalLink)
	{
		longLink = originalLink; 
	}
	string getShortLink()
	{
		return shortLink;
	}
	void setShortLink(string shortenedLink)
	{
		shortLink = shortenedLink; 
	}
	// convert Id to string
	string to_String()
	{
		string result;
		result.append(to_string(Id));
		result.append(" ");
		result.append(shortLink);
		result.append(" ");
		result.append(longLink);
		return result;
	}
};

#endif /* URLSHORTENERFACTORY_HPP */
