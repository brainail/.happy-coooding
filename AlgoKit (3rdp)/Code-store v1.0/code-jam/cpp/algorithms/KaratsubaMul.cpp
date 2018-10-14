#include <iostream>
#include <math.h>
using namespace std;
typedef long long ll;
ll power(ll x, ll y)
{
    if(y == 0)
        return (1);
    else if(y == 1)
        return(x);
    else
        return(x * power(x, y - 1));
}
ll digits(ll n, ll &dig)
{
    if(n < 10)
		return (dig + 1);
    else
	{
        dig++;
        return(digits(n / 10, dig));
    }
}
ll last(ll digits, ll &number)  { return number % power(10, digits); }
ll first(ll digits, ll &number) { return number / power(10, digits); }
ll multiply(ll &u, ll &v)
{
    ll dig1 = 0, dig2 = 0;
    ll numDigits = max(digits(u, dig1), digits(v, dig2));
    if(numDigits <= 1) return u * v;
    numDigits = (numDigits / 2) + (numDigits % 2);
    ll w = first(numDigits, u), x = last(numDigits, u);
    ll y = first(numDigits, v), z = last(numDigits, v);
    ll p = multiply(w, y), q = multiply(x, z);
    ll wPlusx = w + x, zPlusy = z + y;
    ll r = multiply(wPlusx, zPlusy);
    return power(10, 2*numDigits)*p + power(10, numDigits)*(r-p-q) + q;
}
int main()
{
	ll num1 = 1234, num2 = 5678;
	printf("%lld * %lld = %lld\n", num1, num2, multiply(num1,num2));
    return EXIT_SUCCESS;
}
