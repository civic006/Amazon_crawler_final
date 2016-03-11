/*
 * webpage.C
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

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include "global_web_data.h"
#include "webpage.h"
#include "url.h"
#include "product.h"

using namespace std;

/* Constructor for a webpage.
 *
 * Parameters:
 *	URL: url of the new webpage
 *	int: depth of the current page(crawls to Global_Web_Data::maxDepth)
 */
webpage::webpage(URL* url, int depth) {
	this->depth = depth;
	myURL = url;
}

/* Static method, used for the buffer, called by the openPage() method which starts curl.
 *
 * Parameters:
 * 	void*: ptr
 * 	size_t: size
 * 	size_t: nmemb
 *
 * Returns:
 * 	size_t
 */
static size_t write_function(void *ptr, size_t size, size_t nmemb,
		void *userdata) {
	// use buffer as reference so we can use nice . syntax below
	string &buffer = *(string*) userdata;

	// debug info
	/*	printf("in write function, size %d, nmemb %d, userdata %p\n", (uint) size,
	 (uint) nmemb, userdata);*/

	// save current state
	buffer.append((char*) ptr, size * nmemb);

	return size * nmemb;
}

/* Main method called to open a webpage and start curl.
 *
 * Parameters: void
 *
 * Returns:
 * 	const string: HTML of the webpage that was opened.
 */
const string webpage::openPage() {
	return openPage(*myURL);
}

/* Helper method called to open a webpage and start curl.
 *
 * Parameters:
 * 	URL: url of the webpage to open.
 *
 * Returns:
 * 	const string: HTML of the webpage that was opened.
 */
