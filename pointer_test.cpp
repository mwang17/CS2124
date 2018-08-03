#include "std_lib_facilities.h"

int main(){
  char ch = 'a';
  int i = 2;
  double d = 1.2;

  char* chp = &ch;
  int* ip = &i;
  double* dp = &d;

  cout << "character pointer: " << chp;
  cout << "\ndereferenced character pointer: " << *chp;
  cout << "\nsize of pointer: " << sizeof(chp);
  cout << "\nsize of character: " << sizeof(ch);

  cout << "\n\ninteger pointer: " << ip;
  cout << "\ndereferenced integer pointer: " << *ip;
  cout << "\nsize of pointer: " << sizeof(ip);
  cout << "\nsize of integer: " << sizeof(i);

  cout << "\n\ndouble pointer: " << dp;
  cout << "\ndereferenced double pointer: " << *dp;
  cout << "\nsize of pointer: " << sizeof(dp);
  cout << "\nsize of double: " << sizeof(d);
}
