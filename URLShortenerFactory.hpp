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
	void setId(const unsigned long long int newId)
	{
		Id = newId;
	}
	string getLongLink()
	{
		return longLink;
	}
	void setLongLink(const string newLongLink)
	{
		longLink = newLongLink; 
	}
	string getShortLink()
	{
		return shortLink;
	}
	void setShortLink(const string newShortLink)
	{
		shortLink = newShortLink; 
	}
	// convert Id to string
	string to_String()
	{
		string result = to_string(Id);
		result.append(" ");
		result.append(shortLink);
		result.pop_back();
		result.append(" ");
		result.append(longLink);
		result.push_back('\0');
		cout << "inside class, string is:" << result << endl;
		return result;
	}
};

#endif /* URLSHORTENERFACTORY_HPP */
