#include <sstream>
#include <iostream>
using namespace std;

#include "global_web_data.h"
#include "dictionary.h"
#include "hashTable.h"
#include "word.h"
#include "robots_txt.h"
#include "webpage.h"
#include "Customer.h"

Dictionary *Global_Web_Data::dictionary;
HashTable<URL> Global_Web_Data::urls;
HashTable<Word> Global_Web_Data::words;
HashTable<Word> Global_Web_Data::misspelledWords;
BST<Robots_txt> Global_Web_Data::robots_txt;
HashTable<Customer> Global_Web_Data::customers;
HashTable<Product> Global_Web_Data::products;
vector<webpage*> Global_Web_Data::webPageQueue;
timeval Global_Web_Data::lastDequeueTime;
long Global_Web_Data::timeThrottleMs;
int Global_Web_Data::maxCrawlDepth;
Global_Web_Data::dequeueAttemptState *Global_Web_Data::threadDequeueAttempts;
unsigned int Global_Web_Data::threadDequeueAttemptsSize;
int Global_Web_Data::imageCount;
int Global_Web_Data::dequeueCount;
int Global_Web_Data::wordsCount;
pthread_mutex_t Global_Web_Data::url_lock;
pthread_mutex_t Global_Web_Data::words_lock;
pthread_mutex_t Global_Web_Data::misspelledWords_lock;
pthread_mutex_t Global_Web_Data::customers_lock;
pthread_mutex_t Global_Web_Data::products_lock;
pthread_mutex_t Global_Web_Data::robots_txt_lock;
pthread_mutex_t Global_Web_Data::webPageQueue_lock;
pthread_mutex_t Global_Web_Data::maxCrawlDepth_lock;
pthread_mutex_t Global_Web_Data::threadDequeueAttempts_lock;
pthread_mutex_t Global_Web_Data::addWordLock;
pthread_mutex_t Global_Web_Data::dictionary_lock;
pthread_mutex_t Global_Web_Data::imageCount_lock;

Global_Web_Data::Initialize Global_Web_Data::init;

bool Global_Web_Data::addURL(URL *url) {
	if (Global_Web_Data::isURLDisallowed(url)) {
		return false;
	}

	pthread_mutex_lock(&url_lock); // Lock hash table access.
	bool returnVal = urls.add(url);
	pthread_mutex_unlock(&url_lock); // Unlock hash table access.

	return returnVal;
}

void Global_Web_Data::getURLs(vector<URL*> &inputVector) {
	pthread_mutex_lock(&url_lock);
	vector<URL*> *c = urls.getObjects();

	for (unsigned int i = 0; i < c->size(); i++) {
		inputVector.push_back(c->at(i));
		c->at(i) = NULL;
	}
	pthread_mutex_unlock(&url_lock);

	delete c;
}

void Global_Web_Data::setMaxDepth(int i) {
	maxCrawlDepth = i;
}

bool Global_Web_Data::isURLDisallowed(URL *url) {
	Robots_txt tempRobots_txt(url->getDomain(), "");
	Robots_txt *ptrRobots_txt = NULL;
	bool returnVal = false;

	pthread_mutex_lock(&robots_txt_lock); // Lock BST access.

	ptrRobots_txt = robots_txt.get(tempRobots_txt);

	if (ptrRobots_txt != NULL) {
		returnVal = ptrRobots_txt->isDisallowed(*url);
	}

	pthread_mutex_unlock(&robots_txt_lock); // Unlock BST access.

	return returnVal;
}

bool Global_Web_Data::checkWordExists(string &word) {
	bool returnVal;
	pthread_mutex_lock(&dictionary_lock);
	returnVal = dictionary->spelled_correctly(word);
	pthread_mutex_unlock(&dictionary_lock);
	return returnVal;
}

URL* Global_Web_Data::getURL(URL *url) {
	pthread_mutex_lock(&url_lock); // Lock hash table access.
	return urls.get(url);
	pthread_mutex_unlock(&url_lock); // Unlock hash table access
	return NULL;
}

