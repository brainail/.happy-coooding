int[] sortedSquaredArray(int[] array) {
    int i = -1;
    while (i + 1 < array.length && array [i + 1] < 0) ++ i;
    int q = i + 1;
    int [] result = new int [array.length];
    int k = 0;
    while (i >= 0 || q < array.length) {
        int a = i >= 0 ? array [i] * array [i] : -1;
        int b = q < array.length ? array [q] * array [q] : -1;
        if (a >= 0 && (a < b || b < 0)) {
            -- i;
            result [k ++] = a;
        } else {
            ++ q;
            result [k ++] = b;
        }
    }
    return result;
}
