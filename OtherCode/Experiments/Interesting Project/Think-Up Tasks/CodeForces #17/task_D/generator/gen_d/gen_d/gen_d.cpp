#include "testlib.h"
#include <iostream>
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int main(int argc, char* argv[]) {
 registerGen(argc, argv);
 int left = atoi(argv[1]);
 int right = atoi(argv[2]);
 int lenA = rnd.next(left, right);
 int lenB = rnd.next(left, right);
 if(argv[3][0] == '3') {
  forr(i,1,1000000) printf("9");
  printf(" ");
  forr(i,1,1000000) printf("9");
  printf(" ");
  printf("1000000000");
  printf("\n");
  return 0;
 }
 printf("%d",rnd.next(2, 9));
 forr(i,1,lenA-1) printf("%d",rnd.next(0, 9));
 printf(" ");
 
 printf("%d",rnd.next(1, 9));
 forr(i,1,lenB-1) printf("%d",rnd.next(0, 9));
 printf(" ");
  
 if(argv[3][0] == '0') 
  printf("%d",rnd.next(1, 99)); else
 if(argv[3][0] == '1') 
  printf("%d",rnd.next(100, 1000)); else
  printf("%d",rnd.next(999950000, 1000000000));
 printf("\n"); 
 return 0;
}
