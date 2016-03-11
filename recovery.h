/*
 * recovery.h
 *
 *  Created on: Feb 16, 2012
 *      Author:
 *	     	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 * A class that recover last session info that was written in a customerList.txt and
 * a productList.txt files.
 *
 * The recovery file must be written in the following format:
 * 		- a file with list of Customers:
 * 			+ each line will contain a customer name | reviews | pages |...
 * 		- a file with list of Products:
 * 			+ each line contains a product name \n reviews \n customers \n...
 * 		- a file with list of urls to visit:
 * 			+ each line contains a url
 * 		- a file with list of visited urls:
 * 			+ each line contains a visited url
 *
 */

#ifndef RECOVERY_H_
#define RECOVERY_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "url.h"
#include "Customer.h"
#include "product.h"

using namespace std;

class Recovery
{

public:

	/* Constructor for TextFileReader.
	 */
	Recovery();

	/* Destructor for TextFileReader.
	 */
	~Recovery();

	/*
	 * To recover the Global_Web_Data by reading recovery files.
	 */
	void recoverGlobalWebData();

private:

	vector<string> fileLines; // Stores lines of file input.


	/* reads the customerList.txt into a vector of strings.
	 *
	 * Parameters:
	 *
	 * Returns:
	 */
	void readRecoveryFile(string filePathAndName);


	void sendCustomersToGlobalWebData();
	void sendProductsToGlobalWebData();
	void sendUrlsToGlobalWebData();
	void sendVisitedUrlsToGlobalWebData();


	void creatCustomer(string line);
	void createProduct(string line);
	void createUrl(string line);


	/* Returns a vector<string> representing contents of the text file(s) inputs after
	 * having been split by spaces.
	 */
	vector<string> getSplitByTap(vector<string> &fileLines);

};
#endif
