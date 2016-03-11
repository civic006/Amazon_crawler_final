/* Class CommandParser provides a layer of abstraction for command line input
 * for the purpose of convenience.  We don't want to write new command line
 * parsing code for every project.
 * The class is designed with the assumption that command line input will be
 * name/value pair-based. 
 * Braden Edmunds
 * Ryan Finn
 * Nathan Finn
 * Abdullah Aldobaie
 */

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <vector>
#include <string>
using namespace std;

class CommandParser
{
 public:
  
  /* Constructor for CommandParser.
   * int argc  // The size of char* argv[]
   * char* argv[] // The tokenized command line objects.
   */
  CommandParser(int argc, char* argv[]);

  /* Destructor for CommandParser.
   */
  ~CommandParser();

  /* Returns a string that represents the value of a name/value pair from
   * command line input.
   * const string &name // The name in the name/value pair for which the value is returned.
   */
  string getSingleValueByName(const string &name);

  /* Returns a vector<string> representing a list of values from a name/value pair.
   * const string &name // The name in the name/value pair for which the values are returned.
   * const vector<string> &names // A list of names for the expected name/value pairs that allows for determiniation of where the list of values ends as another name/value pair begins.
   */
  vector<string> getValueListByName(const string &name, const vector<string> &names);

  /* Returns a string representation of CommandParser.
   */
  string toString();

 private:
  vector<string> params; // Stores the tokenized command line input.
};

#endif
