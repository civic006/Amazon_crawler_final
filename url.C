#include <string>
#include <sstream>

//#include <regex.h>
//#include <sys/types.h>
//#include <string.h>
//#include <stdio.h>

#include <iostream>
using namespace std;

#include "url.h"

const string URL::topLevelDomains[94] = {".aero", ".asia", ".biz", ".cat", ".com", ".coop", ".info", ".int", ".jobs", ".mobi", ".museum", ".name", ".net", ".org", ".pro", ".tel", ".travel", ".xxx", ".edu", ".gov", ".mil", ".ac", ".ad", ".ae", ".af", ".ag", ".ai", ".al", ".am", ".an", ".ao", ".aq", ".ar", ".as", ".at", ".au", ".aw", ".ax", ".az", ".ba", ".bb", ".bd", ".be", ".bf", ".bg", ".bh", ".bi", ".bj", ".bm", ".bn", ".bo", ".br", ".bs", ".bt", ".bv", ".bw", ".by", ".bz", ".ca", ".cc", ".cd", ".cf", ".cg", ".ch", ".ci", ".ck", ".cl", ".cm", ".cn", ".co", ".cr", ".cs", ".cu", ".cv", ".cx", ".cy", ".cz", ".dd", ".de", ".dj", ".dk", ".dm", ".do", ".dz", ".ec", ".ee", ".eg", ".eh", ".er", ".es", ".et", ".eu", ".fi", ".fj"};
const unsigned int URL::topLevelDomainsSize = 94;

URL::URL(string url)
  : url(normalizeURL(url)),                 // Initialize URL.
    scheme(getScheme(this->url)),           // Initialize scheme portion of URL.
    domain(getDomain(this->url)),           // Initialize domain portion of URL.
    subDomain(getSubDomain(this->url)),     // Initialize the sub domain portion of URL.
    path(getPath(this->url)),               // Initialize path portion of URL.
    queryString(getQueryString(this->url)), // Initialize query string portion of URL.
    fragment(getFragment(this->url))        // Initialize fragment portion of URL.
{
  stringstream concat;
  concat << path << queryString << fragment;
  hashCode = generateHashCode(concat.str()); // Initialize hash code.
}

URL::URL(string suggestedDomain, string url)
  : url(normalizeURL(url)),                 // Initialize URL.
    scheme(getScheme(this->url)),           // Initialize scheme portion of URL.
    domain(getDomain(this->url)),           // Initialize domain portion of URL.
    subDomain(getSubDomain(this->url)),     // Initialize the sub domain portion of URL.
    path(getPath(this->url)),               // Initialize path portion of URL.
    queryString(getQueryString(this->url)), // Initialize query string portion of URL.
    fragment(getFragment(this->url))        // Initialize fragment portion of URL.
{
  stringstream concat;
  concat << path << queryString << fragment;
  hashCode = generateHashCode(concat.str()); // Initialize hash code.
  setDomain(suggestedDomain); // Override the domain found in url with the value of domain.
}

URL::~URL()
{
  // Nothing to delete.
}

unsigned long URL::getHash()
{
  return hashCode;
}

// String folding at 4 bytes at a time.
unsigned long URL::generateHashCode(const string &input)
{
  int intLength = input.size() / 4;
  long sum = 0;
  
  for(int i = 0; i < intLength; i++)
    {
      int startIndex = i * 4;
      int endIndex = (i * 4) + 4;
      long multiplyer = 1;
      
      for(int j = startIndex; j < endIndex; j++)
	{
	  sum += input.at(j) * multiplyer;
	  multiplyer *= 256;
	}
    }
  
  int startIndex = intLength * 4;
  int endIndex = input.size();
  long multiplyer = 1;
  
  for(int i = startIndex; i < endIndex; i++)
    {
      sum += input.at(i) * multiplyer;
      multiplyer *= 256;
    }
  
  if(sum < 0)
    {
      sum *= -1;
    }
  
  return sum;
}

string URL::toString()
{
  stringstream returnString;
  returnString << *this;

  return returnString.str();
}

ostream& operator<<(ostream &str, const URL &v)
{
  str << "URL:         [" << (v.scheme + v.subDomain + v.domain + v.path + v.queryString + v.fragment) << "]\n"
      << "Scheme:      [" << v.scheme << "]\n"
      << "Domain:      [" << v.domain << "]\n"
      << "Sub Domain   [" << v.subDomain << "]\n"
      << "Path:        [" << v.path << "]\n"
      << "Query String [" << v.queryString << "]\n"
      << "Fragement    [" << v.fragment << "]\n"
      << "Hash Code:   [" << v.hashCode << "]";
  
  return str;
}

