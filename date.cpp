#include <iostream>

namespace Calendar{
  //default constructor that takes 3 inputs
  Date::Date(int yy, Month mm, int dd)
    : y(yy), m(mm), d(dd)
  {
    if(!is_date(yy, mm, dd)) throw Invalid();
  }

  //default constructor sets the date to Jan 1 2018
  Date::Date()
    :y(default_date().year()),
     m(default_date().month()),
     d(default_date().day())
  {
  }

  Date::Date(const Date& dd)
    :y(dd.year()), m(dd.month()), d(dd.day())
  {
  }
  //returns the number of days in the given month
  int days_in_month(int y, Date::Month m);

  //adds n days to date
  void Date::add_day(int n)
  {
    if(n < 0) error("add_day(): negative n not valid");
    while(days_in_month(y,m)<n+d){
      n = (n+d) - days_in_month(y,m);
      add_month(1);
      d = 0;
    }
    d += n;
  }

  //adds n months to date
  void Date::add_month(int n)
  {
    if(n < 0) error("add_month(): negative n not valid");
    int i = m+1;
    m = Month(i);
  }

  //adds n years to date. If it is Feb 29 and n is not a multiple of 4, it will go to Mar 3.
  void Date::add_year(int n)
  {
    if(m == Feb && d == 29 && !leapyear(y+n)){
      m = Mar;
      d = 1;
    }
    y += n;
  }

  enum Day{
    Sunday, Monday, Teusday, Wednesday, Thursday, Friday, Saturday
  };

  //prints the date in format month day, year instead of the default (YYYY, MM, DD)
  string print_long_date(Date a)
  {
    vector<string> mm {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int month = a.month()-1;
    return mm[month] + " " + to_string(a.day()) + ", " + to_string(a.year());
  }

  //1601.01.01 was a Monday according to the textbook, so we're using that.
  Date first_date(1601, Date::Jan, 1);
  const Day first_day = Monday;

  //again, default date is 2018.01.01
  const Date& default_date()
  {
    static const Date dd(2018, Date::Jan, 1);
    return dd;
  }

  //returns the days in a given month
  int days_in_month(int y, Date::Month m){
    switch (m) {
      case Date::Feb:
        return (leapyear(y))?29:28;
      case Date::Apr :case Date::Jun :case Date::Sep:case Date::Nov:
        return 30;
      default:
        return 31;
    }
  }

  //checks if given date is valid
  bool is_date(int y, Date::Month m, int d)
  {
    if(d<=0) return false;
    if(days_in_month(y, m)<d) return false;
    if(m <= 0) return false;
    if(m > 12) return false;
    return true;
  }

  //checks for leapyears. Returns false if it is a leap year.
  bool leapyear(int y)
  {
    if(y%4)
      return false;
    if(y%100==0 && y%400)
      return false;
    return true;
  }

  //Overloaded equality checking.
  bool operator==(Date& a, Date& b)
  {
    return a.year()==b.year()
        && a.month()==b.month()
        && a.day()==b.day();
  }

  //Overloaded inequality checking.
  bool operator!=( Date& a,  Date& b)
  {
    return !(a==b);
  }

  //overloaded output gives date in format (YYYY, mm, dd)
  ostream& operator<<(ostream& os, const Date& d)
  {
    return os << '(' << d.year() << '/' << d.month() << '/' << d.day() << ')';
  }

  //overloaded input must take the date in format (YYYY, mm, dd)
  istream& operator>>(istream& is, Date& dd)
  {
    int y, m, d;
    char ch1, ch2, ch3, ch4;
    is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
    if(!is) return is;
    if(ch1!= '(' || ch2!= '/' || ch3 != '/' || ch4 != ')'){
      is.clear(ios_base::failbit);
      return is;
    }
    dd = Date(y, Date::Month(m), d);
    return is;
  }
}
