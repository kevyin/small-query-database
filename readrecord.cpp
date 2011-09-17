#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

#include "fraction.h"
#include "utility.h"

template<class Value> 
void ReadRecords(const char *filename, Value& val)
{ 
  ifstream in(filename);
  assert(in);
  
  while (in.good() && in.peek() != EOF)
    ReadOneRecord(in, val);
  cout << "All done!" << endl;
}

int main()
{
  cout << "What type values would you like to read in the database?\n";
  cout << "(1 = integer, 2 = string, 3 = Fraction): ";
  int choice;
  cin >> choice;
  switch (choice) {
  case 1: { 
    int i;
    ReadRecords("db_int", i);
    break; 
  }
  case 2: { 
    string s;
    ReadRecords("db_string",s);
    break; 
  }
  case 3: { 
    Fraction f;
    ReadRecords("db_fract", f);
    break; 
  }
  default:
    cout << "Invalid choice, exiting.\n";
  }
  
  return 0;
}

inline void ReadFieldname(istream& in, string& fieldname)
{
  getline(in, fieldname, '=');
  TrimString(fieldname);
}

template <class value>
inline void ReadValue(istream& in, value& val)
{
  in >> val;
}

template <>
inline void ReadValue<string>(istream& in, string& val)
{
  getline(in, val, '\n');
  TrimString(val);
}

template<class value> 
void ReadOneRecord(istream& in, value& val)

{
  if (in.peek() != '{') { 		// bail if not at record start
    in.setstate(ios::failbit);  	// set stream failure, so we can detect it
    return; 
  }
  
  in.ignore(1024, '\n');
  while (true) {
    string line;
    getline(in, line, '\n');
    istringstream istr(line.c_str());
    if (istr.peek() == '}') break;
    std::pair<string, value> entry;
    ReadFieldname(istr, entry.first);
    ReadValue(istr, entry.second);
    cout << "pair<attribute : value> = <" << entry.first << " : " 
	 << entry.second << ">" << endl;
  }
}

