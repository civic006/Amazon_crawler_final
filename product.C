/*
 * product.C
 *
 *  Created on: Feb 14, 2012
 *       Author:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 */

#include "product.h"


/*
 * Constructor for a product object, takes a name and a URL.
 */
Product::Product(string name, URL* url)
  : productName(name),
    url(url),
    hashCode(generateHashCode(productName))
{
}
/*
 * This method returns the hashcode based on the product name.
 */
unsigned long Product::getHash()
{
  return hashCode;
}
/*
 * This method retuns the list of customers that the product contains.
 */
vector<Customer*> Product::getCustomers()
{
	return this->customers;
}
/*
 * This method retuns the product name.
 */
string Product::getProductName()
{
	return this->productName;
}
/*
 * This method adds customers to the product list of customers.
 */
bool Product::addCustomer(Customer* customer)
{
	bool added = true;
	//int i = std::find(customers.begin(), customers.end(), customer)!=customers.end();
	int i = 0; // TODO: std::find(string, start, end)

	if(i == 0)
		customers.push_back(customer);
	else
		added = false;

	return added;
}
/**
 * Product decronstructor.
 */
Product::~Product() {

}
/*
 * Operator overload <
 */
bool Product::operator<(const Product &other) const
{
  return hashCode < other.hashCode;
}
/*
 * Operator overload >
 */
bool Product::operator>(const Product &other) const
{
  return hashCode > other.hashCode;
}
/*
 * Operator overload ==
 */
bool Product::operator==(const Product &other) const
{
  return hashCode == other.hashCode;
}

// String folding at 4 bytes at a time.
unsigned long Product::generateHashCode(const string &input)
{
  int intLength = input.size() / 4;
  long sum = 0;
  
  for(int i = 0; i < intLength; i++)
    {
      int startIndex = i * 4;
      int endIndex = (i * 4) + 4;
      long multiplyer = 1;
      
      for(int j = startIndex; j < endIndex; j++)
	{
	  sum += input.at(j) * multiplyer;
	  multiplyer *= 256;
	}
    }
  
  int startIndex = intLength * 4;
  int endIndex = input.size();
  long multiplyer = 1;
  
  for(int i = startIndex; i < endIndex; i++)
    {
      sum += input.at(i) * multiplyer;
      multiplyer *= 256;
    }
  
  if(sum < 0)
    {
      sum *= -1;
    }
  
  return sum;
}