bool URL::operator<(const URL &other) const
{
  return hashCode < other.hashCode;
}

bool URL::operator>(const URL &other) const
{
  return hashCode > other.hashCode;
}

bool URL::operator==(const URL &other) const
{
  return hashCode == other.hashCode;
}

string URL::getScheme()
{
  return scheme;
}

string URL::getDomain()
{
  return domain;
}

string URL::getSubDomain()
{
  return subDomain;
}

string URL::getPath()
{
  return path;
}

string URL::getQueryString()
{
  return queryString;
}

string URL::getFragment()
{
  return fragment;
}

string URL::normalizeURL(const string &input)
{
  string returnString = input;

  //for(string::size_type i = 0; i < returnString.length(); i++)
  //  {
  //    returnString[i] = tolower(returnString[i]);
  //  }

  // and many more...

  return returnString;
}

string URL::getScheme(const string &input)
{
  size_t endIndex = input.find("://");

  if(endIndex == string::npos)
    {
      return "http://";
    }

  return input.substr(0, endIndex + 3);
}

string URL::getDomain(const string &input)
{
  size_t endIndex = 0;
  size_t topLevelDomainStringSize = 0;

  for(unsigned int i = 0; i < URL::topLevelDomainsSize; i++)
    {
      endIndex = input.find(URL::topLevelDomains[i]);

      if(endIndex != string::npos)
	{
	  topLevelDomainStringSize = URL::topLevelDomains[i].size() - 1;
	  //endIndex = endIndex - URL::topLevelDomains[i].size();
	    i = URL::topLevelDomainsSize + 1;
	}
    }

  if(endIndex == string::npos
    || endIndex - 1 < 0)
    {
      return "";
    }

  size_t startIndex = 0;
  startIndex = input.rfind(".", endIndex - 1);

  if(startIndex == string::npos)
    {
      startIndex = -1;
      //return "";
    }

  return input.substr(startIndex + 1, (endIndex - startIndex) + topLevelDomainStringSize);
}

string URL::getSubDomain(const string &input)
{
  size_t startIndex = input.find("://");

  if(startIndex != string::npos)
    {
      startIndex = startIndex + 3;
    }
  else
    {
      startIndex = 0;
    }
  
  size_t endIndex = input.find(domain);

  if(endIndex == string::npos)
    {
      endIndex = startIndex;
    }

  string returnString = input.substr(startIndex, endIndex - startIndex);
  
  if(returnString.find("www.") == string::npos)
    {
      returnString = "www." + returnString;
    }

  return returnString;
}

string URL::getPath(const string &input)
{
  size_t startIndex = 0;

  if(input.find("://") != string::npos)
    {
      startIndex = startIndex + 3 - 1;
    }

  if(domain.size() != 0)
    {
      startIndex = startIndex + domain.size() - 1;
    }

  startIndex = input.find("/", startIndex);
  size_t endIndex = 0;
  size_t fragmentIndex = 0;

  if(startIndex == string::npos)
    {
      startIndex = input.size();
    }

  endIndex = input.find("?", startIndex);

  if(endIndex == string::npos)
    {
      endIndex = input.size();
    }

  fragmentIndex = input.find("#", startIndex);

  if(fragmentIndex != string::npos
     && fragmentIndex < endIndex)
    {
      endIndex = fragmentIndex;
    }

  return input.substr(startIndex, endIndex - startIndex);
}

void URL::setDomain(const string &d)
{
  domain = d;
}

string URL::getQueryString(const string &input)
{
  size_t startIndex = input.find("?");
  size_t endIndex = 0;

  if(startIndex == string::npos)
    {
      return "";
    }

  startIndex++;
  endIndex = input.find("#");

  if(endIndex == string::npos)
    {
      endIndex = input.size();
    }

  return input.substr(startIndex, endIndex - startIndex);;
}

string URL::getFragment(const string &input)
{
  size_t startIndex = input.find("#");

  if(startIndex == string::npos)
    {
      return "";
    }

  startIndex++;
  return input.substr(startIndex, input.size() - startIndex);
}

string URL::getURL()
{
  return scheme + subDomain + domain + path + queryString + fragment;
}
