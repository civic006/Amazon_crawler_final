/* Ryan Finn
 * Braden Edmunds
 * Abdullah Aldobaie
 * Nathan Patterson
 *
 * Class HashTable is a template class that aims to provide a general purpose hash table
 * useful of CS 3505 projects.  To use HashTable, one must override the following operators:
 *
 * unsigned long getHash()
 * operator> override
 * operator< override
 * operator= override
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "bst.h"

template<class T>
class HashTable
{
 public:

  /* Constructor for HashTable.
   */
  HashTable();

  /* Destructor for HashTable.
   */
  ~HashTable();

  /* Method returns a boolean representing whether or not an object pointer was added.
   *
   * Input: T *inputObject // The pointer to the object to be added.
   * Return Value: Boolean representing whether or not the pointer was added. If the
   *               hash code of the object to be added matches an existing hash code,
   *               the pointer is not added and false is returned. True, other wise.
   */
  bool add(T *inputObject);

  /* Method returns a boolean representing whether or not an object with the same hash
   * code already exists in the hash table.
   *
   * Input: T *inputObject // The object who's existance is to be verified.
   * Return Value: True is returned if an object with the same hash code is found.
   *               False, otherwize.
   */
  bool exist(T *inputObject);

  /* Method returns pointer to object with the same hash code as the provided object.
   *
   * Input: T *object // Pointer to object who's hash code will be used to locate an
   *                     object that's already in there.
   * Return Value: Pointer to an object with the same hash code as the input. The return
   *               value may be NULL.
   */
  T* get(T *object);

  /* Method returns a string representation of this HashTable.
   */
  string toString();

  /* Method returns a vector of pointers to objects contained by HashTable.
   */
  vector<T*>* getObjects();

 private:
  int objectCount;                   // Stores the number of object pointers in HashTable
  int bucketCount;                   // Stores the number of buckets in HashTable.
  int nonNullBucketCount;            // Stores the number of non-NULL buckets in HashTable.
  BST<T> **buckets;                  // Stores an array of pointers to BST<T>s.  The bucckets in HashTable are BST<T>s.
  const double BUCKET_RESIZE_LIMIT;  // Stores what is to be the threshold that triggers a dynamic resize of **buckets.

  /* Method resizes the array of buckets if it reaches a threshold capacity.
   */
  void tableResizeIfNecessary();

  /* Sets all the positions of the given array to NULL.  Useful during dynamic array resizing.
   */
  void nullifyArray(BST<T> **array, int size);
};

template<class T>
HashTable<T>::HashTable()
: objectCount(0),
  bucketCount(16),
  nonNullBucketCount(0),
  BUCKET_RESIZE_LIMIT(3.0/4.0) // HashTable is resized when it becomes 3/4 full.
{
  buckets = new BST<T> *[bucketCount];
  nullifyArray(buckets, bucketCount);
}

template<class T>
HashTable<T>::~HashTable()
{
  for(int i = 0; i < bucketCount; i++)
    {
      delete buckets[i];
    }

  delete [] buckets;
}

template<class T>
bool HashTable<T>::add(T *inputObject)
{
  long insertAddress = inputObject->getHash() % bucketCount;
  if(insertAddress < 0)
    {
      insertAddress *= -1;
    }

  if(buckets[insertAddress] != NULL) // Is there already a bucket at this address?
    {
      bool inserted = buckets[insertAddress]->add(inputObject);

      if(inserted)
	{
	  objectCount++;
	}
      
      return inserted;
    }

  BST<T> *bst = new BST<T>;
  bst->add(inputObject);
  buckets[insertAddress] = bst;
  objectCount++;
  nonNullBucketCount++;

  tableResizeIfNecessary();

  return true;
}

template<class T>
T* HashTable<T>::get(T *object)
{
  long hashCode = object->getHash() % bucketCount;
  if(hashCode < 0)
    {
      hashCode *= -1;
    }

  if(buckets[hashCode] != NULL)
    {
      return buckets[hashCode]->get(*object);
    }

  return NULL;
}

template<class T>
void HashTable<T>::tableResizeIfNecessary()
{
  if((double)nonNullBucketCount / (double)bucketCount < BUCKET_RESIZE_LIMIT)
    {
      return;
    }

  vector<T*> *objects = getObjects();
  int numObjects = objects->size();
  int newTableSize = bucketCount + ((double)nonNullBucketCount / (double)bucketCount);
  newTableSize = numObjects * 2;

  BST<T> **moreBuckets = new BST<T> *[newTableSize];

  nullifyArray(moreBuckets, newTableSize);
  nullifyArray(buckets, bucketCount);
  delete [] buckets;

  buckets = moreBuckets;
  objectCount = 0;
  bucketCount = newTableSize;
  nonNullBucketCount = 0;

  for(int i = 0; i < numObjects; i++)
    {
      add(objects->at(i));
      objects->at(i) = NULL;
    }

  delete objects;
}

template<class T>
void HashTable<T>::nullifyArray(BST<T> **array, int size)
{
  for(int i = 0; i < size; i++)
    {
      array[i] = NULL;
    }
}

// I need to learn the best way to deal with this rampant memory leakage.
template<class T>
vector<T*>* HashTable<T>::getObjects()
{
  vector<T*> *returnVector = new vector<T*>();

  for(int i = 0; i < bucketCount; i++)
    {
      if(buckets[i] != NULL)
	{
	  vector<T*> contents = buckets[i]->getOrderedContents();
	  
	  for(unsigned int j = 0; j < contents.size(); j++)
	    {
	      returnVector->push_back(contents[j]);
	    }
	}
    }

  return returnVector;
}

template<class T>
bool HashTable<T>::exist(T *inputObject)
{
  long insertAddress = inputObject->getHash() % bucketCount;

  if(insertAddress < 0)
    {
      insertAddress *= -1;
    }
  
  if(buckets[insertAddress] != NULL)
    {
      return buckets[insertAddress]->exist(*inputObject);
    }

  return false;
}

template<class T>
string HashTable<T>::toString()
{
  stringstream returnString;
  vector<T*> *objects = getObjects();

  for(unsigned int i = 0; i < objects->size(); i++)
    {
      if(i > 0)
	{
	  returnString << "\n";
	}
      returnString << *(objects->at(i));
    }

  if(objects->size() > 0)
    {
      returnString << "\n";
    }

  returnString << "Number of objects in HashTable: " << objectCount << endl;
  returnString << "Number of buckets in HashTable: " << bucketCount << endl;
  returnString << "Number of non-null buckets:     " << nonNullBucketCount << endl;
  returnString << "Number of null buckets:         " << (bucketCount - nonNullBucketCount) << endl;

  return returnString.str();
}

#endif
