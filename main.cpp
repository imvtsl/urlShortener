#include <iostream>

using namespace std;

class URLShortener
{
private:
	int Id;
	string shortLink;
	string longLink;

public:
	int getId()
	{
	 	return Id;
	}
	void setId(int id)
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
};

bool isPresentOriginalLink(string originalLink, urlShortener &urlShort)
{
	bool result = false;
	// check database to see if orginal link is there.
	// if yes update urlShort too.
	return result;
}

bool isPresentShortLink(string shortenedLink, urlShortener &urlShort)
{
	bool result = false;
	// check database to see if orginal link is there.
	// if yes update urlShort too.
	return result;
}

int getCurrentRandomId()
	{
		int result;
		// we are persisting this id in first line of file, get that.
		return result;
	}
	void setCurrentRandomId()
	{
		// we are persisting this id in first line of file, store it there.
		return;
	}

	void updateDb(URLShortener &urlShort)
	{
		return;
	}

	string generate(string originalLink)
	{
		string result;
		URLShortener urlShort;
		int id;
		int newId;
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
		result = urlShort.getShortLink();
		return result;
	}

	string getOriginalLink(string shortenedLink)
	{
		string result = NULL;
		// check if corresponding entry for shortenedLink exists. if yes, return that.
		// else return null.
		URLShortener urlShort;
		if(isPresentShortLink(shortenedLink, urlShort))
			result = urlShort.getLongLink();
		return result;
	}



void urlShortener(string queryType)
{
	//URLShortener urlShort;

	string shortenedLink;
	string originalLink;
	if(queryType == "generate")
	{
		cin >> originalLink;
		shortenedLink = generate(originalLink);
		//append domain name to shortenedLink.
		cout << "Shortened URL is:" << shortenedLink << endl;
	}
	else if(queryType == "getLink")
	{
		cin >> shortenedLink;
		originalLink = getOriginalLink(shortenedLink);
		if(originalLink == NULL)
			cout << "Original URL does not exist in database."
		else
			cout << "Original URL is:" << originalLink << endl;
	}
	return;
}

int main()
{
	string queryType;
	while(true)
	{
		cout << "Enter 'generate' to shorten a URL." << endl;
		cout << "Enter 'getLink' to get original URL." << endl;
		cin >> queryType;
		urlShortener(queryType);	
	}
	return 0;
}