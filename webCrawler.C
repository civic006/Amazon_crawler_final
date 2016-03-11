/***
 * webCrawler.C
 *
 * Authors:
 *   Abdullah Aldobaie
 *   Nathan Patterson
 *   Braden Edmunds
 *   Ryan Finn
 *
 * Date:
 *   Feb. 14, 2012
 *
 * The definition of functions in webCrawler.h
 */

#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

#include "webCrawler.h"
#include "global_web_data.h"

/**
 * WebCrawler: Constructor
 *
 * Parameters:
 *   - int tCount:  The number of worker threads to create.
 *
 */
WebCrawler::WebCrawler(int tCount) :
		threadCount(tCount) {
}
/***
 * This method initiates the multi-threading by creating X amount of pthreads and then
 * sending them to the starting function.
 */
void WebCrawler::crawl() {
	for (int i = 0; i < threadCount; i++) {
		pthread_t workerThread;
		int *threadNumber = new int(i);
		pthread_create(&workerThread, NULL, go, (void *) threadNumber);
	}
}
/*
 *
 * This method loops while there are Webpage's in the queue. Once a thread
 * obtains a webpage it opens it and begins to crawl it. It parses the data within
 * and once completed will attempt to grab another webpage.
 *
 */
void* WebCrawler::go(void *threadNumber) {
	int myThreadNumber = *(int*) threadNumber;

	while (!Global_Web_Data::isQueueEmpty()) {
		webpage *page = Global_Web_Data::dequeueWebPage(myThreadNumber);

		if (page != NULL) {
			stringstream out;
			string s;
			out << endl << "Thread:" << myThreadNumber << endl;
			s = out.str();
			cout << s;
			page->crawlPage();
		}
	}

	exit(0);
	return NULL;
}

/**
 * WebCrawler: destructor
 *
 */
WebCrawler::~WebCrawler() {

}

