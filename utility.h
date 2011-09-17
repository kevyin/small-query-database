/*
 * File: ulitity.h
 * ---------------
 * Defines a convenience function which
 * trims whitespace off the ends of the
 * specified string object.
 */

#ifndef TRIM_H
#define TRIM_H

static void TrimString(string& stringToTrim)
{
  string::const_iterator begin = stringToTrim.begin();
  string::const_iterator front = begin;
  string::const_iterator end = stringToTrim.end();
  string::const_iterator back = end;
  while (front != back && isspace(*front)) front++;
  while (back != front && isspace(*--back)) {}
  
  if (front != back) {
    back++;
    stringToTrim = stringToTrim.substr(front - begin, back - front);
  }
}

#endif
