#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "textFileReader.h"
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
TextFileReader::TextFileReader()
{
}

TextFileReader::~TextFileReader()
{
}

void TextFileReader::addFile(const string &filePathAndName)
{
  if(filePathAndName.compare("") == 0)
    {
      //throw something.
      return;
    }

  string fileLine;
  ifstream infile;
  infile.open(filePathAndName.c_str());
  
  while(getline(infile, fileLine)) // read in file lines
    {
      fileLines.push_back(fileLine);
    }
  
  infile.close();
}

void TextFileReader::getSplitBySpace(vector<string> &splitValues)
{
  size_t startIndex = 0;
  size_t endIndex = 0;

  for(unsigned int i = 0; i < fileLines.size(); i++)
    {
      startIndex = 0;
      endIndex = 0;

      while(endIndex != string::npos)
	{
	  endIndex = fileLines[i].find(" ", startIndex);

	  if(endIndex == string::npos)
	    {
	      splitValues.push_back(fileLines[i].substr(startIndex, fileLines[i].size()));
	    }
	  else
	    {
	      splitValues.push_back(fileLines[i].substr(startIndex, endIndex - startIndex));
	    }

	  startIndex = endIndex + 1;
	}
    }
}

string TextFileReader::getLineAt(unsigned int index)
{
  if(index >= 0 && index < fileLines.size())
    {
      return fileLines[index];
    }

  return "";
}

string TextFileReader::toString()
{
  stringstream returnString;
  
  for(unsigned int i = 0; i < fileLines.size(); i++)
    {
      returnString << fileLines[i];

      if(i < fileLines.size())
	{
	  returnString << "\n";
	}
    }

  return returnString.str();
}
