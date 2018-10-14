#include<iostream>
#include<math.h>
#define MAX 1000

using namespace std;

int table[MAX];
int offset;

void generatePrimeTable(int total) {
   bool isPrime;
   int sq, counter;
   offset = counter = 0;
   
   table[offset++] = 2;
   counter++;
   
   for(int i=3;;i+=2) {
      isPrime = true;
      sq = (int)sqrt(i) + 1;
      for(int j=0;j<offset && table[j]<=sq;j++) {
         if(!(i%table[j])) {
            isPrime = false;
			break;
         }	  
      }
      if(isPrime){
         table[offset++] = i;
         counter++;
      }
      if(total==counter) 
         break; 
   }
}

int main() {
   generatePrimeTable(100);
   for(int i=0; i<offset; i++) {
      cout << table[i] << endl;
   } 
   return 0;
}
