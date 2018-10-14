/**
 * BigMod.cpp - Calculate the remainder or modulus of a big number b^p using 
 *				a divide and conquer approach based on the formula: 
 *
 *				(A*B*C) mod n = (A mod n) * (B mod n) * (C mod n).
 */
#include<math.h>
#include<iostream>

using namespace std; 

long square(long n) 
{
   return n*n;
}

long bigMod(long b, long p, long m) {
	if(p == 0)
		return 1;
	else if(p%2 == 0)
		return square(bigMod(b, p/2, m)) %m;
	else
		return ((b%m) * bigMod(b, p-1, m)) % m; 
	
}

int main() {
	long b, p, m; 
	
	b = 3; 
	p = 18132; 
	m = 17; 
	cout << bigMod(b, p, m) << endl; 
	
	b = 17; 
	p = 1765; 
	m = 3;
	cout << bigMod(b, p, m) << endl; 

	b = 2374859; 
	p = 3029382; 
	m = 36123; 
	cout << bigMod(b, p, m) << endl; 
}

