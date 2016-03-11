/*
 * Authors:
 *  Ryan Finn
 *  Braden Edmunds
 *  Abdullah Aldobaie
 *  Nathan Patterson
 *
 * Class URL abstracts the details of working with URLs, allowing other classes
 * to work with URLs in a more general way.
 */

#ifndef URL_H
#define URL_H

#include <string>
using namespace std;

class URL
{
 public:

  /* Constructor for URL.
   * string url // a string representation of a URL.
   */
  URL(string url);

  /* Constructor for URL.
   * string suggestedDomain // a string to specify the domain. If string url already has
   *  a domain, this domain will not replace it.
   * string url             // a string representation of a URL.
   */
  URL(string suggestedDomain, string url);

  /* Destructor for URL.
   */
  ~URL();

  /* Returns an unsigned long representing a hash code unique to this URL.
   */
  unsigned long getHash();

  /* Returns a string representation of a URL object.
   */
  string toString();

  friend ostream& operator<<(ostream &str, const URL &v);

  /* Operator < overload.
   */
  bool operator<(const URL &other) const;

  /* Operator > overload.
   */
  bool operator>(const URL &other) const;

  /* Operator == overload.
   */
  bool operator==(const URL &other) const;

  /* Returns the scheme portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getScheme();

  /* Returns the domain portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getDomain();

  /* Returns the subdomain portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getSubDomain();

  /* Returns the path portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getPath();

  /* Returns the query_string portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getQueryString();

  /* Returns the fragment portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getFragment();

  /* Updates the URL's domain unless the URL already has a domain stored in string url.
   * const string &d  // suggested domain
   */
  void setDomain(const string &d);

  /* Returns a string representing the entire URL.
   */
  string getURL();
  
 private:

  /* Returns an unsigned long representing a hash code unique to the function input.
   * const string &input // The string on which the generated hash code is based.
   */
  unsigned long generateHashCode(const string &input);

  /* Method attempts to return a normalized URL version of the string input.
   * Normalization attempts to reduced the URL to what makes the URL unique.
   * see http://en.wikipedia.org/wiki/URL_normalization
   *
   * string &input // The URL string to be normalized.
   */
  string normalizeURL(const string &input);

  /* Returns the scheme portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getScheme(const string &input);

  /* Returns the domain portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getDomain(const string &input);

  /* Returns the sub domain portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getSubDomain(const string &input);
  
  /* Returns the scheme portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getPath(const string &input);

  /* Retunrs the query_string portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getQueryString(const string &input);

  /* Retunrs the fragment portion of scheme://domain:port/path?query_string#fragment_id
   */
  string getFragment(const string &input);
  
  string        url;         // The URL string represented by this object.
  string        scheme;      // This URL object's scheme portion of the URL.
  string        domain;      // This URL object's domain portion of the URL.
  string        subDomain;   // This URL object's stuff from http://[stuff]domain.com
  string        path;        // This URL object's path portion of the URL.
  string        queryString; // This URL object's query string portion of the URL.
  string        fragment;    // This URL object's fragment portion of the URL.
  unsigned long hashCode;    // This URL object's hash code.

  static const string topLevelDomains[94];
  static const unsigned int topLevelDomainsSize;
};

#endif

