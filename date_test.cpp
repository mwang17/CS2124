#include "date.h"
#include "date.cpp"

int main()
{
  try{
    using namespace Calendar;
    cout << "Please enter two dates in format (YYYY/MM/DD): ";
    Date d1;
    cin >> d1;
    Date d2 = d1;
    cout << "The first date is " << d1 << " and the second date is " << d2 << "\n";
    if(d1 == d2) cout << d1 << " is equal to " << d2;
    else cout << d1 << " is not equal to " << d2;
    d1.add_day(30);
    d1.add_month(2);
    d1.add_year(3);
    cout << "\nThe changed date is" << print_long_date(d1);
    if(d1 == d2) cout << d1 << " is equal to " << d2;
    else cout << d1 << " is not equal to " << d2;
  }
  catch(Calendar::Date::Invalid&){
    cerr << "error: invalid date\n";
    return 1;
  }
  catch(runtime_error& e){
    cout << e.what() << "\n";
  }
}
