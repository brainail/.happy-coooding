// Z-Algo
vector<int> z_function(string s) {
    int n = (int)s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

// Manacher (palindromes) s -> '#' + s[0] + '#' + .. + '#' + S[n] + '#'
int C = 0, R = -1, rad;
for (int i = 0; i < T.length(); ++i) {
    if (i <= R) {
        rad = min(P[2 * C - i], R - i);
    } else {
        rad = 0;
    }
    // Try to extend
    while (i + rad < T.length() && i - rad >= 0 && T[i - rad] == T[i + rad]) {
        rad++;
    }
    P[i] = rad;
    if (i + rad - 1 > R) {
        C = i;
        R = i + rad - 1;
    }
}

// KMP (prefix)
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

// Convex-Hull
vector<point> convexHull(vector<point> p) {
    int n = p.size();
    if (n <= 1)
        return p;
    sort(p.begin(), p.end());
    int cnt = 0;
    vector<point> q(n * 2);
    for (int i = 0; i < n; q[cnt++] = p[i++])
        for (; cnt >= 2 && !cw(q[cnt - 2], q[cnt - 1], p[i]); --cnt)
            ;
    for (int i = n - 2, t = cnt; i >= 0; q[cnt++] = p[i--])
        for (; cnt > t && !cw(q[cnt - 2], q[cnt - 1], p[i]); --cnt)
            ;
    q.resize(cnt - 1 - (q[0] == q[1]));
    return q;
}