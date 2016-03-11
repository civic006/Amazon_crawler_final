/*
 * Customer.cpp
 *
 *  Created on: Feb 12, 2012
 *      Author: Braden
 */

#include <stdio.h>
#include "global_web_data.h"
//#include <iostream>
using namespace std;

#include "Customer.h"

Customer::Customer(string n, string loc) : name(n), location(loc), hashCode(generateHashCode(n)) {
	this->correctWords = new vector<Word*>();

	this->misspelled = new vector<Misspelled_Word*>();
}
string Customer::getLocation()
{
	return location;
}
Customer::~Customer() {
}

/* Gets the name of the customer
 *
 * Parameters: none
 *
 * Returns: string: name of customer
 */
string Customer::getName() {
	return name;
}

Comment Customer::getCommentByProduct(string p)
{
	for(unsigned int i = 0; i < comments.size(); i++)
	{
		if(comments.at(i).getProduct().compare(p) == 0)
		{
			return comments.at(i);
		}
	}
	return Comment();
}

/* Adds a customer comment to the list of customer comments.
 *
 * Parameters:string: the comment
 * 			  doubel: the rate of the comment
 * 			  string: the date the comment was written
 *
 * Returns: none
 */
void Customer::addComments(string line, double rate, string date, string helpful, string product) {

	this->addAverageRate(rate);
	if (!line.empty() && !date.empty())
		this->comments.push_back(Comment(line, rate, date, helpful, product));
	//Simple char parsing method to pull words out of the incoming string.
	//If char c != NULL keep going, if it equals ' ' then check if it's in the dictionary
	//If its spelled correctly add it to correct, else misspelled
	//NOT VERY ELEGANT BUT IT WORKS
}

/* Gets the customer's list of Comments
 *
 * Parameters: none
 *
 * Returns: vector<string>: list of Comment
 */
vector<Comment> Customer::getComments() {
	return this->comments;
}

/* Adds a comment rate to compute the customer's average rating
 * which is the average of all comments rates.
 *
 * Parameters: double: the rate
 *
 * Returns: none
 */
void Customer::addAverageRate(double rate) {
	this->rating += rate;
	ratingCount++;
}

/* Computes the average customer's rates.
 *
 * Parameters: none
 *
 * Returns: double: the average of rates.
 */
double Customer::getAverageRate() {
	return this->rating*100.0 / ratingCount;
}

/* Adds a customer location: city
 *
 * Parameters: string: city
 *
 * Returns: none
 */
void Customer::addCity(string city) {
	this->city = city;
}

/* Adds a customer location: state
 *
 * Parameters: string: state
 *
 * Returns: none
 */
void Customer::addState(string state) {
	this->state = state;
}

/* Gets the customer city.
 *
 * Parameters: none
 *
 * Returns: string: city
 */
string Customer::getCity() {
	return city;
}

/* Gets the customer state.
 *
 * Parameters: none
 *
 * Returns: string: state
 */
string Customer::getState() {
	return state;
}

/* gets a list of correctly spelled words
 *
 * Parameters: none
 *
 * Returns: vector<Word*>*: a pointer to a list of correct words.
 */
vector<Word*>* Customer::getCorrectWords() {
	return this->correctWords;
}

/* Gets a list of all misspelled words the customer wrote.
 *
 * Parameters: none
 *
 * Returns: vector<Misspelled_Word*>*: a pointer to the list of misspelled words.
 */
vector<Misspelled_Word*>* Customer::getMisspelledWords() {
	return this->misspelled;
}

unsigned long Customer::getHash() {
	return hashCode;
}

/* Gets the hashcode of the customer based on the customer name.
 *
 * Parameters: none
 *
 * Returns: long: the hash code
 */
// String folding at 4 bytes at a time.
unsigned long Customer::generateHashCode(const string &input) {
	int intLength = input.size() / 4;
	long sum = 0;

	for (int i = 0; i < intLength; i++) {
		int startIndex = i * 4;
		int endIndex = (i * 4) + 4;
		long multiplyer = 1;

		for (int j = startIndex; j < endIndex; j++) {
			sum += input.at(j) * multiplyer;
			multiplyer *= 256;
		}
	}

	int startIndex = intLength * 4;
	int endIndex = input.size();
	long multiplyer = 1;

	for (int i = startIndex; i < endIndex; i++) {
		sum += input.at(i) * multiplyer;
		multiplyer *= 256;
	}

	if (sum < 0) {
		sum *= -1;
	}

	return sum;
}

/* returns a string of the customer name, comments, and average rates.
 *
 * Parameters: none
 *
 * Returns: string: contains the name, comments and average rate of a customer.
 */
string Customer::toString() {
	string s;
	//s.assign("User's name: " + this->name + " Comments: " + this->comments
	// 		+ " Rating: " + this->rating/ratingCount);
	s = "Customers's name: " + getName() + "\n";
	s += "Customer's average rate: ";
	//s+= getAverageRate();
	s += "\n";

	for (unsigned int i = 0; i < comments.size(); i++) {
		s += comments.at(0).toString();
	}

	return s;
}

ostream& operator<<(ostream &str, const Customer &v) {
	str << "ASDF";

	return str;
}

/* overrides the == operator to compare names of this customer and the given customer
 *
 * Parameters: Customer*: a customer to be compared with this customer
 *
 * Returns: bool: true if names are equivalent, false otherwise
 */
bool Customer::operator==(const Customer &c) const {
	return hashCode == c.hashCode;
}

/* overrides the > operator to compare names of this customer and the given customer
 *
 * Parameters: Customer*: a customer to be compared with this customer
 *
 * Returns: bool: true if the name of this customer is bigger, false otherwise
 */
bool Customer::operator>(const Customer &c) const {
	return hashCode > c.hashCode;
}

/* overrides the < operator to compare names of this customer and the given customer
 *
 * Parameters: Customer*: a customer to be compared with this customer
 *
 * Returns: bool: true if the name of this customer is smaller, false otherwise
 */
bool Customer::operator<(const Customer &c) const {
	return hashCode < c.hashCode;
}

/* Destructs the customer
 *
 * Parameters: None
 *
 * Returns: None
 */
//Customer::~Customer()
//{
//  for(unsigned int i = 0; i < correctWords->size(); i++)
//{
//  delete correctWords->at(i);
//}
//delete correctWords;
// for(unsigned int i = 0; i < misspelled->size(); i++)
//{
//  delete misspelled->at(i);
//}
//delete misspelled;
//}
