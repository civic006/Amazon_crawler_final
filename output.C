/*
 * output.C
 *
 *  Created on: Feb 15, 2012
 *      Authors:
 *      	- Abdullah Aldobaie
 *      	- Braden Edmunds
 *      	- Nathan Patterson
 *      	- Ryan Finn
 *
 * The definitions of the functions in output.h
 *
 *
 *
 * The HTML file will be formatted as follows:
 * 		- section of authors
 * 		- table of crawling statistics
 * 		- link to list of customers page
 * 		- link to list of products page
 *
 * The recovery file will be formatted as follows:
 * 		- a file with list of Customers:
 * 			+ each line will contain a customer name \n reviews \n pages \n...
 * 		- a file with list of Products:
 * 			+ each line contains a product name \n reviews \n customers \n...
 *
 */


#include "output.h"
#include "global_web_data.h"
#include <sys/stat.h>



/**
 * Prints the results to an HTML files.
 * The files will be in a folder.
 *
 * returns: none
 */
void Output::printResultsToHTML(string domain, string startPage, int threadCount, int missSpelled, int topWords)
{
  this->topWords = topWords; topMisspelledWords = missSpelled;
	//HTML File Name
	struct stat st;
	if(stat("output",&st) != 0)
	{
		system("mkdir output");
	}

	string str = "output/";
	//TODO: append the domain name to the file's name
	string str1 ="index.html";//<< getDomain() << "_Results.html";
	str += str1;

	const char* fileName= (char*) str.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{
		// Get all info from the global data repository:
		int imgsCount = Global_Web_Data::getImageCount();

		Global_Web_Data::getURLs(this->urlsVector);
		Global_Web_Data::getWords(this->wordsVector);
		Global_Web_Data::getMisspelledWords(this->misspelledWordsVector);
		Global_Web_Data::getCustomers(this->customersVector);
		Global_Web_Data::getProducts(this->productsVector);
		webpagesVisitedCount = Global_Web_Data::getDequeueCount();


		int urlsCount = urlsVector.size();
		int wordsCount = wordsVector.size();
		int customersCount =  customersVector.size();
		int productsCount = productsVector.size();
		int uniqueWords = Global_Web_Data::getWordsCount();
		URL url(startPage);
		if(url.getDomain().compare("amazon.com") == 0)
		{
			isAmazon = true;
		}
		else
		{
			isAmazon = false;
		}


		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str() << endl;

		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;


		string link;

		//output the following:


		/*
		 * User instructions to the crawler:
		 */
		myfile << "<h1>Crawling Instructions:</h1>";

		myfile << "<p style=\"font-size:24px;\">"
				<< "Crawl the following webpage:		<FONT COLOR=\"#FF0000\">"
				<< startPage
				<< "</FONT></p>"
				<< endl;

		if(!domain.empty())
		{
			myfile << "<p style=\"font-size:24px;\">"
					<< "With the following domain:		<FONT COLOR=\"#FF0000\">"
					<< domain
					<< "</FONT></p>"
					<< endl;
		}

		myfile << "<p style=\"font-size:24px;\">"
				<< "Using the following number of threads:		<FONT COLOR=\"#FF0000\">"
				<< threadCount
				<< "</FONT></p>"
				<< endl;



		myfile << "<p style=\"font-size:24px;\">"
				<< "Showing the following number of top words:		<FONT COLOR=\"#FF0000\">"
				<< topWords
				<< "</FONT></p>"
				<< endl;




		myfile << "<p style=\"font-size:24px;\">"
				<< "Showing the following number of top misspelled words: <FONT COLOR=\"#FF0000\">"
				<< missSpelled
				<< "</FONT></p>"
				<< endl;



		/*
		 * Crawling results:
		 */
		myfile << "<h1>Crawling Results:</h1>";

		myfile << "<p style=\"font-size:24px;\">"
				<< "Number of extracted urls: 		<FONT COLOR=\"#FF0000\">"
				<< urlsCount
				<< "</FONT></p>"
				<< endl;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Number of web pages crawled:		<FONT COLOR=\"#FF0000\">"
				<< webpagesVisitedCount
				<< "</FONT></p>"
				<< endl;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Number of images found:		<FONT COLOR=\"#FF0000\">"
				<< imgsCount
				<< "</FONT></p>"
				<< endl;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Number of words found:		<FONT COLOR=\"#FF0000\">"
				<< wordsCount
				<< "</FONT></p>"
				<< endl;


		myfile << "<p style=\"font-size:24px;\">"
				<< "Number of unique words found:		<FONT COLOR=\"#FF0000\">"
		                << uniqueWords
				<< "</FONT></p>"
				<< endl;


		if(isAmazon)
		{
			myfile << "<p style=\"font-size:24px;\">"
					<< "Number of products found: 		<FONT COLOR=\"#FF0000\">"
					<< productsCount
					<< "</FONT></p>"
					<< endl;

			myfile << "<p style=\"font-size:24px;\">"
					<< "Number of customers found:		<FONT COLOR=\"#FF0000\">"
					<< customersCount
					<< "</FONT></p>"
					<< endl;
		}

		/*
		 * Crawling statistics:
		 */
		myfile << "<h1>Crawling Statistics:</h1>";

		float tempFloat;

		if( webpagesVisitedCount == 0)
			tempFloat = 0;
		else
			tempFloat = (float) urlsCount / (float) webpagesVisitedCount;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Average number of urls per page is:	<FONT COLOR=\"#FF0000\">"
				<< tempFloat
				<< "</FONT></p>"
				<< endl;

		if( webpagesVisitedCount == 0)
			tempFloat = 0;
		else
			tempFloat = (float) wordsCount / (float) webpagesVisitedCount;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Average number of words per page is:	<FONT COLOR=\"#FF0000\">"
				<< tempFloat
				<< "</FONT></p>"
				<< endl;

		vector<Word*> misspelledVector;
		Global_Web_Data::getMisspelledWords(misspelledVector);
		if( webpagesVisitedCount == 0)
			tempFloat = 0;
		else
		  tempFloat = (float) misspelledVector.size() / (float) webpagesVisitedCount;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Average number of misspelled words per page is:	<FONT COLOR=\"#FF0000\">"
				<< tempFloat
				<< "</FONT></p>"
				<< endl;


		if( webpagesVisitedCount == 0)
			tempFloat = 0;
		else
			tempFloat = (float) imgsCount / (float) webpagesVisitedCount;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Average number of images per page is:	<FONT COLOR=\"#FF0000\">"
				<< tempFloat
				<< "</FONT></p>"
				<< endl;


		if( imgsCount == 0)
			tempFloat = 0;
		else
			tempFloat = (float) wordsCount / (float) imgsCount;

		myfile << "<p style=\"font-size:24px;\">"
				<< "Average number of words per image is:	<FONT COLOR=\"#FF0000\">"
				<< tempFloat
				<< "</FONT></p>"
				<< endl;

		//TODO: avg misspelled words / pg.

		if(isAmazon)
		{
			if( webpagesVisitedCount == 0)
				tempFloat = 0;
			else
				tempFloat = (float) customersCount / (float) webpagesVisitedCount;

			myfile << "<p style=\"font-size:24px;\">"
					<< "Average number of customers per page is:	<FONT COLOR=\"#FF0000\">"
					<< tempFloat
					<< "</FONT></p>"
					<< endl;


			if( customersCount == 0)
				tempFloat = 0;
			else
				tempFloat = (float) wordsCount / (float) customersCount;
			myfile << "<p style=\"font-size:24px;\">"
					<< "Average number of words per customers is:	<FONT COLOR=\"#FF0000\">"
					<< tempFloat
					<< "</FONT></p>"
					<< endl;


			if( customersCount == 0)
				tempFloat = 0;
			else
			  tempFloat = (float) misspelledVector.size() / (float) customersCount;
			myfile << "<p style=\"font-size:24px;\">"
					<< "Average number of misspelled words per customers is:	<FONT COLOR=\"#FF0000\">"
					<< tempFloat
					<< "</FONT></p>"
					<< endl;

			//TODO: avg misspelled words / customer.


			// Link to list of customers:
			myfile << "<h1>List of Customers:</h1>" << endl;
			myfile << "<p style=\"font-size:24px;\">"
					<< "Go to: "
					<< createListOfCustomers()
					<< "</p>"
					<< endl;


			// Link to list of products:
			myfile << "<h1>List of Products:</h1>" << endl;
			myfile << "<p style=\"font-size:24px;\">"
					<< "Go to: "
					<< createListOfProducts()
					<< "</p>"
					<< endl;
		} // if amazon.com only


		// Link to list of products:
		myfile << "<h1>List of Top Words:</h1>" << endl;
		myfile << "<p style=\"font-size:24px;\">"
				<< "Go to: "
				<< createListOfTopWords()
				<< "</p>"
				<< endl;

		// Link to list of products:
			myfile << "<h1>List of Top Misspelled Words:</h1>" << endl;
			myfile << "<p style=\"font-size:24px;\">"
					<< "Go to: "
					<< createListOfTopMisspelledWords()
					<< "</p>"
					<< endl;

		// Link to list of words (words corpus):
		myfile << "<h1>List of Words:</h1>" << endl;
		myfile << "<p style=\"font-size:24px;\">"
				<< "Go to: " << endl
				<< createWordCorpusPage()
				<< "</p>"
				<< endl;


		// End of HTML file
		myfile << "<br><br><br><br><br><br><br>"
				<<"</body></html>" << endl;

		//close file
		myfile.close();

	}
	else cout << "Unable to open file";
}



