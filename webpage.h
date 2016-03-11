/*
 * webpage.h
 *
 *  Created on: Feb 15, 2012
 *      Authors:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 * Reprents a webpage object, with a given depth, and URL of a page. This class
 * helps to crawl the webpage and pull out the the needed statistics from an amazon.com
 * or any other given domain.
 */

#ifndef WEBPAGE_H_
#define WEBPAGE_H_

#include <vector>
#include <string>
#include <stdio.h>
#include "url.h"
#include "Customer.h"
#include "product.h"
#include "comment.h"

using namespace std;

class webpage {
	// Depth of the current webpage, used to make sure we do not go over the max depth.
	int depth;

	// URL* of the current webpage
	URL* myURL;

	// Image count from the current webpage.
	int imageCount;

	/* Helps to trim a string of whitespaces before and after a string.
	 *
	 * Parameters:
	 * 	string: String to trim.
	 *
	 * Returns:
	 * 	string: The trimmed string.
	 */
	string trim(string s);

	/* Method called from crawl page that helps proccess images on a given webpage.
	 *
	 * Parameters:
	 * 	string: The text that is used to search for images.
	 *
	 * Returns:
	 * 	int: The number of images in a given webpage.
	 */
	int processImages(string &htmlTxt);

	/* Method called from crawl page that helps proccess customers on a given webpage.
	 *
	 * Parameters:
	 * 	string: The text that is used to search for words
	 *
	 * Returns: void
	 */
	void processCustomers(string &htmlTxt);

	/* Method called from crawl page that helps proccess URLs on a given webpage.
	 *
	 * Parameters:
	 * 	string: The text that is used to search for words
	 *
	 * Returns: void
	 */
	void processURLs(string &htmlTxt);

	/* Method called from crawl page that helps proccess words on a given webpage.
	 *
	 * Parameters:
	 * 	string: The text that is used to search for words
	 *
	 * Returns: void
	 */
	void processWords(string &htmlTxt);

	/* Method to help parse html from a webpage.
	 *
	 * Parameters:
	 * 	string: String at position to start looking at.
	 * 	string: String at position to finish looking at.
	 * 	string: Text to search in.
	 * 	vector<string>&: Vector of successful parses.
	 *
	 * Returns: void
	 */
	void findSubString(string startString, string endString, string inputTxt,
			vector<string> &inputVec);

	/* This method is used to remove HTML code from customer comments.
	 * Some customer comments have urls in them which make it hard 
	 * to distinguish duplicates.
	 *
	 */
	string removeHTML(string s);

public:
	/* Constructor for a webpage.
	 *
	 * Parameters:
	 *	URL: url of the new webpage
	 *	int: depth of the current page(crawls to Global_Web_Data::maxDepth)
	 */
	webpage(URL* url, int depth);

	/* Main method called to open a webpage and start curl.
	 *
	 * Parameters: void
	 *
	 * Returns:
	 * 	const string: HTML of the webpage that was opened.
	 */
	const string openPage();

	/* Helper method called to open a webpage and start curl.
	 *
	 * Parameters:
	 * 	URL: url of the webpage to open.
	 *
	 * Returns:
	 * 	const string: HTML of the webpage that was opened.
	 */
	const string openPage(URL &url);

	/* Main method that is called by WebCrawler.C to start crawling the current webpage.
	 *
	 * Parameters: void
	 *
	 * Returns: void
	 */
	void crawlPage();

	/* Method that is used to get the URL of the current webpage.
	 *
	 * Parameters: void
	 *
	 * Returns:
	 * 	URL*: URL of current webpage.
	 */
	URL* getURL();

	/* Method for deleteing the webpage
	 *
	 * Parameters: void
	 *
	 * Returns: void
	 */
	~webpage();
};
#endif
