#include "std_lib_facilities.h"

int main(){
  int num_loops = 0;
  while(true){
    double* pd = new double[10000];
    num_loops++;
    cout << num_loops << "\n";
  }
}
