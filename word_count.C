#include <iostream>
using namespace std;

#include "word_count.h"
#include "word.h"

const unsigned int Word_Count::DEFAULT_HISTOGRAM_COUNT = 100;
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
Word_Count::Word_Count()
{
}

Word_Count::~Word_Count()
{
}

void Word_Count::add_word(string word)
{
  if(!word.empty())
    add_word(new Word(word));
}

void Word_Count::add_word(Word *word)
{
  if(!word->getStrippedWordValue().empty() && !bst.add(word))
    {
      bst.get(*word)->incrementWordCount();
      delete word;
    }
}

int Word_Count::get_word_count(string word)
{
  Word w(word);
  return get_word_count(w);
}

int Word_Count::get_word_count(const Word &word)
{
  Word *tempFoundWord = NULL;
  int count = 0;

  tempFoundWord = bst.get(word);

  if(tempFoundWord != NULL)
    {
      count = tempFoundWord->getWordCount();
    }
  
  return count;
}

void Word_Count::get_top_words(vector<string> &word_list, vector<int> &counts, int count)
{
  vector<Word*> const & words = get_top_words(count);
 
  for(unsigned int i = 0; i < words.size(); i++)
    {
      word_list.push_back(words[i]->toString());
      counts.push_back(words[i]->getWordCount());
    }
}

vector<Word*> Word_Count::get_top_words(unsigned count)
{
  if(count > bst.getSize())
    {
      count = bst.getSize();
    }
  vector<Word*> words = bst.getOrderedContents();

  sortWords(words);

  words.erase(words.begin() + count, words.end());

  return words;
}

void Word_Count::sortWords(vector<Word*> &words)
{
  quickSort(words, 0, words.size()-1);
}

void Word_Count::quickSort(vector<Word*> &words, int left, int right)
{
  if(left < 0 || right < 0 || left >= (int)words.size() || right >= (int)words.size())
    return;
  int i = left;
  int j = right;

  Word *ptrWord = words[(left + right) / 2];

  while(i <= j && j<(int)words.size())
    {
      while( i <(int) words.size() &&  words[i]->getWordCount() > ptrWord->getWordCount() )
	{
	  i++;
	}
      while(j >0 && j< (int)words.size() && words[j]->getWordCount() < ptrWord->getWordCount())
	{
	  j--;
	}
      if(i <= j && i>= 0 && j <(int) words.size())
	{
	  ptrWord = words[i];
	  words[i] = words[j];
	  words[j] = ptrWord;
	  i++;
	  j--;
	}
    }
  if(left < j)
    {
      quickSort(words, left, j);
    }
  if(i < right)
    {
      quickSort(words, i, right);
    }
}

unsigned int Word_Count::getFileWordCount()
{
  return bst.getFileWordCount();
}
