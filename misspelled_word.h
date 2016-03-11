#ifndef _MISSPELLEDWORD_H
#define _MISSPELLEDWORD_H

#include <string>
#include <vector>
#include "dictionary.h"
#include "hashTable.h"
#include <fstream>

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
class Misspelled_Word
{
 public:

  /* Default constructor for Misspelled_Word.
   */
  Misspelled_Word();

  /* Constructor for Misspelled_Word.
   *
   * Input: string word // String representing the misspelled word value.
   */
  Misspelled_Word(string word);

  /* Destructor for Misspelled_Word.
   */
  ~Misspelled_Word();

  /* Returns a string representation of Misspelled_Word.
   */
  string toString();

  /* Returns a long representing a hash code for this Misspelled_Word.
   */
  long getHash();

  vector<string> bestMatches; // Stores a vector of strings representing possible correct spellings.

  /* Method returns a pointer to a vector of Misspelled_Words.
   *
   * Input: Dictionary &dictionary // Reference to dictionary to be used to verfiy words.
   *        vector<string> const & wordsToCheck // Words to verify.
   */
  vector<Misspelled_Word>* checkWords(Dictionary &dictionary, vector<string> const & wordsToCheck);

 private:
  string wordValue; // Stores the original word value.
};

#endif
