#include "std_lib_facilities.h"
#include <iostream>

using namespace std;

namespace Calendar{
struct Date{
public:
  enum Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
  };

  //invalid class to throw if invalid date is entered
  class Invalid { };

  //default constructors
  Date(int y, Month m, int d);
  Date();

  //data retrieval
  Month month() const{return m;}
  int day() const{return d;}
  int year() const{return y;}

  //modifiers
  void add_day(int n);
  void add_year(int n);
  void add_month(int n);

private:
  int y, d;
  Month m;
};

//checks if date is valid
bool is_date(int y, Date::Month m, int d);

//returns false if the year is a leapyear
bool leapyear(int y);

//equality checking
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

//overloading input/output
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

//default date is Jan 1, 2018
const Date& default_date();
}