/**
 * Creates top words page to be linked from main page.
 *
 * Parameters: none
 *
 * Returns: string: a link to the words page.
 */
string Output::createListOfTopWords()
{

	Word_Count histogram;

	for(unsigned int i=0; i < wordsVector.size(); i++)
	{
		Word *word = new Word( *wordsVector.at(i));
		histogram.add_word(word);

	}
	vector<Word*> topWordsList;

	topWordsList = histogram.get_top_words(topWords);




	string file = "output/topWords.html";

	const char* fileName= (char*) file.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{
		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		myfile << "<h1>Top " << topWords << " Words</h1>";


		vector<vector<string> > tempTableContent;

		vector<string> firstRow;
		firstRow.push_back("#");

		firstRow.push_back("Word");

		firstRow.push_back("Count");

		firstRow.push_back("Percentage");

		tempTableContent.push_back(firstRow);


		for(unsigned int i=0; i < topWordsList.size(); i++)
		{
			stringstream intStr;
			vector<string> row;


			intStr << i+1;
			row.push_back(intStr.str());
			intStr.str("");

			row.push_back(topWordsList.at(i)->getWordValue());

			intStr << topWordsList.at(i)->getWordCount();
			row.push_back(intStr.str());
			intStr.str("");

			float percentage = (topWordsList.at(i)->getWordCount()*100.0/Global_Web_Data::getWordsCount());

			intStr << "<TABLE><TR><TD bgcolor=darkred>";

			intStr << "<div style=\"width:" << percentage *2
					<< ";height:14px;border:1px solid #000;background-color:#F00;\"></div>";

			intStr <<"</TD>"
					<< "<TD><FONT SIZE=3>"
					<< percentage << "%"
					<< "</FONT></TD></TR>"
					<< "</TABLE>";

			row.push_back(intStr.str());
			intStr.str("");


			tempTableContent.push_back(row);
		}

		myfile << createHTMLTable(tempTableContent) << endl;


		myfile << "</body></html>";


		myfile.close();

	}
	else cout << "Unable to open Top Words page file!" << endl;;


	return createHTMLLink("topWords.html", "Top Words List");
}


