static final int BASE_SHIFT = 10000 + 1;

int n;
int [] f;

void add(int x) {
    while (x < f.length) {
        ++ f [x];
        x = x | (x + 1);
    }
}

int sum(int x) {
    int res = 0;
    while (x > 0) {
        res += f [x];
        x = (x & (x + 1)) - 1;
    }
    return res;
}

int[] countSmallerToTheRight(int[] nums) {
    n = nums.length;
    int [] result = new int [n];
    f = new int [BASE_SHIFT * 2 + 1];
    for (int i = nums.length - 1; i >= 0; -- i) {
        final int x = nums [i] + BASE_SHIFT;
        result [i] = sum(x - 1);
        add(x);
    }
    return result;
}

/*
 Merge sort approach
 
 Node {num, pos, cnt}

int[] countSmallerToTheRight(int[] nums) {
    int n = nums.length;
    for (int i = 0; i < nums.length; i++) node[i] = new Node(nums[i], i);
    mergeSort(node, temp, 0, n - 1);
    int[] result = new int[n];
    for (int i = 0; i < n; i++) result[node[i].ind] = node[i].count;
    return result;
}

void mergeSort(Node[] node, Node[] temp, int lo, int hi) {
    if (lo >= hi) return;
    
    int mid = (lo + hi) / 2;
    mergeSort(node, temp, lo, mid);
    mergeSort(node, temp, mid + 1, hi);
    
    int count = 0;
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid || j <= hi) {
        if (i > mid || (j <= hi && node[i].compareTo(node[j]) > 0)) {
            temp[k++] = node[j++];
            count++;
        } else {
            node[i].count += count;
            temp[k++] = node[i++];
        }
    }
    System.arraycopy(temp, lo, node, lo, hi - lo + 1);
}
 */