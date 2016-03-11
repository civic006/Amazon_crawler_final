/*Braden Edmunds
 *Ryan Finn
 *Nathan Patterson
 *Abdullah Aldoabie
 */

#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <cctype>
using std::ifstream;

Dictionary::Dictionary()
{
  bst = new BST<Word>;
}

bool Dictionary::spelled_correctly(string &word)
{
  Word w(word);
  return bst->exist(w);
}

int Dictionary::getCount()
{
  return bst->getSize();
}

bool Dictionary::best_matches(string word, vector<string> &list, unsigned int count)
{
  bool returnValue = spelled_correctly(word);

  if(!returnValue)
    {
      vector<Word*> wordObjects;

      Word *tempWord = new Word(word);
      bst->add(tempWord);
      
      for(unsigned int i = 0; i < word.size(); i++) //We can't look for a word that isn't in there.
	{
          // Don't delete what you don't uderstand.
	  Word tempWord(word.substr(0, word.size() - i));
	  wordObjects = bst->getSimilar(tempWord, count);
	  
	  if(wordObjects.size() > 0)
	    {
	      i = word.size() + 1;
	    }
	}
      
      for(unsigned int i = 0; i < wordObjects.size() && i < count; i++)
	{
	  list.push_back(wordObjects[i]->getWordValue());
	}

      bst->remove(*tempWord);
      delete tempWord;
    }
  
  return returnValue;
}

void Dictionary::addWords(vector<string> &words)
{
  for(unsigned int i = 'a'; i < 'z'; i+=2) // load in the alphabet to help find find suggested words
      {
	char l[] = {i};
	string letter(l);
	bst->add(new Word(letter));
      }

    for(unsigned int i = 'b'; i < 'z'; i+=2) // load in the alphabet to help find find suggested words
      {
	char l[] = {i};
	string letter(l);
	bst->add(new Word(letter));
      }

     for(unsigned int i = 0; i < words.size() - 1; i+= 2)
      {
       	bst->add(new Word(words[i]));
      }
     
    for(unsigned int i = 1; i < words.size() - 1; i+= 2)
      {
       	bst->add(new Word(words[i]));
       }
}