/**
 * Creates top words page to be linked from main page.
 *
 * Parameters: none
 *
 * Returns: string: a link to the words page.
 */
string Output::createListOfTopMisspelledWords()
{
        
	Word_Count histogram;
	
	for(unsigned int i=0; i < misspelledWordsVector.size(); i++)
	{
		Word *word = new Word( *misspelledWordsVector.at(i));
		histogram.add_word(word);

	}
	vector<Word*> topWordsList;

	topWordsList = histogram.get_top_words(topMisspelledWords);




	string file = "output/topMisspelledWords.html";

	const char* fileName= (char*) file.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{
		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		myfile << "<h1>Top " << topWords << " Misspelled Words</h1>";


		vector<vector<string> > tempTableContent;

		vector<string> firstRow;
		firstRow.push_back("#");

		firstRow.push_back("Word");

		firstRow.push_back("Count");

		firstRow.push_back("Percentage");

		tempTableContent.push_back(firstRow);


		for(unsigned int i=0; i < topWordsList.size(); i++)
		{
			stringstream intStr;
			vector<string> row;


			intStr << i+1;
			row.push_back(intStr.str());
			intStr.str("");

			row.push_back(topWordsList.at(i)->getWordValue());

			intStr << topWordsList.at(i)->getWordCount();
			row.push_back(intStr.str());
			intStr.str("");

			float percentage = (topWordsList.at(i)->getWordCount()*100.0/Global_Web_Data::getWordsCount());

			intStr << "<TABLE><TR><TD bgcolor=darkred>";

			intStr << "<div style=\"width:" << percentage *2
					<< ";height:14px;border:1px solid #000;background-color:#F00;\"></div>";

			intStr <<"</TD>"
					<< "<TD><FONT SIZE=3>"
					<< percentage << "%"
					<< "</FONT></TD></TR>"
					<< "</TABLE>";

			row.push_back(intStr.str());
			intStr.str("");


			tempTableContent.push_back(row);
		}

		myfile << createHTMLTable(tempTableContent) << endl;


		myfile << "</body></html>";


		myfile.close();

	}
	else cout << "Unable to open Top Words page file!" << endl;;


	return createHTMLLink("topMisspelledWords.html", "Top Misspelled Words List");
}


