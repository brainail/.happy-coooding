class WireComparator implements Comparator<int []> {
    @Override
    public int compare(int [] a, int [] b) {
        return Integer.compare(a [2], b [2]);        
    }
}

private static final Random RANDOM = new Random();
int n;
int p [];

int findComp(int x) {
    return x == p[x] ? x : (p [x] = findComp(p [x]));
}

void joinComp(int cx, int cy) {
    if (RANDOM.nextBoolean()) {
        int tmp = cx;
        cx = cy;
        cy = tmp;
    }
    p [cy] = cx;
}

int networkWires(int nw, int[][] wires) {
    Arrays.sort(wires, new WireComparator());
    n = nw;
    p = new int [n];
    for (int i = 0; i < n; ++ i) p [i] = i;
    int result = 0;
    for (int i = 0; i < wires.length; ++ i) {
        int ca = findComp(wires [i][0]);
        int cb = findComp(wires [i][1]);
        if (ca != cb) {
            result += wires [i][2];
            joinComp(ca, cb);
        }
    }
    return result;
}
