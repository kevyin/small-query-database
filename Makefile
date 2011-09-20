## There are 2 separate targets in this makefile.
## "readtest" compiles the simple record reading code
## "database" compiles all the database program modules
##
## If you just say "make" it makes the database.  If you want to build
## the readtest, you need to do it explicitly.  The readtest is just
## there to show that the reading code works, you can compile it
## with the fraction class and the STL string to make sure that
## everything behaves on your platform.
##

CPPFLAGS = -Wall -Werror -O2
# enable this for debugging
#CPPFLAGS = -Wall -g
#CXX = g++-4.3
CXX = g++
# enable this on Mac OS X
#CXX = g++-4.2

LDFLAGS =
READTEST_SRCS = readrecord.cpp fraction.cpp
DB_SRCS = fraction.cpp interactive.cpp

READTEST_OBJS = $(READTEST_SRCS:.cpp=.o)
DB_OBJS = $(DB_SRCS:.cpp=.o)

PROGS = database readtest testrec

default : database

readtest : $(READTEST_OBJS)
	$(CXX) -o $@ $(READTEST_OBJS)  $(LDFLAGS)


database : $(DB_OBJS)
	$(CXX) -o $@ $(DB_OBJS) $(LDFLAGS)

# The dependencies below make use of make's default rules,
# under which a .o automatically depends on its .c and
# the action taken uses the $(CXX) and $(CFLAGS) variables.
# These lines describe a few extra dependencies involved.

depend:: Makefile.dependencies $(DB_SRCS) $(HDRS)

Makefile.dependencies:: $(DB_SRCS) $(READTEST_SRCS) $(HDRS)
	$(CXX) $(CPPFLAGS) -MM $(DB_SRCS) $(READTEST_SRCS) > Makefile.dependencies

-include Makefile.dependencies

testrec: record.h record.tem testrecord.cpp
	$(CXX) $(CPPFLAGS) -DTEST -lboost_unit_test_framework -o testrec record.h fraction.cpp testrecord.cpp

testdb: record.h record.tem database.h database.tem testdatabase.cpp
	$(CXX) $(CPPFLAGS) -DTEST -lboost_unit_test_framework -o testdb record.h database.h testdatabase.cpp

clean : 
	rm -f *.o a.out core $(PROGS) Makefile.dependencies
