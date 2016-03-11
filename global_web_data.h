/*
 * Ryan Finn
 * Braden Edmunds
 * Abdullah Aldobaie
 * Nathan Patterson
 *
 * Class Global_Web_Data provides a convenient means of storing and retrieving
 * information that is shared by multiple instances of the objects in this project.
 * The class guarantees thread-safe operations for insertion and retrieval of data.
 * The class does not guarantee thread-safe operations on data retrieved from the class.
 */

#ifndef GLOBAL_WEB_DATA_H
#define GLOGAL_WEB_DATA_H

#include <iostream>
#include <sys/time.h>
#include <pthread.h>
#include <vector>
using namespace std;

#include "hashTable.h"
#include "url.h"
#include "robots_txt.h"
#include "bst.h"
#include "webpage.h"
#include "dictionary.h"
#include "Customer.h"
#include "product.h"

class Global_Web_Data
{
 public:

  /* Method allows user to insert a pointer to a URL object.  If a URL object with the
   * same hash code already exists in Global_Web_Data, false is returned, true otherwise.
   *
   * Input: URL *url // the URL pointer to be added to Global_Web_Data.
   * Return Value: A boolean representing whether or not the pointer was added.
   */
  static bool addURL(URL *url);

  /* Returns a pointer to a URL with the same hash code as the provided URL.  Method
   * returns NULL if no matching URL is found.
   *
   * Input: URL *url // Pointer to URL who's hash code will be compared.
   * Return Value: A pointer to a URL who's hash code matches the URL provided as input.
   *               Return pointer may be NULL if no matching URL is found.
   */
  static URL* getURL(URL *url);

  /* Method fills the provided vector with pointers to all the URL pointers stored by
   * Global_Web_Data.
   *
   * Input: vector<URL*> &inputVector // Reference to vector that will be filled with
   *        every URL pointer stored by Global_Web_Data.
   */
  static void getURLs(vector<URL*> &inputVector);


  /* Method allows user to insert a pointer to a Word object.  If a Word object with the
   * same hash code already exists in Global_Web_Data, false is returned, true otherwise.
   *
   * Input: Word *input // Word pointer to be added to Global_Web_Data.
   * Return Value: A boolean representing whether or not the pointer was added.
   */
  static bool addWord(Word *input);

  /* Method fills the provided vector with pointers to all the Word pointers stored by
   * Global_Web_Data.
   *
   * Input: vector<Word*> &inputVector // Reference to vector that will be filled with
   *        every Word pointer stored by Global_Web_Data.
   */
  static void getWords(vector<Word*> &inputVector);

  /* Method gets the count of all detected words during crawling.
   *
   * return: int wordsCount
   */
  static int getWordsCount();

  /* Method allows user to insert a pointer to a Word object.  If a Word object with the
   * same hash code already exists in Global_Web_Data, false is returned, true otherwise.
   *
   * Input: Word *input // Word pointer to be added to Global_Web_Data.
   * Return Value: A boolean representing whether or not the pointer was added.
   */
  static bool addMisspelledWord(Word *input);

  /* Method fills the provided vector with pointers to all the Word pointers stored by
   * Global_Web_Data.
   *
   * Input: vector<Word*> &inputVector // Reference to vector that will be filled with
   *        every Word pointer stored by Global_Web_Data.
   */
  static void getMisspelledWords(vector<Word*> &inputVector);

  /* Method allows user to insert a pointer to a Customer object.  If a Customer object with the
   * same hash code already exists in Global_Web_Data, false is returned, true otherwise.
   *
   * Input: Customer *input // Customer pointer to be added to Global_Web_Data.
   * Return Value: A boolean representing whether or not the pointer was added.
   */
  static bool addCustomer(Customer *input);


  /* Method fills the provided vector with pointers to all the Customer pointers stored by
   * Global_Web_Data.
   *
   * Input: vector<Customer*> &inputVector // Reference to vector that will be filled with
   *        every Customer pointer stored by Global_Web_Data.
   */
  static void getCustomers(vector<Customer*> &inputVector);

