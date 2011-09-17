#ifndef DATABASE_H
#define DATABASE_H

#ifdef TEST
#define private public
#endif

//#include <iostream>
//#include <string>
using namespace std;

enum DBSelectOperation { All, Clear, Add, Remove, Refine };
enum DBScope { AllRecords, SelectedRecords};
enum DBQueryOperator { Equal, NotEqual, LessThan, GreaterThan };

template <class value>
class Database {
 public:
  // types

  // constructors
  Database<value>() : nselected(0) {}

  // operations
  inline int numRecords() { return records.size(); }
  inline int numSelected() { return nselected; }
  // destructor

 private:
  // datamembers
  int nselected;
  typename vector< Record<value> > records;



}


#include "database.tem"

#endif
