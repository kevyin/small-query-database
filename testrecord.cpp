#include "record.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE const_string test
#include <boost/test/unit_test.hpp>



#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
using namespace std;

#include "utility.h"
#include "fraction.h"


template<class Value> 
void ReadRecords(const char *filename, Value& val)
{ 
  ifstream in(filename);
  assert(in);
  
  while (in.good() && in.peek() != EOF)
    ReadOneRecord(in, val);
  cout << "All done!" << endl;
}

BOOST_AUTO_TEST_CASE( constructors ) {
    cout << "Constructors" << endl;

    Record<int> rec; 
    BOOST_CHECK(rec.isSelected() == false);
    BOOST_CHECK(rec.entries.empty());

    Record<int> rec2 = Record<int>(); 
    BOOST_CHECK(rec2.isSelected() == false);

    rec2.setSelected(false);
    BOOST_CHECK(rec2.isSelected() == false);
    rec2.setSelected(true);
    BOOST_CHECK(rec2.isSelected() == true);

    cout << "finished Constructors" << endl;
} 

BOOST_AUTO_TEST_CASE( operatorinInt ) {
    cout << "operator>> and << int" << endl;
    Record<int> rec; 
    ifstream in("db_int");
    assert(in);
    in >> rec;
    cout << rec << endl;
}

BOOST_AUTO_TEST_CASE( operatorinstring) {
    cout << "operator>> and << string" << endl;
    Record<string> rec; 
    ifstream in("db_string");
    assert(in);
    in >> rec;
    cout << rec << endl;
}

BOOST_AUTO_TEST_CASE( operatorinfract ) {
    cout << "operator>> and << fract" << endl;
    Record<Fraction> rec; 
    ifstream in("db_fract");
    assert(in);
    in >> rec;
    cout << rec << endl;
}
BOOST_AUTO_TEST_CASE( test_matchesquery ) {
    cout << "test_matchesQuery" << endl;

    Record<int> rec; 
    cout << "stream in db_int" << endl;
    ifstream in("db_int");
    cout << "assering db_int" << endl;
    assert(in);
    cout << "reading in record" << endl;
    in >> rec;
    cout << "finished reading in record" << endl;

    BOOST_CHECK_EQUAL(rec.matchesQuery("part number", Equal, 16485), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("part number", Equal, 4599957), false);
    BOOST_CHECK_EQUAL(rec.matchesQuery("part number", NotEqual, 14256485), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("part number", LessThan, 14256485), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("part number", GreaterThan, 43), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("retail cost", GreaterThan, 43), false);
    BOOST_CHECK_EQUAL(rec.matchesQuery("number in stock", GreaterThan, 5), true);

    BOOST_CHECK_EQUAL(rec.matchesQuery("*", GreaterThan, 5), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("*", GreaterThan, 43), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("*", GreaterThan, 99999993), false);
    BOOST_CHECK_EQUAL(rec.matchesQuery("*", LessThan, 999993), true);
    BOOST_CHECK_EQUAL(rec.matchesQuery("*", LessThan, 3), false);
}

//int main()
//{
  //cout << "What type values would you like to read in the database?\n";
  //cout << "(1 = integer, 2 = string, 3 = Fraction): ";
  //int choice;
  //cin >> choice;
  //switch (choice) {
  //case 1: { 
    //int i;
    //ReadRecords("db_int", i);
    //break; 
  //}
  //case 2: { 
    //string s;
    //ReadRecords("db_string",s);
    //break; 
  //}
  ////case 3: { 
    ////Fraction f;
    ////ReadRecords("db_fract", f);
    ////break; 
  ////}
  //default:
    //cout << "Invalid choice, exiting.\n";
  //}
  
  //return 0;
//}

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


