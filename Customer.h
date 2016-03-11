/*
 * Customer.h
 *
 *  Created on: Feb 12, 2012
 *      Author:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>
using namespace std;

#include "word_count.h"
#include "misspelled_word.h"
#include "comment.h"


class Customer
{
public:
  Customer(string n, string loc);
  ~Customer();
  
  /* Gets the name of the customer
   *
   * Parameters: none
   *
   * Returns: string: name of customer
   */
  string getName();
  
  Comment getCommentByProduct(string p);

  /* Adds a customer comment to the list of customer comments.
   *
   * Parameters:string: the comment
   * 			  doubel: the rate of the comment
   * 			  string: the date the comment was written
   *
   * Returns: none
   */
  void addComments(string str, double rate, string date, string helpful, string product );
  
  /* Gets the customer's list of Comments
   *
   * Parameters: none
   *
   * Returns: vector<string>: list of Comment
   */
  vector<Comment> getComments();
  
  /* Adds a comment rate to compute the customer's average rating
   * which is the average of all comments rates.
   *
   * Parameters: doubel: the rate
   *
   * Returns: none
   */
  void addAverageRate(double r);
  
  /* Computes the average customer's rates.
   *
   * Parameters: none
   *
   * Returns: double: the average of rates.
   */
  double getAverageRate();
  
  /* Adds a customer location: city
   *
   * Parameters: string: city
   *
   * Returns: none
   */
  void addCity(string city);

  /* Adds a customer location: city
   *
   * Parameters: string: city
   *
   * Returns: none
   */
  void addState(string state);
  
  /* Gets the customer city.
   *
   * Parameters: none
   *
   * Returns: string: city
   */
  string getCity();

  /* Gets the customer state.
   *
   * Parameters: none
   *
   * Returns: string: state
   */
  string getState();

  string getLocation();
  /* gets a list of correctly spelled words
   *
   * Parameters: none
   *
   * Returns: vector<Word*>*: a pointer to a list of correct words.
   */
  vector<Word*>* getCorrectWords();
  
  /* Gets a list of all misspelled words the customer wrote.
   *
   * Parameters: none
   *
   * Returns: vector<Misspelled_Word*>*: a pointer to the list of misspelled words.
   */
  vector<Misspelled_Word*>* getMisspelledWords();
  
  /* Gets the hashcode of the customer based on the customer name.
   *
   * Parameters: none
   *
   * Returns: long: the hash code
   */
  unsigned long getHash();
  
  /* returns a string of the customer name, comments, and average rates.
   *
   * Parameters: none
   *
   * Returns: string: contains the name, comments and average rate of a customer.
   */
  string toString();
  
  friend ostream& operator<<(ostream &str, const Customer &v);
  
  /* overrides the == operator to compare names of this customer and the given customer
   *
   * Parameters: Customer*: a customer to be compared with this customer
   *
   * Returns: bool: true if names are equivalent, false otherwise
   */
  bool operator==(const Customer &c) const;
  
  /* overrides the > operator to compare names of this customer and the given customer
   *
   * Parameters: Customer*: a customer to be compared with this customer
   *
   * Returns: bool: true if the name of this customer is bigger, false otherwise
   */
  bool operator>(const Customer &c) const;
  
  /* overrides the < operator to compare names of this customer and the given customer
   *
   * Parameters: Customer*: a customer to be compared with this customer
   *
   * Returns: bool: true if the name of this customer is smaller, false otherwise
   */
  bool operator<(const Customer &c) const;
  
  /* Destructs the customer
   *
   * Parameters: None
   *
   * Returns: None
   */

  /* Returns an unsigned long representing a hash code unique to the function input.
   * const string &input // The string on which the generated hash code is based.
   */
  unsigned long generateHashCode(const string &input);
  
 private:
  string name;
  string location;
  //string commentStr;
  double rating;
  int ratingCount;
  string city;
  string state;
  unsigned long hashCode;
  
  vector<Word*> *correctWords;
  vector<Misspelled_Word*> *misspelled;
  vector<Comment> comments;
};

#endif
