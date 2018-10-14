#include<iostream>

using namespace std;

int GCD(int x, int y)
{
    while(y>0) {
        x = x%y;
        x^=y^=x^=y;  //swap
    }
    return x;
}

int LCM(int x, int y)
{
   return (x * y)/GCD(x, y);    
}

int main() {
   cout << LCM(8, 16) << endl;
   cout << LCM(3, 7) << endl;
   cout << LCM(100, 200) << endl; 
   return 0;
}
