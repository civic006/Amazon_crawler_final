/* bst.h
 *
 * Abdullah Aldobaie
 * Braden Edmunds
 * Nathan Patterson
 * Ryan Finn
 *
 * Jan. 24, 2012
 *
 *
 * The class definition of the BST class.
 */


/* Template BST is a common Binary Search Tree template implemented by a student.
 * This BST will not add duplicates.
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "bstNode.h"



template<class T>
class BST
{
 public:

  /* Constructor for BST
   */
  BST();



  /* Destructor for BST
   */
  ~BST();



  /* Adds a new item to the BST if an item of the same value does not already
   * exist in BST.
   * Returns true if item was added, false otherwise.
   */
  bool add(T *key);



  /*Returns a pointer to an item in BST if the item is found.
   */
  T* get(const T &key);



  /* Returns a boolean representing whether or not an item exists in BST.
   */
  bool exist(const T &key);



  //Gets the similar Ts within the BST
  vector<T*> getSimilar(T &key, int count);



  /* Removes an item from BST if the item is found.
   * Returns a boolean representing whether or not the item was found and
   * therefore removed.
   */
  bool remove(T &key);



  /* Returns size of BST.
   */
  unsigned int getSize();
 


  /* Returns a vector of pointers to BST node contents. This method threatens
   * the integrity of the BST because node values could be changed, making them
   * impossible to lookup.
   */
  vector<T*> getOrderedContents();



  /* Returns a string representation of BST.
   */
  string toString();




  /*
   * Returns the total number of words from the original file.
   */
  unsigned int getFileWordCount();



 private:

  unsigned int size; // The current size of BST (The number of nodes).
  unsigned int fileWordCount; //Count of all the words in the file.
  BSTNode<T> *head;  // The highest node.



  /* Adds a new item to the BST if an item of the same value does not already
   * exist in BST.
   * Returns true if item was added, false otherwise.
   */
  bool addNode(BSTNode<T>* &treeNode, BSTNode<T> *newNode);



  /*Returns a pointer to an item in BST if the item is found.
   */
  BSTNode<T>* getNode(BSTNode<T> *node, const T &key);



  /* Fills a vector with pointers to BST node contents. The vector will be
   * ordered based on the boolean operators of the contents objects.
   */
  void getOrderedContentsTraversal(vector<T*> &v, BSTNode<T> *n);



  /* Gets similar Ts in BST.
   */
  int getSimilar(BSTNode<T> *node, vector<T*> *returnList, T &key, int count);
};



/**
 * BST class constructor
 */
template<class T>
BST<T>::BST()
: size(0),
  fileWordCount(0),
  head(NULL)
{
}



/**
 * BST class deconst.
 */
template<class T>
BST<T>::~BST()
{
  vector<T*> remainingContents = getOrderedContents();

  for(unsigned int i = 0; i < remainingContents.size(); i++)
    {
      delete remainingContents[i];
    }

  delete head;
}



/**
 * add: takes an element (key) to be added to the tree.
 * 
 * parameters: key (Type T)
 *
 * returns: true if word added, false otherwise.
 */
template<class T>
bool BST<T>::add(T *key)
{
  if(head == NULL)
    {
      head = new BSTNode<T>(key);
      size++;
      fileWordCount++;
      return true;
    }
  else
    {
      return addNode(head, new BSTNode<T>(key));
    }


  return false;
}



/**
 * addNode: adds a node that is created by add(), to the tree.
 *
 * Parameters: a tree(Type T), and newNode (Type T)
 *
 *
 * returns: true if the node is added to the tree, false otherwise.
 */
template<class T>
bool BST<T>::addNode(BSTNode<T>* &treeNode, BSTNode<T> *newNode)
{
  if(treeNode == NULL)
    {
      treeNode = newNode;
      size++;
      fileWordCount++;
      return true;
    }
  else if(*newNode < *treeNode)
    {
      return addNode(treeNode->getLeft(), newNode);
    }
  else if(*newNode > *treeNode)
    {
      return addNode(treeNode->getRight(), newNode);
    }
  else
    {
      fileWordCount++;
      delete newNode;
      return false;
    }

  return false;
}



/***
 * get: gets a node from the tree
 *
 * Parameters: takes an element key (Type T) to be looked up.
 *
 * Returns: a pointer (Type T) to the location, or NULL if key not found.
 */
template<class T>
T* BST<T>::get(const T &key)
{
  BSTNode<T> *returnNode = NULL;
  returnNode = getNode(head, key);
  
  if(returnNode != NULL)
    {
      return returnNode->getContents();
    }

  return NULL;
}



/***
 * getNode: finds the node where the given key is.
 *
 * Parameters: A tree (Type T), and an element key (Type T).
 *
 * Returns: A pointer (Type T) to the node, or NULL otherwise.
 */
template<class T>
BSTNode<T>* BST<T>::getNode(BSTNode<T> *node, const T &key)
{
  if(node == NULL)
    {
      return NULL;
    }

  if(key < *(node->getContents()))
    {
      return getNode(node->getLeft(), key);
    }
  else if(key > *(node->getContents()))
    {
      return getNode(node->getRight(), key);
    }
  else if(key == *(node->getContents()))
    {
      return node;
    }

  return NULL;
}



/**
 * exist: Looks up a key.
 *
 * Parameters: An element key (Type T)
 *
 * Returns: true if key is found, false otherwise.
 */
template<class T>
bool BST<T>::exist(const T &key)
{
  if(get(key) != NULL)
    {
      return true;
    }

  return false;
}