const string webpage::openPage(URL &url) {
	CURL *curl;
	CURLcode res;

	const string buffer;

	curl = curl_easy_init();
	if (curl) {
		string s = myURL->getURL();
		string ss;
		stringstream out;
		out << "curl:  " << s.c_str() << endl;
		ss = out.str();
		cout << ss;
		curl_easy_setopt(curl, CURLOPT_URL, s.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "cs3505_aefp");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		res = curl_easy_perform(curl);

		if (res) {
			printf("\noops, res is %d\n", res);
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return buffer;
}

/* Main method that is called by WebCrawler.C to start crawling the current webpage.
 *
 * Parameters: void
 *
 * Returns: void
 */
void webpage::crawlPage() {
	if (Global_Web_Data::maxDepthReached(depth + 1)) {
		return;
	}

	string htmlTxt = openPage(); //Buffer for all parsing.

	// Begin parse all the stuff we want statistics about.
	// Begin parse out image urls.
	processImages(htmlTxt);
	// End parse out image urls

	//TODO: Make sure URL class returns lower cased domain.
	if (myURL->getDomain().compare("amazon.com") == 0) {
		// Begin parse out customer info.
		processCustomers(htmlTxt);
		// End parse out customer info.
	}

	// Bigin parse words on page.
	processWords(htmlTxt);
	// End parse words on page.
	// End parse all the stuff we want statistics about.

	// Begin parse all URLs.
	processURLs(htmlTxt);
	// End parse all URLs.
}

/* Method that is used to get the URL of the current webpage.
 *
 * Parameters: void
 *
 * Returns:
 * 	URL*: URL of current webpage.
 */
URL* webpage::getURL() {
	return myURL;
}

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
void webpage::findSubString(string startString, string endString,
		string inputTxt, vector<string> &inputVec) {
	size_t startIndex = inputTxt.find(startString);
	size_t endIndex = 0;

	while (startIndex != string::npos) {
		startIndex += startString.size();
		endIndex = inputTxt.find(endString, startIndex);

		if (endIndex != string::npos) {
			inputVec.push_back(
					inputTxt.substr(startIndex, endIndex - startIndex));
			startIndex = inputTxt.find(startString, endIndex);
		} else {
			startIndex = string::npos;
		}
	}
}

/* Helps to trim a string of whitespaces before and after a string.
 *
 * Parameters:
 * 	string: String to trim.
 *
 * Returns:
 * 	string: The trimmed string.
 */
string webpage::trim(string s) {
	string whitespaces = " \t\f\v\n\r";

	const size_t beginStr = s.find_first_not_of(whitespaces);

	if (beginStr != string::npos) {
		s = s.substr(beginStr, s.size() - beginStr);
	} else {
		s.clear(); // str is all whitespace
	}

	const size_t endStr = s.find_last_not_of(whitespaces);

	if (endStr != string::npos) {
		s = s.substr(0, endStr + 1);
	} else {
		s.clear(); // str is all whitespace
	}
	return s;
}

/* Method called from crawl page that helps proccess words on a given webpage.
 *
 * Parameters:
 * 	string: The text that is used to search for words
 *
 * Returns: void
 */
void webpage::processWords(string &htmlTxt) {
	vector<string> sentences;
	vector<string> splitWords;

	size_t bodyStart = htmlTxt.find("body>");
	size_t bodyEnd = 0;

	if (bodyStart == string::npos) {
		return;
	}

	bodyEnd = htmlTxt.find("</body");

	if (bodyEnd == string::npos) {
		return;
	}

	string bodyTxt = htmlTxt.substr(bodyStart, bodyEnd - bodyStart);

	findSubString(">", "<", bodyTxt, sentences);

	for (unsigned int i = 0; i < sentences.size(); i++) {
		findSubString(" ", " ", sentences[i], splitWords);
	}

	for (unsigned int i = 0; i < splitWords.size(); i++) {
		if (splitWords[i].size() > 0) {
			Word *w = new Word(splitWords[i]);
			if (!Global_Web_Data::addWord(w)) {
				delete w;
			}
		}
	}
}

/* Method called from crawl page that helps proccess images on a given webpage.
 *
 * Parameters:
 * 	string: The text that is used to search for images.
 *
 * Returns:
 * 	int: The number of images in a given webpage.
 */
int webpage::processImages(string &htmlTxt) {
	vector<string> imgAttributes;
	vector<string> imgs;

	findSubString("<img", ">", htmlTxt, imgAttributes);

	for (unsigned int i = 0; i < imgAttributes.size(); i++) {
		findSubString("src=\"", "\"", imgAttributes[i], imgs);
		findSubString("src=\'", "\'", imgAttributes[i], imgs);
	}

	for (unsigned int i = 0; i < imgs.size(); i++) {
		Global_Web_Data::incrementImageCount();
	}

	return imgs.size();
}

/* Method called from crawl page that helps proccess customers on a given webpage.
 *
 * Parameters:
 * 	string: The text that is used to search for words
 *
 * Returns: void
 */
void webpage::processCustomers(string &htmlTxt) {
	vector<string> customerBoundaries;
	vector<string> rating;
	vector<string> date;
	vector<string> name;
	vector<string> comment;
	vector<string> location;
	vector<string> helpful;
	string productTitle = "Default Product Title";
	bool foundCustomer = false;

	findSubString("<!-- BOUNDARY -->",
			"style=\"padding-top: 10px; clear: both; width: 100%;", htmlTxt,
			customerBoundaries);

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		findSubString("title=\"", " out of 5 stars", customerBoundaries[i],
				rating);
		foundCustomer = true;
	}

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		findSubString("<nobr>", "</nobr>", customerBoundaries[i], date);
	}

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		findSubString("<span style = \"font-weight: bold;\">", "</span>",
				customerBoundaries[i], name);
	}

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		size_t reviewIndex = customerBoundaries[i].find("This review is from:");
		if (reviewIndex != string::npos) {
			size_t startIndex = customerBoundaries[i].find("</div>",
					reviewIndex);
			if (startIndex != string::npos) {
				startIndex += 6;
				size_t endIndex = customerBoundaries[i].find("<div",
						startIndex);
				if (endIndex != string::npos) {
				  string s = trim(customerBoundaries[i].substr(startIndex, endIndex - startIndex));
				  s = removeHTML(s);
				  comment.push_back(s);
				}
			}
		} else {
			// More scenarios...
			comment.push_back("Default comment.");
		}
	}

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		findSubString("</span></a> (", ")", customerBoundaries[i], location);
	}

	for (unsigned int i = 0; i < customerBoundaries.size(); i++) {
		findSubString("<div style=\"margin-bottom:0.5em;\">", "helpful",
				customerBoundaries[i], helpful);
	}

	if (foundCustomer) {
		string title = "<title>";
		size_t startIndex = htmlTxt.find(title);

		if (startIndex != string::npos) {
			startIndex += title.size();
			size_t endIndex = htmlTxt.find("</title>", startIndex);
			if (endIndex != string::npos) {
				productTitle = htmlTxt.substr(startIndex,
						endIndex - startIndex);
			}
		}
	}

	vector<Customer*> newCustomers;

	for (unsigned int i = 0;
			i < customerBoundaries.size() && i < rating.size()
					&& i < date.size() && i < name.size() && i < comment.size()
					&& i < location.size() && i < helpful.size(); i++) {
		Customer *c = new Customer(name[i], location[i]);
		c->addComments(comment[i], atof(rating[i].c_str()), date[i], helpful[i],
				productTitle);

		if (!Global_Web_Data::addCustomer(c)) {
			Customer *temp = Global_Web_Data::getSingleCustomer(c);
			vector<Comment> tempComments = temp->getComments();
			bool addComment =true;
			for(unsigned int j =0; j < tempComments.size(); j++)
			  {
			    if(tempComments.at(j).getComment().compare(comment[i]) == 0)
			      addComment = false;
			  }

			if(addComment)
			  temp->addComments(comment[i], atof(rating[i].c_str()), date[i],helpful[i], productTitle);
			delete c;
			c = temp;
		}

		newCustomers.push_back(c);
	}

	Product *p = new Product(productTitle, this->myURL);
	if (!Global_Web_Data::addProduct(p)) {
		Product *temp = Global_Web_Data::getSingleProduct(p);
		delete p;
		p = temp;
	}

	for (unsigned int i = 0; i < newCustomers.size(); i++) {
		p->addCustomer(newCustomers[i]);
	}
}

