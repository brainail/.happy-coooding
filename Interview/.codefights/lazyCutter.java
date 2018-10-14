int lazyCutter(int n) {
    int max = 1;
    for (int v = 1; v <= n; ++ v) {
        max += v;
    }
    return max; // or just sum progression :) O(1)
}