void Global_Web_Data::enqueueWebPage(webpage *page) {
	pthread_mutex_trylock(&webPageQueue_lock);
	webPageQueue.push_back(page);
	pthread_mutex_unlock(&webPageQueue_lock);
}

webpage* Global_Web_Data::dequeueWebPage(unsigned int threadNumber) {
	pthread_mutex_lock(&webPageQueue_lock); // Lock webPageQueue access, elapsed time calculations.

	// Calculate how many milliseconds have elapsed since the last dequeue.
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	long elapsedTimeMs = (long) (currentTime.tv_sec - lastDequeueTime.tv_sec)
			* 1000.0;
	elapsedTimeMs += (long) (currentTime.tv_usec - lastDequeueTime.tv_usec)
			/ 1000.0;

	if (elapsedTimeMs < timeThrottleMs) // Don't dequeue again until the required throttle time elapses.
			{
		usleep((timeThrottleMs - elapsedTimeMs) * 1000);
	}

	webpage *returnPage = NULL;

	if (webPageQueue.size() > 0) {
		returnPage = webPageQueue.front();
		webPageQueue.front() = NULL;
		webPageQueue.erase(webPageQueue.begin());
		updateThreadDequeue(threadNumber, Global_Web_Data::DEQUEUE_SUCCESS);
		dequeueCount++;
	} else {
		updateThreadDequeue(threadNumber, Global_Web_Data::DEQUEUE_FAILURE);
	}

	gettimeofday(&lastDequeueTime, NULL); // Mark the last dequeue time.

	pthread_mutex_unlock(&webPageQueue_lock); // Unlock webPageQueue access, elapsed time calculations.
	return returnPage;
}

bool Global_Web_Data::addRobots_txt(Robots_txt *r) {
	bool returnVal = false;
	pthread_mutex_lock(&robots_txt_lock); // Lock BST access.
	returnVal = robots_txt.add(r);
	pthread_mutex_unlock(&robots_txt_lock); // Unlock BST access.

	return returnVal;
}

string Global_Web_Data::toString() {
	stringstream returnString;
	returnString << urls.toString();
	returnString << "\n";
	returnString << robots_txt.toString();

	return returnString.str();
}

int Global_Web_Data::getDequeueCount()
{
  return dequeueCount;
}

bool Global_Web_Data::maxDepthReached(int currentDepth) {
	pthread_mutex_lock(&maxCrawlDepth_lock); // Lock maxCrawlDepth access.

	if (maxCrawlDepth < 0) {
		return false;
	}

	bool returnVal = currentDepth >= maxCrawlDepth;
	pthread_mutex_unlock(&maxCrawlDepth_lock); // Unlock maxCrawlDepth access.

	return returnVal;
}

bool Global_Web_Data::isQueueEmpty() {
	bool returnVal = true;

	pthread_mutex_lock(&threadDequeueAttempts_lock);

	for (unsigned int i = 0; i < threadDequeueAttemptsSize; i++) {
		if (threadDequeueAttempts[i] != Global_Web_Data::DEQUEUE_NO_ATTEMPT
				&& threadDequeueAttempts[i] == Global_Web_Data::DEQUEUE_SUCCESS) {
			returnVal = false;
			i = threadDequeueAttemptsSize + 1;
		}
	}

	pthread_mutex_unlock(&threadDequeueAttempts_lock);

	return returnVal;
}

void Global_Web_Data::updateThreadDequeue(unsigned int threadNumber,
		dequeueAttemptState state) {
	pthread_mutex_lock(&threadDequeueAttempts_lock);

	if (threadNumber > threadDequeueAttemptsSize - 1) {
		dequeueAttemptState *replacement = new dequeueAttemptState[threadNumber
				+ 1];

		for (unsigned int i = 0; i < threadNumber + 1; i++) {
			replacement[i] = Global_Web_Data::DEQUEUE_NO_ATTEMPT;
		}

		for (unsigned int i = 0; i < threadDequeueAttemptsSize; i++) {
			replacement[i] = threadDequeueAttempts[i];
		}

		delete[] threadDequeueAttempts;
		threadDequeueAttempts = replacement;
		threadDequeueAttemptsSize = threadNumber + 1;
	}

	threadDequeueAttempts[threadNumber] = state;

	pthread_mutex_unlock(&threadDequeueAttempts_lock);
}

