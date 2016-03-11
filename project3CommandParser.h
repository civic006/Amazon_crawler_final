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
 *//* Class Project3CommandParser extends class CommandParser for the purpose
 * of providing specifics to the abstraction of command line input in a way
 * that is useful to CS3505 Project3.
 */

#ifndef PROJECT3COMMANDPARSER_H
#define PROJECT3COMMANDPARSER_H

//#include <vector>
//#include <string>

#include "commandParser.h"

class Project3CommandParser : public CommandParser
{
 public:

  /* Constructor for Project3CommandParser.
   */
  Project3CommandParser(int argc, char* argv[]);

  /* Destructor for Project3CommandParser.
   */
  ~Project3CommandParser();

  /* Need to update to include dictionary right inside of our program.
  static const string FLAG_DICTIONARY;      // Command line flag that indicates the value provided is that of the location of the dictionary or dictionaries.
  */

  static const string FLAG_DOMAIN;      // Command line flag that indicates the value provided is that of the domain to crawl (only crawl within the given domain, if a domain is not given only crawl the given url).

  static const string FLAG_THREADS;      // Command line flag that indicates the value provided is that of the number of threads we can use (default should be 1).

  static const string FLAG_COUNT;      // Command line flag that indicates the value provided is that of the top X words and their frequency (default should be 100).

  static const string FLAG_MISS;      // Command line flag that indicates the value provided is that of the top X misspelled words and their frequency (deafault should be 100).

  static const string FLAG_DICTIONARY;      // Command line flag that indicates the value provided is that of the location of the dictionary or dictionaries.


  /* Returns list of values associated to a name.
   * const string &name // The name in the name/value pair for which the values are returned.
   */
  vector<string> getValueListByName(const string &name);

 private:
  vector<string> commandFlags; // Stores a list of expected command line name for name/value pairs.
};

#endif