  /* Returns a pointer to a Customer with the same hash code as the provided Customer.  Method
   * returns NULL if no matching URL is found.
   *
   * Input: Customer *input // Pointer to Customer who's hash code will be compared.
   * Return Value: A pointer to a Customer who's hash code matches the Customer provided as input.
   *               Return pointer may be NULL if no matching URL is found.
   */
  static Customer* getSingleCustomer(Customer *input);

  /* Method allows user to insert a pointer to a Product object.  If a Product object with the
   * same hash code already exists in Global_Web_Data, false is returned, true otherwise.
   *
   * Input: Product *input // Product pointer to be added to Global_Web_Data.
   * Return Value: A boolean representing whether or not the pointer was added.
   */
  static bool addProduct(Product *input);

  /* Method fills the provided vector with pointers to all the Product pointers stored by
   * Global_Web_Data.
   *
   * Input: vector<Product*> &inputVector // Reference to vector that will be filled with
   *        every Product pointer stored by Global_Web_Data.
   */
  static void getProducts(vector<Product*> &inputVector);

  /* Returns a pointer to a Product with the same hash code as the provided Product.  Method
   * returns NULL if no matching URL is found.
   *
   * Input: Product *input // Pointer to Product who's hash code will be compared.
   * Return Value: A pointer to a Customer who's hash code matches the Customer provided as input.
   *               Return pointer may be NULL if no matching URL is found.
   */
  static Product* getSingleProduct(Product *input);

  /* Method returns a boolean representing whether or not a URL should be crawled.
   * One reason a URL may not be crawled is that it is disallowed by [domain]/robots.txt.
   *
   * Input: URL *url // URL pointer to URL that is to be determined whether or not it should be crawled.
   * Return Value: Returs true if the URL should be crawled, false otherwise.
   */
  static bool isURLDisallowed(URL *url);

  /* Method allows a user to add a pointer to a Robots_txt object to Global_Web_Data.
   *
   * Input: Robots_txt *r // Robots_txt pointer to be added to Global_Web_Data.
   * Return Value: Returns true if the pointer is added, false if the pointer was not
   * added because another Robots_txt object with the same domain had already been added.
   */
  static bool addRobots_txt(Robots_txt *r);

  /* Method allows user to add words to the dictionary stored in Global_Web_Data.
   *
   * Input: vector<string> &words // A vector full of strings to be added to the dictionary.
   */
  static void addWordsToDictionary(vector<string> &words);

  /* Method allows user to check if a word is spelled correctly according to the dictionary stored by Global_Web_Data.
   *
   * Input: string &word // String representing a word to be verified against the dictionary.
   * Return Value: Boolean representing whether or not the word was found in the dicationary.
   */
  static bool checkWordExists(string &word);

  /* Method allows user to enqueue a web page object so that it may be crawled later.
   *
   * Input: webpage *page // webpage to be enqueued.
   */
  static void enqueueWebPage(webpage *page);

  /* Method allows user to override the default crawl depth of 16.
   *
   * Input: int i // The value that will become the new crawl depth limit.
   */
  static void setMaxDepth(int i);

  /* Method allows a user to dequeue a webpage, likely to call the webpage's crawl method.
   * Method will make the caller wait if the call is made before the time throttle has elapsed.
   *
   * Input: unsigned int threadNumber // The number of the thread who is making the function call.
            This number is needed to determine whether or not the queue is empty.
   */
  static webpage* dequeueWebPage(unsigned int threadNumber);

  /* Method adds 1 to the total number of images detected during crawling.
   */
  static void incrementImageCount();

  /* Method returns the number of images detected during crawling.
   *
   * Return Value: Integer representing the number of images detected during crawling.
   */
  static int getImageCount();

  /* Method returns the number of webpages that have been dequeued duing crawling.
   * Method is useful for determining a close approximation of how many pages were
   * crawled over the execution of the program.
   */
  static int getDequeueCount();

  /* Method returns a boolean representing whether or not the input represents the maximum
   * allowd crawl depth.
   *
   * Input: int currentDepth // Represents the current depth of a web page.
   * Return Value: Returns a boolean representing whether or not the input represents
   * the maximum allowed crawl depth.
   */
  static bool maxDepthReached(int currentDepth);

  /* Returns a boolean representing whether or not the queue of webpages is empty.
   */
  static bool isQueueEmpty();

  /* Returns a string representation of Global_Web_Data.
   */
  static string toString();

