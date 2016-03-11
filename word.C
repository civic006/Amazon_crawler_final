#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#include "word.h"
/* hash.C
 *
 * Abdullah Aldobaie
 * Braden Edmunds
 * Nathan Patterson
 * Ryan Finn
 *
 * Jan. 24, 2012
 *
 *
 * The definitions of the functions in hash.h
 */
Word::Word(string s)
  : wordValue(s),
    strippedWordValue(s),
    wordCount(1),
    hashCode(generateHashCode())
{
  stripUnwantedChars(strippedWordValue);
}

Word::~Word()
{
  // Nothing to delete because no heap stuff was allocated.
}

unsigned long Word::getHash()
{
  return hashCode;
}

ostream& operator<<(ostream &str, const Word &v)
{
  str << "Original Word value: [" <<  v.wordValue
      << "], Stripped Word value: [" << v.strippedWordValue
      << "] Count: [" << v.wordCount
      << "] hash code [" << v.hashCode
      << "]";
  
  return str;
}

bool Word::operator<(const Word &other) const
{
  return strippedWordValue.compare(other.strippedWordValue) < 0;
}

bool Word::operator>(const Word &other) const
{
  return strippedWordValue.compare(other.strippedWordValue) > 0;
}

bool Word::operator==(const Word &other) const
{
  return strippedWordValue.compare(other.strippedWordValue) == 0;
}

void Word::stripUnwantedChars(string &input)
{
  vector<int> badCharLocations;

  // Convert to lower case and gather locations of unwanted characters.
  for(string::size_type i = 0; i < input.length(); i++)
    {
      input[i] = tolower(input[i]);

      if(input[i] < 'a' || input[i] > 'z')
	{
	  badCharLocations.push_back(i);
	}
    }
  
  // Remove unwanted characters from input.
  for(string::size_type i = 0; i < badCharLocations.size(); i++)
    {
      input.erase(input.begin() + badCharLocations[i] - i);
    }
}

string Word::getWordValue()
{
  return wordValue;
}

string Word::getStrippedWordValue()
{
  stripUnwantedChars( strippedWordValue);
  return strippedWordValue;
}

string Word::toString()
{
  stringstream s;
  s << *this;

  return s.str();
}

void Word::incrementWordCount()
{
  wordCount++;
}

int Word::getWordCount()
{
  return wordCount;
}

// String folding at 4 bytes at a time.
unsigned long Word::generateHashCode()
{
  int intLength = strippedWordValue.size() / 4;
  long sum = 0;

  for(int i = 0; i < intLength; i++)
    {
      int startIndex = i * 4;
      int endIndex = (i * 4) + 4;
      long multiplyer = 1;

      for(int j = startIndex; j < endIndex; j++)
	{
	  sum += strippedWordValue.at(j) * multiplyer;
	  multiplyer *= 256;
	}
    }

  int startIndex = intLength * 4;
  int endIndex = strippedWordValue.size();
  long multiplyer = 1;

  for(int i = startIndex; i < endIndex; i++)
    {
      sum += strippedWordValue.at(i) * multiplyer;
      multiplyer *= 256;
    }

  if(sum < 0)
    {
      sum *= -1;
    }

  return sum;
}
