/* word.h
 *
 * Abdullah Aldobaie
 * Braden Edmunds
 * Nathan Patterson
 * Ryan Finn
 *
 * Feb. 03, 2012
 *
 * Class Word represents a written word from the English language.
 * The class abstracts string operations useful to other classes.
 */

#ifndef WORD_H
#define WORD_H

#include <string>
#include <stdlib.h>
#include <ostream>
using namespace std;

class Word
{
 public:

  /* Constructor for Word.
   * string s // The string that will be represented by Word.
   */
  Word(string s);

  /* Destructor for Word.
   */
  ~Word();

  /* Returns a hash key that strives to be unique to this Word instance.
   */
  unsigned long getHash();

  friend ostream& operator<<(ostream &str, const Word &v);

  /* Overloaded < operator.
   * Alphanumeric ordering of strings represented by this Word
   * and other Word determines <.
   */
  bool operator<(const Word &other) const;

  /* Overloaded > operator.
   * Alphanumeric ordering of strings represented by this Word
   * and other Word determines >.
   */
  bool operator>(const Word &other) const;

  /* Overloaded == operator.
   * Alphanumeric equality of strings represented by this Word
   * and other Word determines ==.
   */
  bool operator==(const Word &other) const;

  /* Returns the string that Word represents.
   */
  string getWordValue();

  /* Returns a version of the string that Word represents that
   * has been converted to all lower case characters and has had
   * all characters that are not 'a' through 'z' removed.
   * Example: "Don't" becomes "dont"
   */
  string getStrippedWordValue();

 
  /* Returns a string representation of this Word object.
   */
  string toString();

  /* Increments the variable that stores how many times this word appears.
   */
  void incrementWordCount();

  /* Returns this Word's count.
   */
  int getWordCount();


 private:
  string wordValue;          // The string that Word represents.
  string strippedWordValue;  /* The version of the string that Word represents
			      * converted to lower case and reduced to charcters
			      * that are 'a' through 'z.
			      */

  unsigned int wordCount;    // Stores the number of times this Word occurs.
  unsigned long hashCode;    // Stores this Word's hash code.
  
  /* Converts a string to lower case and reduces the string to characters
   * in the range 'a' through 'z'.
   */
  void stripUnwantedChars(string &input);

  /* Generates a hash code that strives to be unique to this Word.
   */
  unsigned long generateHashCode();
};

#endif
