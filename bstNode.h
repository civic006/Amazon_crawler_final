/* This class template exists to server template class BST.
 * The class functions as a Binary Search Tree node.
 */

#ifndef BSTNODE_H
#define BSTNODE_H

#include <iostream>
using namespace std;

template <class T>
class BSTNode
{
 public:

  /* Constructor for BSTNode.
   */
  BSTNode(T *object);

  /* Destructor for BSTNode.
   */
  ~BSTNode();

  /* Returns the left child node.
   */
  BSTNode<T>*& getLeft();

  /* Returns the right child node.
   */
  BSTNode<T>*& getRight();

  /* Returns a BSTNode that is to be removed from the BST and then deleted.
   */
  BSTNode<T>* remove(T &key, BSTNode<T> *parent);

  /* Returns the contents of BSTNode.
   */
  T* getContents();

  bool operator<(const BSTNode<T> &other) const; //Operator overloading useful for BST.
  bool operator>(const BSTNode<T> &other) const;

 private:
  T *objectData;     // Stores BSTNode value data.

  BSTNode<T> *left;  // Stores pointer to left BSTNode.
  BSTNode<T> *right; // Stores pointer to right BSTNode.

  /* Returns the smaller of left and right BSTNode child nodes.
   */
  T* minValue();
};

template<class T>
BSTNode<T>::BSTNode(T *object)
:objectData(object),
  left(NULL),
  right(NULL)
{
}

template<class T>
BSTNode<T>::~BSTNode()
{
  //delete objectData;
  //delete left;
  //delete right;
}

template<class T>
BSTNode<T>*& BSTNode<T>::getLeft()
{
  return left;
}

template<class T>
BSTNode<T>*& BSTNode<T>::getRight()
{
  return right;
}

template<class T>
bool BSTNode<T>::operator<(const BSTNode<T> &other) const
{
  return *objectData < *(other.objectData);
}

template<class T>
bool BSTNode<T>::operator>(const BSTNode<T> &other) const
{
  return *objectData > *(other.objectData);
}

template<class T>
T* BSTNode<T>::getContents()
{
  return objectData;
}

template<class T>
BSTNode<T>* BSTNode<T>::remove(T &key, BSTNode<T> *parent)
{
  if (key < *objectData)
    {
      if (left != NULL)
	{
	  return left->remove(key, this);
	}
      else
	{
	  return NULL;
	}
    }
  else if (key > *objectData)
    {
      if (right != NULL)
	{
	  return right->remove(key, this);
	}
      else
	{
	  return NULL;
	}
    }
  else
    {
      if (left != NULL && right != NULL)
	{
	  delete objectData; // Don't let that get away in the next line.
	  objectData  = right->minValue();
	  return right->remove(*objectData, this);
	}
      else if (parent->left == this)
	{
	  parent->left = (left != NULL) ? left : right;
	  return this;
	}
      else if (parent->right == this)
	{
	  parent->right = (left != NULL) ? left : right;
	  return this;
	}
    }
  return this;
}

template<class T>
T* BSTNode<T>::minValue()
{
  if(left == NULL)
    {
      return objectData;
    }
  else
    {
      return left->minValue();
    }
}

#endif
