#include <iostream>
#include <string>
#include <sstream>
#include <regex.h>
using namespace std;

#include "robots_txt.h"

Robots_txt::Robots_txt(string domain, string txt)
  : domain(domain),                    // Set the domain of [domain]/robots.txt
    hashCode(generateHashCode(domain)) // Set the hash code based on domain.
{
  initialize_txt("disallow: ", txt, disallow, regexDisallow);
}

Robots_txt::~Robots_txt()
{
  // Delete dynamically-generated compiled regular expressions.
  for(size_t i = 0; i < regexDisallow.size(); i++)
    {
      delete regexDisallow[i];
    }
}

void Robots_txt::initialize_txt(string parameter, const string &input, vector<string> &vec, vector<regex_t*> &regexVec)
{
  string lowerCase;
  size_t startIndex = 0;
  size_t endIndex = 0;
  vector<int> wildcardIndexes;

  lowerCase.insert(0, input);
  
  // Convert to lower case.
  // Find locations of '*' because they need to be converted to ".*"
  for(size_t i = 0; i < input.size(); i++)
    {
      lowerCase[i] = tolower(lowerCase[i]);

      if(lowerCase[i] == '*')
	{
	  wildcardIndexes.push_back(i);
	}
    }

  // Replace '*' with '.*' so the compiled regex works later on.
  for(size_t i = 0; i < wildcardIndexes.size(); i++)
    {
      lowerCase.replace(wildcardIndexes[i] + i, 1, ".*");
    }
  
  // Parse the input and store all the robots.txt values based on parameter.
  // Example: Store "/gp/voting/" from "Disallow: /gp/voting/"
  for(size_t i = 0; i < lowerCase.size(); i++)
    {
      startIndex = lowerCase.find(parameter, i);
      
      if(startIndex != string::npos)
	{
	  endIndex = lowerCase.find("\n", startIndex + parameter.size());
	  
	  if(endIndex == string::npos)
	    {
	      endIndex = lowerCase.size();
	    }

	  string pattern = lowerCase.substr(startIndex + parameter.size(), endIndex - startIndex - parameter.size());

	  // Store value as regex if it compiles.
	  regex_t *exper = new regex_t();
	  if(regcomp(exper, pattern.c_str(), REG_EXTENDED) == 0)
	   {
	     regexVec.push_back(exper);
	     vec.push_back(pattern);
	   }

	  i = endIndex;
	}
      else
	{
	  i = lowerCase.size() + 1;
	}
    }
}

string Robots_txt::toString()
{
  stringstream returnString;
  returnString << *this;

  return returnString.str();
}

bool Robots_txt::isDisallowed(URL &url)
{
  size_t nmatch = 1;
  regmatch_t pmatch[1];
  string urlPath = url.getPath();

  // Check all the Disallow regex and return false if a pattern match is made.
  // False would indicate that the supplied URL is not allowed by [domain]/robots.txt.
  for(size_t i = 0; i < regexDisallow.size(); i++)
    {    
      if(regexec(regexDisallow[i], urlPath.c_str(), nmatch, pmatch, 0) == 0)
	{
	  return true;
	}
    }
  
  return false;
}

ostream& operator<<(ostream &str, const Robots_txt &r)
{
  for(unsigned int i = 0; i < r.disallow.size(); i++)
    {
      if(i > 0)
	{
	  str << "\n";
	}
      
      str << "Disallow: " << r.disallow[i];
    }
  
  if(r.disallow.size() > 0)
    {
      str << "\n";
    }
  
  str << "Domain:   [" << r.domain << "]\n"
	       << "Hash Code [" << r.hashCode << "]";

  return str;
}

bool Robots_txt::operator<(const Robots_txt &other) const
{
  return hashCode < other.hashCode;
}

bool Robots_txt::operator>(const Robots_txt &other) const
{
  return hashCode > other.hashCode;
}

bool Robots_txt::operator==(const Robots_txt &other) const
{
  return hashCode == other.hashCode;
}

// String folding at 4 bytes at a time.
unsigned long Robots_txt::generateHashCode(const string &input)
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

unsigned long Robots_txt::getHash()
{
  return hashCode;
}
