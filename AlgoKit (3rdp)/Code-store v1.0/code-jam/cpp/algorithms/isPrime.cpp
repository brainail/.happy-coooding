#include<iostream>

using namespace std;

bool isPrime(int number) {
   if(number == 1 || (number%2 == 0)) return false;
   if(number == 2) return true;
   
   for(int i=3; i*i<=number; i+=2) {
      if(number%i == 0)
         return 0;
   }
   return 1;
}

int main() {
   for(int i=0; i<100; i++) {
      if(isPrime(i)) 
         cout << i << " is Prime" << endl;
   }
   return 0;
}
