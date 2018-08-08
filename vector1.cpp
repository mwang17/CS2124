#include "std_lib_facilities.h"

class vect{
  int sz;
  double* elem;

public:

  vect(int s)
    :sz(s), elem{new double[s]}{
     for(int i = 0; i < s; i++) {elem[i] = 0;}
  }

  ~vect(){
    delete[] elem;
  }

  int size() const{
    return sz;
  }

  double get(int n) const{
    return elem[n];
  }

  void set(int n, double v){
    elem[n] = v;
  }

};

void f(int n){
  vect v(n);
  v.set(2, 2.2);
  vect v2 = v;
  v.set(0, 88);
  v.set(1, 99);
  v2.set(0, 8);
  v2.set(1, 9);
  cout << "v1: ";
  for(int i = 0; i < v.size(); i++){
    cout << v.get(i) << ", ";
  }
  cout << "\nv2: ";
  for(int i = 0; i < v2.size(); i++){
    cout << v2.get(i) << ", ";
  }
}


int main(){
  f(3);
}
