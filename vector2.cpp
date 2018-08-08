#include "std_lib_facilities.h"

class vect{
  int sz;
  double* elem;

public:

  vect(int s)
    :sz(s), elem{new double[s]}{
      for(int i = 0; i < s; i++) {elem[i] = 0;}
  }

  vect(const vect& arg)
    :sz(arg.sz), elem{new double[arg.sz]}{
      copy(arg.elem,arg.elem+arg.sz,elem);
  }

  vect& operator=(const vect& a)
  {
    double*p = new double[a.sz];
    copy(a.elem, a.elem+a.sz, p);
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
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

  double operator[](int n){
    return elem[n];
  }

  double operator[](int n) const{
    return elem[n];
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
    cout << v[i] << ", ";
  }
  cout << "\nv2: ";
  for(int i = 0; i < v2.size(); i++){
    cout << v2[i] << ", ";
  }
}

int main(){
  f(3);
}