 private:
  static Dictionary *dictionary;           // Pointer to dictionarly object used to verfiy words.
  static HashTable<URL> urls;              // Hash table of URL objects.
  static HashTable<Word> words;            // Hash table of Word objects.
  static HashTable<Word> misspelledWords;  // Hash table of Word objects representing misspelled words.
  static HashTable<Customer> customers;    // Hash table of Customer objects.
  static HashTable<Product> products;      // Hash table of Product objects.
  static BST<Robots_txt> robots_txt;       // Binary search tree of Robots_txt objects.
  static vector<webpage*> webPageQueue;    // Vector of webpage pointers representing the webpage crawl queue.
  static timeval lastDequeueTime;          // timeval to store the time of the last dequeue operation.
  static long timeThrottleMs;              // Long to store the number of milliseconds that must elapse between dequeue operations.
  static int maxCrawlDepth;                // Stores the maximum allowed crawl depth.
  static int imageCount;                   // Stores the number of images detected during crawling.
  static int dequeueCount;                 // Stores the number of webpage dequeues that occured duing crawling.
  static int wordsCount;                   // Stores the number of all words detected during cralwing
  // Represents webpage dequeue attempt outcomes.
  enum dequeueAttemptState
  {
    DEQUEUE_SUCCESS,
    DEQUEUE_FAILURE,
    DEQUEUE_NO_ATTEMPT
  };

  static dequeueAttemptState *threadDequeueAttempts;  // Stores array of dequeue attempt states.
  static unsigned int threadDequeueAttemptsSize;      // The size of the array that stores webpage dequeue attempt states.

  /* Method updates the array that stores the webpage dequeue attempt states.
   *
   * Input: unsigned int threadNumber // The thread number of the thread performing the dequeue attempt.
            dequeueAttemptState state // The dequeue attempt state.
   */
  static void updateThreadDequeue(unsigned int threadNumber, dequeueAttemptState state);


  static pthread_mutex_t url_lock;                      // Locks the URL hash table.
  static pthread_mutex_t words_lock;                    // Locks the Words hash table.
  static pthread_mutex_t misspelledWords_lock;          // Locks the misspelled words hash table.
  static pthread_mutex_t customers_lock;                // Locks the customers hash table.
  static pthread_mutex_t products_lock;                 // Locks the products hash table.
  static pthread_mutex_t robots_txt_lock;               // Locks the Robots_txt binary search tree.
  static pthread_mutex_t webPageQueue_lock;             // Locks the webpage queue vector.
  static pthread_mutex_t maxCrawlDepth_lock;            // Locks the maxCrawlDepth member variable.
  static pthread_mutex_t threadDequeueAttempts_lock;    // Locks the threadDequeueAttempts array.
  static pthread_mutex_t addWordLock;                   // Locks the addWord method.
  static pthread_mutex_t dictionary_lock;               // Locks the dictionary object.
  static pthread_mutex_t imageCount_lock;               // Locks the imageCount member variable.

  

  static class Initialize
  {
  public:
    Initialize()
      {
	timeThrottleMs = 125; // 8 request per second limit.
	maxCrawlDepth = 16;   // Crawl no deeper than 16 pages from the start page.
	imageCount = 0;
	wordsCount = 0;
	threadDequeueAttempts = new dequeueAttemptState[1];
	threadDequeueAttempts[0] = DEQUEUE_SUCCESS;
	threadDequeueAttemptsSize = 1;

	dictionary = new Dictionary();


	pthread_mutex_init(&url_lock, NULL);
	pthread_mutex_init(&words_lock, NULL);
	pthread_mutex_init(&misspelledWords_lock, NULL);
	pthread_mutex_init(&customers_lock, NULL);
	pthread_mutex_init(&products_lock, NULL);
	pthread_mutex_init(&robots_txt_lock, NULL);
	pthread_mutex_init(&webPageQueue_lock, NULL);
	pthread_mutex_init(&maxCrawlDepth_lock, NULL);
	pthread_mutex_init(&threadDequeueAttempts_lock, NULL);
	pthread_mutex_init(&addWordLock, NULL);
	pthread_mutex_init(&dictionary_lock, NULL);
	pthread_mutex_init(&imageCount_lock, NULL);
      }
  } init;
};
#endif
