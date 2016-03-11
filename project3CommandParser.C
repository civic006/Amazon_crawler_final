#include "project3CommandParser.h"
#include "commandParser.h"
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
 * 
 */
const string Project3CommandParser::FLAG_DOMAIN = "-domain";
const string Project3CommandParser::FLAG_THREADS = "-threads";
const string Project3CommandParser::FLAG_COUNT = "-count";
const string Project3CommandParser::FLAG_MISS = "-miss";
const string Project3CommandParser::FLAG_DICTIONARY = "-d";

Project3CommandParser::Project3CommandParser(int argc, char* argv[])
  : CommandParser(argc, argv)
{
  commandFlags.push_back(Project3CommandParser::FLAG_DOMAIN);
  commandFlags.push_back(Project3CommandParser::FLAG_THREADS);
  commandFlags.push_back(Project3CommandParser::FLAG_COUNT);
  commandFlags.push_back(Project3CommandParser::FLAG_MISS);
  commandFlags.push_back(Project3CommandParser::FLAG_DICTIONARY);
}

Project3CommandParser::~Project3CommandParser()
{
  // Nothing to delete.
}

vector<string> Project3CommandParser::getValueListByName(const string &name)
{
  return CommandParser::getValueListByName(name, commandFlags);
}
