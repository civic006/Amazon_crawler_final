/***
 * webCrawler.h
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
 * A web crawler class will be used to create a web page
 *   from the URLs in the given domain.
 */

#ifndef _WEBCRAWLER__H
#define _WEBCRAWLER__H


#include <stdio.h>
#include <string>
#include "webpage.h"
#include "url.h"

using namespace std;

class WebCrawler
{


 public:

	 int threadCount;
 /**
  * WebCrawler: Constructor
  *
  * Parameters:
  *   - int depth: the depth limit from the given url.
  *                 By default the depth is 16.
  *
  */
 WebCrawler(int tCount);

 /*
  * This method initiates each thread and then sends it to the go function.
  */
 void crawl();

 /**
  *  This method is the starting point for each thread that webcrawler is given.
  */
 static void *go(void *args);
 /**
  * WebCrawler: destructor
  *
  */
  ~WebCrawler();



};

#endif
