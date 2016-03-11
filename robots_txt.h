/* Authors:
 *  Ryan Finn
 *  Braden Edmunds
 *  Abdullah Aldobaie
 *  Nate Patterson
 *
 * Class Robots_txt stores the contents of a web domain's /robots.txt file.  URL objects
 * can be checked against a Robots_txt object to see if the target domain has disallowed
 * the path of the URL object.
 *
 * It would only make sense to check a URL object against a Robots_txt object if they
 * are of the same domain.
 */

#ifndef ROBOTS_TXT_H
#define ROBOTS_TXT_H

#include <string>
#include <vector>
#include <regex.h>
using namespace std;

#include "url.h"

class Robots_txt
{
 public:

  /* Constructor for Robots_txt.
   */
  Robots_txt(string domain, string txt);

  /* Destructor for Robots_txt.
   */
  ~Robots_txt();

  /* Returns a string representation of Robots_txt.
   */
  string toString();

  /* Returns a boolean representing whether or not a URL is allowed to be used by a
   * web crawler on the domain of this Robot_txt.
   *
   * URL &url  // Reference to a URL that is to be checked for allowed web crawling.
   */
  bool isDisallowed(URL &url);

  friend ostream& operator<<(ostream &str, const Robots_txt &r);

  /* Operator < overload.
   */
  bool operator<(const Robots_txt &other) const;

  /* Operator > overload.
   */
  bool operator>(const Robots_txt &other) const;

  /* Operator == overload.
   */
  bool operator==(const Robots_txt &other) const;

  /* Returns an unsigned long representing a hash code unique to this Robot_txt.
   * Hash is based on Robot_txt.domain.
   */
  unsigned long getHash();

 private:

  /* Mehtod initializes Robots_txt member variables.
   *
   * string parameter           // Parameter from [domain]/robots.txt to focus on. Example: "Disallow"
   * const string &input        // Contents of [domain]/robots.txt
   * vector<string> &stringVec  // Vector to be filled with values from [domain]/robots.txt based on string parameter.
   * vector<regex_t*> &regexVec // Vector to be filled with compiled regular expressions from [domain]/robots.txt base on string prameter.
   */
  void initialize_txt(string parameter, const string &input, vector<string> &stringVec, vector<regex_t*> &regexVec);

  /* Returns an unsigned long representing a hash code unique to the function input.
   * const string &input // The string on which the generated hash code is based.
   */
  unsigned long generateHashCode(const string &input);

  string           domain;        // Stores the domain of [domain]/robots.txt
  unsigned long    hashCode;      // Stores a hash code based on domain.
  vector<string>   disallow;      // Stores Disallow values from [domain]/robots.txt. Currently, only used for toString();
  vector<regex_t*> regexDisallow; // Stores compiled Disallow regular expressions from [domain]/robots.txt.
};

#endif