/**
 * Creates words corpus page to be linked from main page.
 *
 * Parameters: none
 *
 * Returns: string: a link to the words page.
 */
string Output::createWordCorpusPage()
{
	string str1 = "";
	unsigned int pagesInterval = 1000;

	//HTML File Name
	struct stat st;
	if(stat("output/wordCorpus",&st) != 0)
	{
		system("mkdir output/wordCorpus");
	}

	str1 = "output/wordCorpus/";

	string wordsLinks;
	for(unsigned int pages=0; pages < wordsVector.size(); pages+=1000)
	{
		stringstream intStr;

		if(pages+1000 > wordsVector.size())
			pagesInterval = wordsVector.size() - pages;


		intStr << "Words"
				<< pages+1
				<< "_"
				<< pages+pagesInterval
				<< ".html";

		string link = "wordCorpus/" + intStr.str();
		string file = str1 + intStr.str();
		intStr.str("");

		const char* fileName= (char*) file.c_str();

		ofstream myfile(fileName); // Create an HTML file.

		if (myfile.is_open())
		{
			//Start HTML File
			myfile << "<html>" << endl;

			//HTML file header:
			myfile << (char*)createHTMLHeader().c_str() << endl;

			//HTML file BODY
			myfile << "<body>" << endl;

			//Output the creators of this projects' names:
			myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

			myfile << "<h1>list of words:</h1>";

			if(wordsVector.size() < 1)
			{
				myfile << "<p> Unfortunately the crawler didn't result to any words. Try again!</p>";
			}
			else
			{
				myfile << "<p> Click on the word to google its meaning.</p>";

				vector<vector<string> > tempTableContent;

				vector<string> firstRow;
				firstRow.push_back("#");

				firstRow.push_back("Word");

				firstRow.push_back("Count");

				firstRow.push_back("Percentage");

				tempTableContent.push_back(firstRow);


				for(unsigned int i=pages; i< pages+1000 && i < wordsVector.size(); i++)
				{
					stringstream intStr;
					vector<string> row;


					intStr << i+1;
					row.push_back(intStr.str());
					intStr.str("");

					string word = wordsVector.at(i)->getStrippedWordValue();
					if(word.empty())
					{
						continue;
					}
					row.push_back(createHTMLLink("https://www.google.com/search?q=meaning of " + word , word));

					intStr << wordsVector.at(i)->getWordCount();
					row.push_back(intStr.str());
					intStr.str("");

					float  percentage = (wordsVector.at(i)->getWordCount()*100.0/Global_Web_Data::getWordsCount());

					intStr << "<TABLE><TR><TD bgcolor=darkred>";

					intStr << "<div style=\"width:" << percentage *2
							<< ";height:14px;border:1px solid #000;background-color:#F00;\"></div>";

					intStr <<"</TD>"
							<< "<TD><FONT SIZE=3>"
							<< percentage << "%"
							<< "</FONT></TD></TR>"
							<< "</TABLE>";

					row.push_back(intStr.str());
					intStr.str("");

					tempTableContent.push_back(row);
				}

				myfile << createHTMLTable(tempTableContent) << endl;

			}
			// End of HTML file
			myfile << "</body></html>" << endl;

			//close file
			myfile.close();
		} else cout << "Unable to open word corpus file";

		intStr << "Words List "
				<< pages+1
				<< "_"
				<< pages+pagesInterval;
		wordsLinks += createHTMLLink(link, intStr.str()) + "<br>";
	}


	return wordsLinks;
}



