/*
 *   Created on: Feb 14, 2012
 *      Author: Braden Edmunds
 *      		Ryan Finn
 *      		Nathan Patterson
 *      		Abdullah Aldobaie
 */

#ifndef PRODUCT_H_
#define PRODUCT_H_
#include "Customer.h"
#include "url.h"
#include <string.h>
#include <vector>

using namespace std;


class Product{
public:
	//The name of the product, URL to the product page
	Product(string name, URL* url);

	/*
	 * This method adds a customer to a given product.
	 */
	bool addCustomer(Customer* customer);

	/*
	 * This method returns all customers contained within this product.
	 */
	vector<Customer*> getCustomers();

	/*
	 * This method retuns the product name as a string.
	 */
	string getProductName();

	/*
	 * This method gets the hash code for the product name
	 */
	unsigned long getHash();
	virtual ~Product();

	/* Operator < overload.
	 */
	bool operator<(const Product &other) const;
	
	/* Operator > overload.
	 */
	bool operator>(const Product &other) const;
	
	/* Operator == overload.
	 */
	bool operator==(const Product &other) const;
	
	
 private:
	//List of customers
	vector<Customer*> customers;
	//product name
	string productName;
	//url of the product page
	URL* url;
	//customer count
	int customerCount;
	//hash code of product
	unsigned long hashCode;
	
	/* Returns an unsigned long representing a hash code unique to the function input.
	 * const string &input // The string on which the generated hash code is based.
	 */
	unsigned long generateHashCode(const string &input);
};

 /* namespace std */
#endif /* PRODUCT_H_ */
