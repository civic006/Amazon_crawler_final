#include <iostream>
#include <sstream>
using namespace std;
/*Braden Edmunds
 *Ryan Finn
 *Nathan Patterson
 *Abdullah Aldobaie
 */
#include "commandParser.h"
/*
 *Constructor for the commandParser. It takes in all of the command line parameters
 *and loads them into this object.
 *
 */
CommandParser::CommandParser(int argc, char* argv[])
{
  for(int i = 0; i < argc; i++)
    {
      params.push_back(argv[i]);
    }
}

CommandParser::~CommandParser()
{
  // Nothing to delete.
}
/*
 *This method returns a string of the file name given the constant enumerator.
 */
string CommandParser::getSingleValueByName(const string &name)
{
  string returnString = "";

  for(unsigned int i = 0; i < params.size(); i++)
    {
      if(i + 1 < params.size()
	 && name.compare(params[i]) == 0)
	{
	  returnString = params[i + 1];
	  i = params.size() + 1;
	}
    }

  return returnString;
}

// This needs to be updated to use a hash table when the professor lets us use the STL.
vector<string> CommandParser::getValueListByName(const string &name, const vector<string> &names)
{
  vector<string> returnVector;

  for(unsigned int i = 0; i < params.size(); i++) // Find the location of the name.
    {
      if(i + 1 < params.size()
	 && name.compare(params[i]) == 0)
	{
	  for(unsigned int j = i + 1; j < params.size(); j++) // Work through each token after the position of name.
	    {
	      bool nameFound = false;

	      for(unsigned int k = 0; k < names.size(); k++) // Is the current token another name command?  If not, add it to the return list.
		{
		  if(names[k].compare(params[j]) == 0)
		    {
		      nameFound = true;
		      k = names.size() + 1;
		      j = params.size() + 1;
		    }
		}

	      if(!nameFound)
		{
		  returnVector.push_back(params[j]);
		}
	    }

	  i = params.size() + 1;
	}
    }

  return returnVector;
}
/*
 *This method returns the entire parameters list as a string.
 */
string CommandParser::toString()
{
  stringstream returnString;

  for(unsigned int i = 0; i < params.size(); i++)
    {
      returnString << params[i];

      if(i < params.size() + 1)
	{
	  returnString << "\n";
	}
    }

  return returnString.str();
}
