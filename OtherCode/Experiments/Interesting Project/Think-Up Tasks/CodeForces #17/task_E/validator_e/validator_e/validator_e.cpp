#include<cassert>
#include<iostream>
#include "testlib.h"
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int main() {
 registerValidation();
 int n = inf.readInt(1, 1000000);
 inf.readEoln();
 forr(i,1,n) {
  char ch = inf.readChar();
  ensure((ch >= 'a' && ch <= 'z'));
 }
 inf.readEoln();
 inf.readEof();
}

