#ifndef DATABASE_H
#define DATABASE_H

#ifdef TEST
#define private public
#endif

//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;

#include "record.h"

//enum DBSelectOperation { All, Clear, Add, Remove, Refine };
//enum DBScope { AllRecords, SelectedRecords};
//enum DBQueryOperator { Equal, NotEqual, LessThan, GreaterThan };

template <class value>
class Database {
 private:
  // types
  typedef vector< Record<value> > records_type;
  // datamembers
  int nselected;
  records_type records;

 public:
  // types
  typedef typename records_type::iterator iterator;
  typedef typename records_type::const_iterator const_iterator;

  // constructors
  Database<value>() : nselected(0) { records = vector< Record<value> >(); }

  // operations
  inline int numRecords() { return records.size(); }
  inline int numSelected() { return nselected; }
  void write(ostream& out, DBScope scope) const;
  void read(istream& in);
  void deleteRecords(DBScope scope);
  void selectAll();
  void deselectAll();
  void select(DBSelectOperation selOp, const string& attr,
              DBQueryOperator op, const value& val);

  // destructor
  ~Database() {} // use default destructors



};


#include "database.tem"

#endif
