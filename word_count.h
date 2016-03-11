/* Braden Edmunds
 * Ryan Finn
 * Nathan Patterson
 * Abdullah Aldobaie
 *
 * Class Word_Count provides information about text inputs such as how
 * often words occur.
 */

#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include <vector>

#include "bst.h"
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
class Word_Count
{
 public:

  /* Constructor for Word_Count.
   */
  Word_Count();

  /* Destructor for Word_Count.
   */
  ~Word_Count();

  /* Adds a word to Word_Count.
   * string word // String representing an English word.
   */
  void add_word(string word);
 
  /* Adds a word to Word_Count.
   * Word *word // Represents an English word.
   */
  void add_word(Word *word);

  /* Returns an integer representing the number of times a word appears.
   */
  int get_word_count(string word);

  /* Returns an integer representing how many times a word appears.
   */
  int get_word_count(const Word &word);

  /* Updates provided vectors to represent occurring words and how many times they occur.
   */
  void get_top_words(vector<string> &word_list, vector<int> &counts, int count = DEFAULT_HISTOGRAM_COUNT);
  
  /* Returns a vector of Word pointers in descending sorted order by occurrance.
   */
  vector<Word*> get_top_words(unsigned int count = 50);

  static const unsigned int DEFAULT_HISTOGRAM_COUNT; // The default historgram size;

  unsigned int getFileWordCount();

 private:
  /* Sorts a provided list of Words.
   */
  void sortWords(vector<Word*> &words);

  /* A quicksort algorithm to help method sortWords()
   */
  void quickSort(vector<Word*> &words, int left, int right);

  BST<Word> bst; // Stores a binary search tree of Words.
};

#endif