/***
 * getSize: gives the size of the tree.
 *
 * Parameters: None
 *
 * Returns: size (unsigned int)
 */
template<class T>
unsigned int BST<T>::getSize()
{
  return size;
}



/***
 * getFileWordCount: gives the word count appeared in the given file including
 *                   were not added because they already exist.
 *
 * Parameters: None
 *
 * Return: Count (unsigned int) 
 */
template<class T>
unsigned int BST<T>::getFileWordCount()
{
  return fileWordCount;
}



/***
 * getOrderedContents: gets the content of a node in order (left, middle, then right)
 *
 * Parameters: None
 *
 * Returns: the vector (Type T) contains the contents of the node.
 */
template<class T>
vector<T*> BST<T>::getOrderedContents()
{
  vector<T*> *ptrV = new vector<T*>();

  getOrderedContentsTraversal(*ptrV, head);

  return *ptrV;
}



/***
 * getOrderedContentsTraversal: 
 *
 * Parameters: a vector pointer Tree (Type T), and a node (Type T)
 *
 * Returns: None
 */
template<class T>
void BST<T>::getOrderedContentsTraversal(vector<T*> &v, BSTNode<T> *n)
{
  if(n != NULL)
    {
      getOrderedContentsTraversal(v, n->getLeft());
      v.push_back(n->getContents());
      getOrderedContentsTraversal(v, n->getRight());
}
}



/**
 * getSimilar: gives similar contents to the given key, based on the location in the tree.
 *
 * Parameters: a key (Type T), and the count (int) of similar keys!
 *
 * Returns: vector (Type T) contains similar keys.
 */
template<class T>
vector<T*> BST<T>::getSimilar(T &key, int count)
{
  vector<T*> *returnList = new vector<T*>();

  if(count <= 0)
    {
      return *returnList;
    }

  BSTNode<T> *currentNode = getNode(head, key);
  BSTNode<T> *leftNode = NULL;
  BSTNode<T> *rightNode = NULL;

  if(currentNode == NULL)
    {
      return *returnList;
    }

  int leftDepth = count / 2;
  int rightDepth = count - leftDepth;

  leftNode = currentNode->getLeft();
  rightNode = currentNode->getRight();

  if(leftNode != NULL)
    {
      returnList->push_back(leftNode->getContents());
      leftDepth--;
      leftDepth = getSimilar(leftNode, returnList, *leftNode->getContents(), leftDepth);
      rightDepth += leftDepth;
    }
  
  if(rightNode != NULL)
    {
      returnList->push_back(rightNode->getContents());
      rightDepth--;
      rightDepth = getSimilar(rightNode, returnList, *rightNode->getContents(), rightDepth);
    }
  
  return *returnList;
}



/***
 * getSimilar: same as getSimilar(T &key, int count) but the rurn list is provided by address,
 *             and the Tree to be searched.
 *
 * returns: count (int)
 */
template<class T>
int BST<T>::getSimilar(BSTNode<T> *node, vector<T*> *returnList, T &key, int count)
{
  if(count <= 0)
    {
      return count;
    }

  BSTNode<T> *currentNode = getNode(node, key);
  BSTNode<T> *leftNode = NULL;
  BSTNode<T> *rightNode = NULL;
  
  if(currentNode == NULL)
    {
      return count;
    }
  
  int leftDepth = count / 2;
  int rightDepth = count - leftDepth;
  
  leftNode = currentNode->getLeft();
  rightNode = currentNode->getRight();
  
  if(leftNode != NULL)
    {
      returnList->push_back(leftNode->getContents());
      leftDepth--;
      leftDepth = getSimilar(leftNode, returnList, *leftNode->getContents(), leftDepth);
      rightDepth += leftDepth;
    }
  
  if(rightNode != NULL)
    {
      returnList->push_back(rightNode->getContents());
      rightDepth--;
      rightDepth = getSimilar(rightNode, returnList, *rightNode->getContents(), rightDepth);
    }

  return rightDepth + leftDepth;
}




/***
 * remove: removes a key from the tree.
 *
 * Parameters: a key (Type T) to be removed.
 *
 * Returns: true if key is removed, false otherwise.
 */
template<class T>
bool BST<T>::remove(T &key)
{
  if (head == NULL)
    {
      return false;
    }
  else
    {
      if (*(head->getContents()) == key)
	{
	  BSTNode<T> auxRoot(&key);
	  //auxRoot.setLeftChild(head);
	  auxRoot.getLeft() = head;
	  BSTNode<T> *removedNode = head->remove(key, &auxRoot);
	  head  = auxRoot.getLeft();
	  if (removedNode != NULL)
	    {
	      delete removedNode;
	      size--;
	      return true;
	    }
	  else
	    {
	      return false;
	    }
	}
      else
	{
	  BSTNode<T>* removedNode = head->remove(key, NULL);
	  if (removedNode != NULL)
	    {
	      delete removedNode;
	      size--;
	      return true;
	    }
	  else
	    {
	      return false;
	    }
	}
    }
}



/***
 * toString:  overload the toString() to output all contents of the tree.
 *
 * Parameters: None
 *
 * Returns: a string contains all contents.
 */
template<class T>
string BST<T>::toString()
{
  stringstream returnString;
  vector<T*> nodeContents = getOrderedContents();
  
  for(unsigned int i = 0; i < nodeContents.size(); i++)
    {
      if(i > 0)
	{
	  returnString << "\n";
	}
      returnString << *nodeContents[i];
    }

  if(nodeContents.size() > 0)
    {
      returnString << "\n";
    }

  returnString << "Number of objects in tree: " << getSize();

  return returnString.str();
}

#endif
