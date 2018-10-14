static final int MODULO = (int) 1e9 + 7;

int [] count = new int [2002];
int res = 0;

void inc(int i) {
    while (i - 1 <= 2000) { count [i] = (count [i] + 1) % MODULO; i = i | (i + 1); }
}

void inv(int i) {
    while (i > 0) { res = (res + count [i]) % MODULO; i = (i & (i + 1)) - 1; }
}

int countInversions(int[] a) {
    for (int i = a.length - 1; i >= 0; -- i) {
        inv(a [i] + 1000); 
        inc(a [i] + 1000 + 1);
    }
    return res;
}