/* Method called from crawl page that helps proccess URLs on a given webpage.
 *
 * Parameters:
 * 	string: The text that is used to search for words
 *
 * Returns: void
 */
void webpage::processURLs(string &htmlTxt) {
	vector<string> hrefsAttributes;
	vector<string> hrefs;

	findSubString("<a", ">", htmlTxt, hrefsAttributes);

	for (unsigned int i = 0; i < hrefsAttributes.size(); i++) {
		findSubString("href=\"", "\"", hrefsAttributes[i], hrefs);
		findSubString("href=\'", "\'", hrefsAttributes[i], hrefs);
	}

	for (unsigned int i = 0; i < hrefs.size(); i++) {
		URL *u = new URL(myURL->getDomain(), hrefs[i]);
		if (myURL->getDomain().compare(u->getDomain()) == 0
				&& Global_Web_Data::addURL(u)) {
			webpage *w = new webpage(u, depth + 1);
			Global_Web_Data::enqueueWebPage(w);
		} else {
			delete u;
		}
	}
}

/* Method for deleteing the webpage
 *
 * Parameters: void
 *
 * Returns: void
 */
webpage::~webpage() {

}

/* This method is used to remove HTML code from customer comments.
 * Some customer comments have urls in them which make it hard 
 * to distinguish duplicates.
 *
 */
string webpage::removeHTML(string s) {
    try{
    string aStart = "<a";
    string aEnd = ">";
    size_t start = s.find(aStart, 0);
    size_t end;

    while (start != string::npos) {
        end = s.find(aEnd, start) + aEnd.size();
        if(end != string::npos){
        s.erase(start, end-start);
        }
        start = s.find(aStart, end);
    }
    }catch(int &e){
        cout << "Error removeHTML::" << e << endl;
    }

    return s;
}
