long long gcdex (long long a, long long b, long long & x, long long & y) {
	if (a == 0) {
		x = 0, y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcdex (b%a, a, x1, y1);
	x = y1 - (b / a) * x1, y = x1;
	return d;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = gcdex (a, m, x, y);
    if (g != 1)
	    return -1;
    else {
	    return (x % m + m) % m;
    }
}
