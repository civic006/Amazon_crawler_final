/* comment.C
 *
 *  Created on: Feb 18, 2012
 *      Author: aldobaie
 */

#include "comment.h"
#include "global_web_data.h"

Comment::Comment() {
	comment = "";
	date = "";
	rate = 0;
}

/*
 * Constructor
 */
Comment::Comment(string str, double rate, string date, string helpful,
		string product) {
	this->misspelled = new vector<Misspelled_Word*>();
	this->correct = new vector<Word*>();
	setComment(str);
	setRate(rate);
	setDate(date);
	setHelpful(helpful);
	setProduct(product);
}
void Comment::setHelpful(string help) {
	this->helpful = help;

}

void Comment::setProduct(string product) {
	this->product = product;
}

string Comment::getHelpful() {
	return helpful;
}

string Comment::getProduct() {
	return product;
}
Comment::~Comment() {
}

void Comment::setDate(string date) {
	this->date = date;
}

string Comment::getDate() {
	return date;
}

void Comment::setComment(string line) {
	//this->comment= comment;
	this->comment.append(line);

	char c;
	string temp = "";

	if (!line.empty()) {
		for (unsigned int i = 0; i < line.size(); i++) {
			c = line[i];
			if (c == ' ') {
				if (Global_Web_Data::checkWordExists(temp)) {
					this->correct->push_back(new Word(temp));
				} else {
					this->misspelled->push_back(new Misspelled_Word(temp));
					Word *w = new Word(temp);
					if (!Global_Web_Data::addMisspelledWord(w)) {
						delete w;
					}
				}

				temp = "";
			} else {
				temp += c;
			}
		}
		if (Global_Web_Data::checkWordExists(temp)) {
			this->correct->push_back(new Word(temp));
		} else {
			this->misspelled->push_back(new Misspelled_Word(temp));
		}
	}

}
/* gets a list of correctly spelled words
 *
 * Parameters: none
 *
 * Returns: vector<Word*>*: a pointer to a list of correct words.
 */
vector<Word*>* Comment::getCorrectWords() {
	return this->correct;
}

/* Gets a list of all misspelled words the customer wrote.
 *
 * Parameters: none
 *
 * Returns: vector<Misspelled_Word*>*: a pointer to the list of misspelled words.
 */
vector<Misspelled_Word*>* Comment::getMisspelledWords() {
	return this->misspelled;
}
string Comment::getComment() {
	return comment;
}

void Comment::setRate(double star) {
	this->rate = star;
}

double Comment::getRate() {
	return rate;
}

string Comment::toString() {
	string str = "Comment: [";
	str += this->comment;
	str += "], rate: [";
	str += this->rate;
	str += "], date: [";
	str += this->date;
	str += "].";

	return str;
}
