int Solution::lis(const vector<int> &A) {
    int INF = 1000000000;
    int n = A.size();
    vector<int> d(n + 1, INF);
    vector<int> f(n + 1, 0);
    d [0] = -INF;
    int rtv = 0;

    for (int i = 0; i < n; ++ i) {
        int j = upper_bound (d.begin(), d.end(), A [i]) - d.begin();
        if (d [j - 1] < A [i] && A [i] < d [j]) {
            d [j] = A [i];
            f [j] = f [j - 1] + 1;
            rtv = f [j] > rtv ? f [j] : rtv;
        }
    }
    
    return rtv;
}
