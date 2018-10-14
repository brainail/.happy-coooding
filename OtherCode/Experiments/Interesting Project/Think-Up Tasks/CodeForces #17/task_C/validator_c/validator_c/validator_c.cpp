#include<cassert>
#include<iostream>
#include "testlib.h"
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

int main() {
 registerValidation();
 int n = inf.readInt(1, 150);
 inf.readEoln();
 forr(i,1,n) {
  char ch = inf.readChar();
  ensure((ch == 'a' || ch == 'b' || ch == 'c'));
 }
 inf.readEoln();
 inf.readEof();
}

