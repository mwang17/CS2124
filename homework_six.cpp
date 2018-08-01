#include "std_lib_facilities.h"

int main(){
  cout << "Please enter input file name: ";
  string iname, oname;
  cin >> iname;
  cout << "Please enter output file name: ";
  cin >> oname;
  int integer;
  double first_double;
  double second_double;
  char comma;
  ifstream ist {iname};
  if(!ist) error("Can't open input file ", iname);
  ofstream ost {oname};
  if(!ost) error("can't open output file ", oname);

  while(ist >> integer >> comma >> first_double >> comma >> second_double){
    ost << integer << "\t" << first_double << "\t" << second_double << "\n";
  }
}
