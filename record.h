#ifndef RECORD_H
#define RECORD_H

#ifdef TEST
#define private public
#endif

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#include "utility.h"

/* Database enums
 * --------------
 * Ideally, these enums would be declared inside the scope of
 * the Database class, but it turns out gcc doesn't not handle
 * nested enums inside a template class very well, so you will 
 * want to define that at the top-level scope as a workaround.
 */
 
enum DBSelectOperation { All, Clear, Add, Remove, Refine };
enum DBScope { AllRecords, SelectedRecords};
enum DBQueryOperator { Equal, NotEqual, LessThan, GreaterThan };


// Need to add declarations for operator<< and operator >> here
template <class value> class Record;
template <class value> ostream& operator<<(ostream& out, const Record<value>& r);
template <class value> istream& operator>>(istream& in, Record<value>& r);


template <class value>
class Record {
 public:
  // types
  typedef multimap<string, value> entry_type;
  typedef typename entry_type::iterator iterator;
  typedef typename entry_type::const_iterator const_iterator;

  // constructors
  Record<value>() : selected(false) { entries = multimap<string, value>(); } 

  // operations
  inline bool isSelected() const { return selected; }
  inline void setSelected(bool val) { selected = val; }
  bool matchesQuery(const string& attr, DBQueryOperator op,
                    const value& want) const;

  // operators
  friend ostream& operator<<<value>(ostream& out, const Record<value>& r);
  friend istream& operator>><value>(istream& in, Record<value>& r);

  // destructor
  ~Record() {}; // use default destructors
 
 private:
  // datamembers
  bool selected;
  entry_type entries;
  
};

#include "record.tem"

#endif
