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
#include "misspelled_word.h"
#include "word.h"

Misspelled_Word::Misspelled_Word()
{
}
Misspelled_Word::Misspelled_Word(string word)
  : wordValue(word)
{
}

Misspelled_Word::~Misspelled_Word()
{
}
long Misspelled_Word::getHash()
{
	long hashCode;
	int count = 0;
	char c = this->wordValue[count++];
	while(c != 0)
	{
		hashCode += c;
		c = this->wordValue[count++];
	}

	return hashCode;

}
string Misspelled_Word::toString()
{
  return wordValue;
}


/* Dictionary does not have a copy constructor and therefore cannot reliably
 * be passed by value.  Dictionary must be passed by reference or pointer.
 */
vector<Misspelled_Word>* Misspelled_Word::checkWords(Dictionary &dictionary, vector<string> const & wordsToCheck)
{
  vector<Misspelled_Word> *misspelledWords = new vector<Misspelled_Word>();
  ifstream in;
  string strippedWord, line, strippedTemp,  temp;
  HashTable<Word> tempTable;

  for(unsigned int i = 0; i < wordsToCheck.size(); i++)
    {
      strippedWord = Word(wordsToCheck[i]).getStrippedWordValue();
      if(tempTable.add(new Word(strippedWord)))
	{
	  if(!strippedWord.empty() && !(dictionary.spelled_correctly(strippedWord)))
	    {
	      Misspelled_Word *word = new Misspelled_Word(strippedWord);
	      dictionary.best_matches(strippedWord, word->bestMatches, 5);
	      misspelledWords->push_back(*word);
	      
	    }
	}
    }

  return misspelledWords;
}