void Global_Web_Data::addWordsToDictionary(vector<string> &words) {
	pthread_mutex_lock(&dictionary_lock);
	dictionary->addWords(words);
	pthread_mutex_unlock(&dictionary_lock);
}

void Global_Web_Data::incrementImageCount() {
	pthread_mutex_lock(&imageCount_lock);
	imageCount++;
	pthread_mutex_unlock(&imageCount_lock);
}

int Global_Web_Data::getImageCount() {
	int returnVal;
	pthread_mutex_lock(&imageCount_lock);
	returnVal = imageCount;
	pthread_mutex_unlock(&imageCount_lock);
	return returnVal;
}

void Global_Web_Data::getWords(vector<Word*> &inputVector) {
	pthread_mutex_lock(&words_lock);
	vector<Word*> *w = words.getObjects();

	for (unsigned int i = 0; i < w->size(); i++) {
		inputVector.push_back(w->at(i));
		w->at(i) = NULL;
	}
	pthread_mutex_unlock(&words_lock);

	delete w;
}

bool Global_Web_Data::addWord(Word *input) {
	bool returnVal;
	pthread_mutex_lock(&words_lock);
	returnVal = words.add(input);
	if (!returnVal) {
		words.get(input)->incrementWordCount();
	} wordsCount++;
	pthread_mutex_unlock(&words_lock);
	return returnVal;
}

void Global_Web_Data::getMisspelledWords(vector<Word*> &inputVector) {
	pthread_mutex_lock(&misspelledWords_lock);
	vector<Word*> *w = misspelledWords.getObjects();

	for (unsigned int i = 0; i < w->size(); i++) {
		inputVector.push_back(w->at(i));
		w->at(i) = NULL;
	}
	pthread_mutex_unlock(&misspelledWords_lock);

	delete w;
}

bool Global_Web_Data::addMisspelledWord(Word *input) {
	bool returnVal;
	pthread_mutex_lock(&misspelledWords_lock);
	returnVal = misspelledWords.add(input);
	if (!returnVal) {
		misspelledWords.get(input)->incrementWordCount();
	}
	pthread_mutex_unlock(&misspelledWords_lock);
	return returnVal;
}

void Global_Web_Data::getCustomers(vector<Customer*> &inputVector) {
	pthread_mutex_lock(&customers_lock);
	vector<Customer*> *c = customers.getObjects();

	for (unsigned int i = 0; i < c->size(); i++) {
		inputVector.push_back(c->at(i));
		c->at(i) = NULL;
	}
	pthread_mutex_unlock(&customers_lock);

	delete c;
}

bool Global_Web_Data::addCustomer(Customer *input) {
	bool returnVal = false;
	pthread_mutex_lock(&customers_lock);
	returnVal = customers.add(input);
	pthread_mutex_unlock(&customers_lock);
	return returnVal;
}

Customer* Global_Web_Data::getSingleCustomer(Customer *input) {
	pthread_mutex_lock(&customers_lock);
	Customer * tempCustomer = customers.get(input);
	pthread_mutex_unlock(&customers_lock);
	return tempCustomer;
}

void Global_Web_Data::getProducts(vector<Product*> &inputVector) {
	pthread_mutex_lock(&products_lock);
	vector<Product*> *c = products.getObjects();

	for (unsigned int i = 0; i < c->size(); i++) {
		inputVector.push_back(c->at(i));
		c->at(i) = NULL;
	}
	pthread_mutex_unlock(&products_lock);

	delete c;
}

bool Global_Web_Data::addProduct(Product *input) {
	bool returnVal = false;
	pthread_mutex_lock(&products_lock);
	returnVal = products.add(input);
	pthread_mutex_unlock(&products_lock);
	return returnVal;
}

Product* Global_Web_Data::getSingleProduct(Product *input) {
	pthread_mutex_lock(&products_lock);
	Product * tempProduct = products.get(input);
	pthread_mutex_unlock(&products_lock);
	return tempProduct;
}

int Global_Web_Data::getWordsCount()
{
  return wordsCount;
}
