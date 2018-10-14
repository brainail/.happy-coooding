#include<iostream>
#include<vector>
using namespace std;

/**
 * 判斷a是不是質數
 */
bool isprime(int a)
{
    if(a == 2) return true; // 2 is prime

    if(a % 2 == 0) return false; // but 2's times is not prime

    for(int i = 3; i * i <= a; i += 2)
        if(a % i == 0) return false;

    return true;
}

/**
 * 列出a所有的質因數
 */
vector<int> primefactors(int a)
{
    vector<int> primefactors;

    for(int i = 1; i <= a; i++)
        if(a % i == 0 && isprime(i)) {
            primefactors.push_back(i);

            while(a % i != 0) a = a / i;
        }

    return primefactors;
}

int main()
{
    int a = 5, b = 2500;

    for(int b = 0; b < 100; ++b)
        if(isprime(b)) cout << b << " is  prime." << endl;

    vector <int> p = primefactors(17 * 19);

    for(int i = 0; i < p.size(); ++i)
        cout << p[i] << endl;

    return 0;
}
