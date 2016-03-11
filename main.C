/*
 * main.cpp
 *
 *  Created on: Feb 12, 2012
 *      Author: Braden
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
using namespace std;

#include "project3CommandParser.h"
#include "textFileReader.h"
#include "webCrawler.h"
#include "output.h"
#include "global_web_data.h"
#include <algorithm>

void produceOutput(void);

string domain;
string startPage;
int threadCount;
int missSpelled;
int topWords;

int main(int argc, char* argv[]) {

	string s = argv[0];
	cout << s << endl;
	int removeIndex = s.rfind("/");
	s = s.erase(removeIndex);
	s = s + "../src/dictionary";

	Project3CommandParser cp(argc, argv);

	// Begin loading the Dictionary.
	cout << "Loading Dictionary..." << endl;
	TextFileReader fileReader;
	string dictionaryFilePath = cp.getSingleValueByName(
			Project3CommandParser::FLAG_DICTIONARY);
	if (dictionaryFilePath.compare("") != 0) {
		fileReader.addFile(dictionaryFilePath);
	} else {
	  cout << "Please load a dictoinary file" << endl;
	  // fileReader.addFile(s);
	}
	vector<string> splitWords;
	fileReader.getSplitBySpace(splitWords);
	Global_Web_Data::addWordsToDictionary(splitWords);
	cout << "Dictionary loaded." << endl;
	// End loading the Dictionary.

	//domain to start crawling
	domain = cp.getSingleValueByName(Project3CommandParser::FLAG_DOMAIN);

	// start page/url.
	startPage = argv[1];

	//thread count
	threadCount =
			atoi(
					cp.getSingleValueByName(Project3CommandParser::FLAG_THREADS).c_str());
	if (threadCount > 8) {
		threadCount = 8;
	}
	if (threadCount < 1) {
		threadCount = 1;
	}

	//count of top misspelled words
	missSpelled = atoi(cp.getSingleValueByName(Project3CommandParser::FLAG_MISS).c_str());
	//	if (missSpelled > 100) {
	//	missSpelled = 100;
	//	}
	if (missSpelled < 1) {
		missSpelled = 100;
	}

	//histogram word count
	topWords = atoi(cp.getSingleValueByName(Project3CommandParser::FLAG_COUNT).c_str());
	//	if (topWords > 100) {
	//		topWords = 100;
	//	}
	if (topWords < 1) {
		topWords = 100;
	}

	//Begin load Robots.txt
	stringstream domainConcat;

	if (domain.size() == 0) {
		//if no domain is provided we only crawl the given page
		Global_Web_Data::setMaxDepth(1);
		domainConcat << startPage;
	} else {
		URL *tempU = new URL(startPage);
		domainConcat << tempU->getDomain();
		delete tempU;
	}

	domainConcat << "/robots.txt";
	cout << "Loading [" << domainConcat.str() << "]..." << endl;
	URL *robotsURL = new URL(domainConcat.str());
	webpage *robotsPage = new webpage(robotsURL, 1);
	Robots_txt *robots = new Robots_txt(robotsURL->getDomain(),
			robotsPage->openPage(*robotsURL));
	Global_Web_Data::addRobots_txt(robots);
	delete robotsPage;
	cout << "[" << domainConcat.str() << "] loaded." << endl;
	//End load Robots.txt

	//Begin initialize the webpage queue.
	URL *firstURL = new URL(startPage);
	webpage *firstPage = new webpage(firstURL, 1);
	Global_Web_Data::enqueueWebPage(firstPage);
	//End initialize the webpage queue.

	//Start worker threads.
	cout << "Starting worker threads..." << endl;
	WebCrawler crawler(threadCount);
	crawler.crawl();
	cout << "Crawling  " + startPage + "..." << endl;
	//End worker threads.

	//Register exit function(s):
	atexit(produceOutput);

	cout
			<< "Enter 0 (zero) then press Enter key to exit program early, "
			<< "or wait for program to exit automatically after finishing crawling."
			<< "\n";
	int i = 1;
	while (i != 0) {
		cin >> i;
	}

	return 0;
}

void produceOutput(void) {
	cout << "Writing output file(s)..." << endl;

	// Abdullah Outputbaie
	Output out;
	out.printResultsToHTML(domain, startPage, threadCount, missSpelled, topWords);

	cout << "Output file(s) written\nProgram exiting..." << endl;
}
