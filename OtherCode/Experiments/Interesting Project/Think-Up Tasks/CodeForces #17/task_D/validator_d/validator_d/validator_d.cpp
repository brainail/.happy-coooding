#include<cassert>
#include<iostream>
#include "testlib.h"
using namespace std;

int main() {
 registerValidation();
 string A = inf.readToken("[0-9]{1,1000000}");
 ensure(((A.length() > 1 && A[0] != '0') || (A.length() == 1 && A[0] > '1')));
 inf.readSpace();
 string B = inf.readToken("[0-9]{1,1000000}");
 ensure(((B.length() > 1 && B[0] != '0') || (B.length() == 1 && B[0] > '0')));
 inf.readSpace();
 int C = inf.readInt(1, 1000000000);
 inf.readEoln();
 inf.readEof(); 
}

