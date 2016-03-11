/*
 * output.h
 *
 *  Created on: Feb 15, 2012
 *      Authors:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 * A class that outputs results reserved in the global_web_data
 * to an HTML file. Also, creates a recovery file of the global_web_data
 * to be used in a rerun of the program.
 *
 *
 *
 * The HTML file will be formatted as follows:
 * 		- section of authors
 * 		- table of crawling statistics
 * 		- link to list of customers page
 * 		- link to list of products page
 *
 * The recovery file will be formatted as follows:
 * 		- a file with list of Customers:
 * 			+ each line will contain a customer name \n reviews \n pages \n...
 * 		= a file with list of Products:
 * 			+ each line contains a product name \n reviews \n customers \n...
 *
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "url.h"
#include "Customer.h"
#include "product.h"
#include "word.h"
#include "word_count.h"

using namespace std;

class Output
{
private:
	vector<URL*> urlsVector;
	vector<Word*> wordsVector;
	vector<Word*> misspelledWordsVector;
	vector<Customer*> customersVector;
	vector<Product*> productsVector;
	bool isAmazon;
	unsigned int webpagesVisitedCount;
	unsigned int topWords, topMisspelledWords;
public:

	/**
	 * Prints the results to an HTML files.
	 * The files will be in a folder.
	 *
	 * returns: none
	 */
	void printResultsToHTML(string domain,
			string startPage,
			int threadCount,
			int missSpelled,
			int topWords);

	/**
	 * Creates a recovery file of the program.
	 * This recovery file will be used when
	 * restarting the program to ontinues from where it left off.
	 */
	void createRecoveryFile();

private:
	/**
	 * Creates top words page to be linked from main page.
	 *
	 * Parameters: none
	 *
	 * Returns: string: a link to the words page.
	 */
	string createListOfTopWords();
	string createListOfTopMisspelledWords();
	/**
	 * Creates words corpus page to be linked from main page.
	 *
	 * Parameters: none
	 *
	 * Returns: string: a link to the words page.
	 */
	string createWordCorpusPage();

	/**
	 * Creates an HTML page that contains a list of customers.
	 *
	 * Parameters: a list of customers
	 *
	 * Returns: string: link to the the list of customers page
	 */
	string createListOfCustomers();

	/**
	 * Creates a customer page to be linked from main page.
	 *
	 * Parameters: a customer
	 *
	 * Returns: string: a link to the customer page.
	 */
	string createCustomerPage(Customer *c);


	/**
	 * Creates an HTML page that contains a list of productss.
	 *
	 * Parameters: a list of products
	 *
	 * Returns: string: link to the the list of products page
	 */
	string createListOfProducts();

	/**
	 * Creates a product page to be linked from the main page.
	 *
	 * Parameters: a product\
	 *
	 * Returns: string: a link to the product page.
	 */
	string createProductPage(Product *p);

	/**
	 * Creates an HTML type header.
	 *
	 * Parameters: None.
	 *
	 * Returns: a string of the HTML header code.
	 */
	string createHTMLHeader();

	/**
	 * Creates an HTML type title.
	 *
	 * Parameters: None.
	 *
	 * Returns: a string of the HTML title code.
	 */
	string createHTMLTitle(string title, bool addAuthors);

	/**
	 * Creates an HTML type link.
	 *
	 * Parameters: None.
	 *
	 * Returns: a string of the HTML link code appended with the given text.
	 */
	string createHTMLLink(string link, string text);

	/**
	 * Creates an HTML type table. The width of the table is the size of the first
	 * row in rowsContent. The height of the table is the size of the rows. the
	 * content of each row is the content of each inner vector of rowsContent.
	 *
	 * Parameters: vector<vector<string> > rowsContent: the table content in rows of columns.
	 *
	 * Returns: a string of the HTML table code.
	 */
	string createHTMLTable(vector<vector<string> > &tableContent);

};
#endif
