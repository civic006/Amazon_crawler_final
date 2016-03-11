/*
 * comment.h
 *
 *  Created on: Feb 18, 2012
 *      Author:
 *         	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 *  This class represents a customer's comment with it's creation date and rate.
 */

#ifndef COMMENT_H_
#define COMMENT_H_


#include <string>
#include <vector>
#include <stdio.h>

#include "word.h"
#include "misspelled_word.h"
using namespace std;

class Comment
{
public:
	/*
	 * Constructor
	 */
	Comment();

	/*
	 * Overloading Constructor
	 */
	Comment(string str, double rate, string date, string helpful, string product);
	vector<Misspelled_Word*>* getMisspelledWords();
	vector<Word*>* getCorrectWords();
	/*
	 * Destructor
	 */
	~Comment();
	vector<Misspelled_Word*> *misspelled;

	vector<Word*> *correct;
	void setHelpful(string help);
	void setProduct(string product);
	string getHelpful();
	string getProduct();
	/*
	 * sets the date of writing the comment
	 *
	 * Parameters: string: the date
	 *
	 * return: void
	 */
	void setDate(string date);

	/*
	 * Gets the date
	 *
	 * Parameter: none
	 *
	 * Returns: string: the date
	 */
	string getDate();

	/*
	 *
	 * Parameters:
	 *
	 * Returns:
	 *
	 */
	void setComment(string comment);

	/*
	 *
	 * Parameters:
	 *
	 * Returns:
	 *
	 */
	string getComment();

	/*
	 *
	 * Parameters:
	 *
	 * Returns:
	 *
	 */
	void setRate(double star);

	/*
	 *
	 * Parameters:
	 *
	 * Returns:
	 *
	 */
	double getRate();

	/*
	 *
	 * Parameters:
	 *
	 * Returns:
	 *
	 */
	string toString();

private:
	string comment;
	string date;
	string helpful;
	string product;
	double rate;

};
#endif

