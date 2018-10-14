#include<cassert>
#include<iostream>
#include "testlib.h"
using namespace std;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)

vector<int> q;

int main() {
 registerValidation();
 int n = inf.readInt(1, 1000);
 inf.readEoln();
 q.resize(n+1);
 forr(i,1,n) {
  q[i] = inf.readInt(0, 1000000); 
  if(i < n) inf.readSpace();
 }
 inf.readEoln();
 int m = inf.readInt(0, 10000);
 inf.readEoln();
 forr(i,0,m-1) {
  int A = inf.readInt(1, n);
  inf.readSpace();
  int B = inf.readInt(1, n);
  inf.readSpace();
  inf.readInt(0, 1000000);
  inf.readEoln();
  ensure(q[A] > q[B]);
 }
 inf.readEof();
}

