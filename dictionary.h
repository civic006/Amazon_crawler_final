#ifndef __DICTIONARY_H
#define __DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>
#include "bst.h"
//#include "../src/hash.h"
#include "word.h"
/*Braden Edmunds
 *Ryan Finn
 *Nathan Patterson
 *Abdullah Aldobaie
 */
 class Dictionary
 {
    public:
      Dictionary();

      bool spelled_correctly(string &word);
      bool best_matches( string word, vector<string> &list, int unsigned count ); // return true if spelled correctly or up to count (default 5) best matches
      void addWords(vector<string> &words);
      
      int getCount();
    private:
      //Instance variables. The dictionary contains a BST and a hash table.
      //Hash *hash;
      BST<Word> *bst;
      string fileName;
      
      //This method takes the file name saved in the constructor,
      //and opens the file to load the dictionary words.
      void LoadWords();
      
 };

#endif
