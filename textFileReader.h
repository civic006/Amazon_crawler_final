/* Class TextFileReader is useful for reading text files into memory and then making the
 * text contents conveniently availalbe to other classes.
 */

#ifndef TEXTFILEREADER_H
#define TEXTFILEREADER_H

#include <vector>
#include <string>
using namespace std;
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
class TextFileReader
{
 public:

  /* Constructor for TextFileReader.
   */
  TextFileReader();

  /* Destructor for TextFileReader.
   */
  ~TextFileReader();

  /* Appends a file's contents to TextFileReader.
   */
  void addFile(const string &filePathAndName);

  /* Modifies a vector<string> representing contents of the text file(s) inputs after
   * having been split by spaces.
   * vector<string> &splitValues  // This vector will be filled with split values.
   */
  void getSplitBySpace(vector<string> &splitValues);

  string getLineAt(unsigned int index);

  /* Returns a string representation of TextFileReader.
   */
  string toString();

 private:
  vector<string> fileLines; // Stores lines of file input.
};

#endif