/**
 * Creates an HTML page that contains a list of customers.
 *
 * Parameters: a list of customers
 *
 * Returns: string: link to the the list of customers page
 */
string Output::createListOfCustomers()
{
	string str= "output/List_of_Customers.html";

	const char* fileName= (char*) str.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{

		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		//TODO: if there are customers!...
		myfile << "<h1>List of Customers:</h1>";

		if(customersVector.size() < 1)
		{
			myfile << "<p> Unfortunately the crawler didn't result to any customers. Try again!</p>";
		}
		else
		{
			myfile << "<p> Click on the customer's name to get more details.</p>";

			vector<vector<string> > tempTableContent;

			vector<string> firstRow;
			firstRow.push_back("#");

			firstRow.push_back("Customer Name");

			firstRow.push_back("Number of Reviews");

			firstRow.push_back("Percentage of Reviews");

			tempTableContent.push_back(firstRow);


			for(unsigned int i=0; i < customersVector.size(); i++)
			{
				stringstream intStr;
				vector<string> row;


				intStr << i+1;
				row.push_back(intStr.str());
				intStr.str("");

				//Creats a customer page and return a link with the name of the customer.
				row.push_back(createCustomerPage(customersVector.at(i)));

				intStr << customersVector.at(i)->getComments().size();
				row.push_back(intStr.str());
				intStr.str("");

				float percentage = (customersVector.at(i)->getComments().size()*100.0/customersVector.size());

				intStr << "<TABLE><TR><TD bgcolor=darkred>";

				intStr << "<div style=\"width:" << percentage *2
						<< ";height:14px;border:1px solid #000;background-color:#F00;\"></div>";

				intStr <<"</TD>"
						<< "<TD><FONT SIZE=3>"
						<< percentage << "%"
						<< "</FONT></TD></TR>"
						<< "</TABLE>";

				row.push_back(intStr.str());
				intStr.str("");

				tempTableContent.push_back(row);
			}

			myfile << createHTMLTable(tempTableContent) << endl;

		}
		// End of HTML file
		myfile << "</body></html>";


		myfile.close();

	}
	else cout << "Unable to open customer list file!" << endl;

	return createHTMLLink("List_of_Customers.html", "Customers List");
}



/**
 * Creates a customer page to be linked from main page.
 *
 * Parameters: a customer
 *
 * Returns: string: a link to the customer page.
 */
