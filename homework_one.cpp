#include "std_lib_facilities.h"

int main(){
  cout << "double conversions\n";
  double Double = 11.234;
  //double to int
  int Integer = Double;
  cout << Integer << "\n";
  //double to char
  char Character = Double;
  cout << Character << "\n";
  //double to bool
  bool Bool = Double;
  cout << Bool << "\n";

  cout << "integer conversions\n";
  Integer = 2000000;
  //int to char
  Character = Integer;
  cout << Character << "\n";
  //int to bool
  Bool = Integer;
  cout << Bool << "\n";

  cout << "character conversions\n";
  Character = 'd';
  //char to bool
  Bool = Character;
  cout << Bool << "\n";
}
