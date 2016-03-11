/*
 * recovery.C
 *
 *  Created on: Feb 16, 2012
 *      Author:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 *
 * A class that recover last session info that was written in a customerList.txt and
 * a productList.txt files.
 *
 * The recovery file must be written in the following format:
 * 		- a file with list of Customers:
 * 			+ each line will contain a customer name | reviews | pages |...
 * 		- a file with list of Products:
 * 			+ each line contains a product name \n reviews \n customers \n...
 * 		- a file with list of urls to visit:
 * 			+ each line contains a url
 * 		- a file with list of visited urls:
 * 			+ each line contains a visited url
 *
 */

#include "recovery.h"



#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "textFileReader.h"
/* hash.C
 *
 * Abdullah Aldobaie
 * Braden Edmunds
 * Nathan Patterson
 * Ryan Finn
 *
 * Jan. 24, 2012
 *
 *
 * The definitions of the functions in hash.h
 */
Recovery::Recovery()
{

}

Recovery::~Recovery()
{

}

void Recovery::recoverGlobalWebData()
{
	readRecoveryFile("customerList.txt");

	readRecoveryFile("productList.txt");

	readRecoveryFile("urlsList.txt");

	readRecoveryFile("visitedUrlsList.txt");

}

void Recovery::readRecoveryFile(string filePathAndName)
{
	string fileLine;
	ifstream infile;
	infile.open(filePathAndName.c_str());

	while(getline(infile, fileLine)) // read in file lines
	{
		fileLines.push_back(fileLine);
	}

	infile.close();
}



vector<string> Recovery::getSplitByTap(vector<string> &fileLines)
{
	vector<string> returnVector;
	size_t startIndex = 0;
	size_t endIndex = 0;

	for(unsigned int i = 0; i < fileLines.size(); i++)
	{
		startIndex = 0;
		endIndex = 0;

		while(endIndex != string::npos)
		{
			endIndex = fileLines[i].find("\t", startIndex);

			if(endIndex == string::npos)
			{
				returnVector.push_back(fileLines[i].substr(startIndex, fileLines[i].size()));
			}
			else
			{
				returnVector.push_back(fileLines[i].substr(startIndex, endIndex - startIndex));
			}

			startIndex = endIndex + 1;
		}
	}

	return returnVector;
}

/* Returns a vector<string> representing contents of the text file(s) inputs after
 * having been split by spaces.
 */
//vector<string> Recovery::getSplitByTap(vector<string> &fileLines);



void Recovery::creatCustomer(string line)
{

}

void Recovery::createProduct(string line)
{

}

void Recovery::createUrl(string line)
{

}