string Output::createCustomerPage(Customer *c)
{
	//HTML File Name
	struct stat st;
	if(stat("output/customersList",&st) != 0)
	{
		system("mkdir output/customersList");
	}

	Word name(c->getName());
	string customerName = name.getStrippedWordValue()
																																									;
	string file = "output/";

	string link = "customersList/";
	link += customerName;
	link +=".html";

	file += link;

	const char* fileName= (char*) file.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{
		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		myfile << "<h1>" << customerName << "'s Info</h1>";


		myfile << "<p>Name: " << customerName << "</p>";
		myfile << "<p>From: " << c->getLocation() << "</p>";
		myfile << "<p>Average ratings: " << c->getAverageRate() << "</p>";
		myfile << "<p>Number of reviews: " << c->getComments().size() << "</p>";
		myfile << "<h1>" << customerName << "'s Comments</h1>";

		vector<vector<string> > tempTableContent;

		vector<string> firstRow;
		firstRow.push_back("#");

		firstRow.push_back("Product's Name");

		firstRow.push_back( customerName +"'s Comment");

		firstRow.push_back("Creation Date");

		firstRow.push_back("Given Rate");

		firstRow.push_back("Number of Words");

		firstRow.push_back("Misspelled Words");

		firstRow.push_back("Number of Misspelled Words");

		tempTableContent.push_back(firstRow);


		for(unsigned int i=0; i < c->getComments().size(); i++)
		{
			stringstream intStr;
			vector<string> row;


			intStr << i+1;
			row.push_back(intStr.str());
			intStr.str("");

			row.push_back(c->getComments().at(i).getProduct());

			row.push_back(c->getComments().at(i).getComment());

			row.push_back(c->getComments().at(i).getDate());

			intStr << c->getComments().at(i).getRate();
			row.push_back(intStr.str());
			intStr.str("");

			intStr << c->getComments().at(i).misspelled->size() + c->getComments().at(i).correct->size();
			row.push_back(intStr.str());
			intStr.str("");

			for(unsigned int j=0; j < c->getComments().at(i).getMisspelledWords()->size(); j++)
			  { if(!c->getComments().at(i).getMisspelledWords()->at(j)->toString().empty()) {
			      intStr << c->getComments().at(i).getMisspelledWords()->at(j)->toString() << "<FONT COLOR=\"#FF0000\"> | </FONT>";
			    }}
			row.push_back(intStr.str());
			intStr.str("");

			intStr << c->getComments().at(i).getMisspelledWords()->size();
			row.push_back(intStr.str());
			intStr.str("");

			//				row.push_back(intStr.str());
			//				intStr.str("");

			tempTableContent.push_back(row);
		}

		myfile << createHTMLTable(tempTableContent) << endl;


		//		}


		// End of HTML file
		myfile << "</body></html>";


		myfile.close();

	}
	else cout << "Unable to open customer page file!" << endl;;


	return createHTMLLink(link, name.getWordValue());
}



/**
 * Creates an HTML page that contains a list of productss.
 *
 * Parameters: a list of products
 *
 * Returns: string: link to the the list of products page
 */
string Output::createListOfProducts()
{
	string str= "output/List_of_Products.html";

	const char* fileName= (char*) str.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	{

		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		//TODO: if there are products!...
		myfile << "<h1>List of Products:</h1>";

		vector<vector<string> > tempTableContent;

		vector<string> firstRow;
		firstRow.push_back("#");

		firstRow.push_back("Product Name");

		firstRow.push_back("Number of Reviews");

		firstRow.push_back("Percentage of Reviews");

		tempTableContent.push_back(firstRow);


		for(unsigned int i=0; i < productsVector.size(); i++)
		{
			Word name(productsVector.at(i)->getProductName());
			if(name.getStrippedWordValue().empty())
			{
				continue;
			}
			stringstream intStr;
			vector<string> row;


			intStr << i+1;
			row.push_back(intStr.str());
			intStr.str("");

			//Creats a customer page and return a link with the name of the customer.
			row.push_back(createProductPage(productsVector.at(i)));

			intStr << productsVector.at(i)->getCustomers().size();
			row.push_back(intStr.str());
			intStr.str("");

			float  percentage = (productsVector.at(i)->getCustomers().size()*100.0/customersVector.size());

			intStr << "<TABLE><TR><TD bgcolor=darkred>";

			intStr << "<div style=\"width:" << percentage *2
					<< ";height:14px;border:1px solid #000;background-color:#F00;\"></div>";

			intStr <<"</TD>"
					<< "<TD><FONT SIZE=3>"
					<< percentage << "%"
					<< "</FONT></TD></TR>"
					<< "</TABLE>";

			row.push_back(intStr.str());
			intStr.str("");

			tempTableContent.push_back(row);
		}

		myfile << createHTMLTable(tempTableContent) << endl;

		// End of HTML file
		myfile << "</body></html>";


		myfile.close();

	}
	else cout << "Unable to open product List file!" << endl;

	return createHTMLLink("List_of_Products.html", "Products List");
}



