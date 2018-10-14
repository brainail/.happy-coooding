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

int main() {
    cout << GCD(10, 20) << endl;
    cout << GCD(12, 57) << endl;
    cout << GCD(13, 20) << endl;
    cout << GCD(1, 20) << endl;
   return 0;
}
