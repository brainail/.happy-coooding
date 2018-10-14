#include<iostream>

using namespace std;

int fastest_exponentiation(int base, int exponent) {
   int half;
   if(exponent == 0)
      return 1;
   else if(exponent % 2 == 0) {
      half = fastest_exponentiation(base, exponent/2);
      return half*half;
   }
   else {
      half = fastest_exponentiation(base, exponent-1);
      return base * half;   
   }
}

int main() {
   cout << fastest_exponentiation(3, 2) << endl; 
   cout << fastest_exponentiation(30, 5) << endl;
   cout << fastest_exponentiation(2, 5) << endl;
   return 0;
}