/**
 * Creates a product page to be linked from the main page.
 *
 * Parameters: a product\
 *
 * Returns: string: a link to the product page.
 */
string Output::createProductPage(Product *p)
{
	//HTML File Name
	struct stat st;
	if(stat("output/productsList",&st) != 0)
	{
		system("mkdir output/productsList");
	}

	Word name(p->getProductName());
	string productName = name.getStrippedWordValue();
	string file = "output/";

	string link = "productsList/";
	link += productName;
	link +=".html";

	file += link;

	const char* fileName= (char*) file.c_str();

	ofstream myfile(fileName); // Create an HTML file.

	if (myfile.is_open())
	  {cout<< "INSIDE PRODUCT PAGE..." <<endl;
		//Start HTML File
		myfile << "<html>" << endl;

		//HTML file header:
		myfile << (char*)createHTMLHeader().c_str();


		//HTML file BODY
		myfile << "<body>" << endl;

		//Output the creators of this projects' names:
		myfile <<(char*)createHTMLTitle( "CS3505: WEB CRAWLER RESULTS:", true).c_str() << endl;

		//TODO: if there are customers!...
		myfile << "<h1>" << productName << "'s Info</h1>";

		// myfile << "<p> Click on the customer's name to get more details.</p>";

		myfile << "<p>Name: " << productName << "</p>";
		int productRate =0; unsigned int i;
		for(i= 0; i < p->getCustomers().size(); i++)
		{
		  productRate +=  p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getRate();
		}
		//TODO: Add product rating:
		myfile << "<p>Average ratings: " << productRate/(i+1) << "</p>";

		myfile << "<p>Number of reviews: " << p->getCustomers().size() << "</p>";
		myfile << "<h1>" << productName << "'s Comments</h1>";

		vector<vector<string> > tempTableContent;

		vector<string> firstRow;
		firstRow.push_back("#");

		firstRow.push_back("Customer's Name");

		firstRow.push_back("Comment");

		firstRow.push_back("Creation Date");

		firstRow.push_back("Given Rate");

		firstRow.push_back("Number of Words");

		firstRow.push_back("Misspelled Words");

		firstRow.push_back("Number of Misspelled Words");

		tempTableContent.push_back(firstRow);


		for(unsigned int i=0; i < p->getCustomers().size(); i++)
		  {cout << "INSIDE SECOND FOR LOOOP IN PRODUCT PAGE>>>"<< endl;
			stringstream intStr;
			vector<string> row;


			intStr << i+1;
			row.push_back(intStr.str());
			intStr.str("");
			cout<<"name..";
			row.push_back(p->getCustomers().at(i)->getName());
			cout << ", comment";
			//TODO: get customer's comment for this product
			row.push_back(p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getComment());


			row.push_back(p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getDate());
			cout << ", rate";
			intStr << p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getRate();
			row.push_back(intStr.str());
			/*
	    		intStr <<  p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).misspelled->size() +  p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).correct->size();
			row.push_back(intStr.str());
			intStr.str("");
			cout << ", before third loop ";
			for(unsigned int j=0; j < p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getMisspelledWords()->size() ; j++)
			  {cout << "INSIDE THIRD FOR LOOP..."<<endl;
			  if(!p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getMisspelledWords()->at(j)->toString().empty())
			  intStr << p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).getMisspelledWords()->at(j)->toString()
				 << "<FONT COLOR=\"#FF0000\"> | </FONT>";
			}
			row.push_back(intStr.str());
			intStr.str("");

			row.push_back(""+  p->getCustomers().at(i)->getCommentByProduct(p->getProductName()).misspelled->size() );
			*/


			tempTableContent.push_back(row);
		}

		myfile << createHTMLTable(tempTableContent) << endl;



		// End of HTML file
		myfile << "</body></html>";

		myfile.close();
	}
	else cout << "Unable to open product page file: " << productName << endl;

	return createHTMLLink(link, name.getWordValue());
}



