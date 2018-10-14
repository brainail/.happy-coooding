long long gcd (long long a, long long b, long long & x, long long & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
 
bool solve (long long a, long long b, long long c, long long & x, long long & y, long long & g) {
    if (!a && !b && c) return false;
	g = gcd (a, b, x, y);
	if (c % g != 0) return false;
	x *= c / g, y *= c / g;
	return true;
}

long long minimumNumberOfBoxes(long long a, long long b, long long c) {
    long long x, y, g;
    if (!solve(a, b, c, x, y, g)) {
        return -1;
    }
    if (a > b) {
        swap(a, b);
        swap(x, y);
    }
    long long bg = b / g;
    long long ag = a / g;
    long long k = ceil(-x / (bg + .0));
    x += k * bg;
    y -= k * ag;
    cout << x << " " << y << " " << g << endl;
    if (x < 0 || y < 0) return -1;
    return x + y;
}