/**
 * Creates an HTML type header.
 *
 * Parameters: None.
 *
 * Returns: a string of the HTML header code.
 */
string Output::createHTMLHeader()
{
	string HEADER;

	//HTML file header:
	HEADER = "<head><style type=\"text/css\">";
	HEADER += "body {background-color: #FFCC66;";
	HEADER += "font-family: arial, verdana, sans-serif;";
	HEADER += "font-size: 110%;}";
	HEADER += "h1 {color: #990000;background-color: #FC9804; ";
	HEADER += "font-family: \"Times New Roman\", serif;}";
	HEADER += "h3 {color: #008000; font-family: \"Times New Roman\", serif;";
	HEADER += "font-style: italic;}";
	HEADER += "TH {border-bottom-color: black; border-bottom-width: 2px; color: #000080; font-family:arial, verdana, sans-serif; max-width: 300px; overflow: hidden; word-wrap: break-word;";
	HEADER += "font-size: 140%;}";
	HEADER += "TD {font-family: arial, verdana, sans-serif;vertical-align:top; max-width: 400px; overflow: hidden; word-wrap: break-word;}";
	HEADER += "font-size: 140%;}";
	HEADER += "</style></head>";

	return HEADER;
}



/**
 * Creates an HTML type title.
 *
 * Parameters: None.
 *
 * Returns: a string of the HTML title code.
 */
string Output::createHTMLTitle(string title, bool addAuthors)
{
	string TITLE =  "<title>";
	TITLE += title;
	TITLE += "</title>";

	if(addAuthors)
	{
		TITLE += "<h1>This file was created by:</h1>";
		TITLE += "<h3>Abdullah Aldobaie</h3>";
		TITLE += "<h3>Braden Edmunds</h3>";
		TITLE += "<h3>Nathan Patterson</h3>";
		TITLE += "<h3>Ryan Finn</h3>";
	}

	return TITLE ;
}



/**
 * Creates an HTML type link.
 *
 * Parameters: None.
 *
 * Returns: a string of the HTML link code appended with the given text.
 */
string Output::createHTMLLink(string link, string text="")
{
	string LINK;
	if(link.empty())
		return "";
	LINK = "<a href=\"";
	LINK += link + "\">";
	LINK += "<pr style=\"font-size:24px;\">";
	LINK += text;
	LINK += "</pr></a>";

	return LINK;
}



/**
 * Creates an HTML type table. The width of the table is the size of the first
 * row in rowsContent. The height of the table is the size of the rows. the
 * content of each row is the content of each inner vector of rowsContent.
 *
 * Parameters: vector<vector<string> > rowsContent: the table content in rows of columns.
 *
 * Returns: a string of the HTML table code.
 */
string Output::createHTMLTable(vector<vector<string> > &tableContent)
{
	// if table is empty or only contains header, ignore it and return an empty string.
	if(tableContent.size() <= 1)
	{
		return "";
	}


	// Start the table
	string TABLE ="<table BORDER=0 CELLSPACING=5 CELLPADDING=0 width= 100%>" ;


	//Table header
	TABLE += "<TR bgcolor=lightgrey>";
	for(unsigned col= 0; col < tableContent.at(0).size(); col++)
	{
		TABLE += "<TH align=center>";
		TABLE += tableContent.at(0).at(col);
		TABLE += "</TH>";
	}
	TABLE +="</TR>";


	//Table Content
	for(unsigned int row= 1; row < tableContent.size(); row++)
	{
		TABLE += "<TR>";

		for(unsigned col= 0; col < tableContent.at(row).size(); col++)
		{
			TABLE += "<TD>";
			TABLE += tableContent.at(row).at(col);
			TABLE += "</TD>";
		}

		TABLE +="</TR>";
	}

	// End the table
	TABLE += "</table>";

	return TABLE;
}
