int missingNumber(int[] a) {
        int n = a.length;
        int res = 0;  
        for (int i = 0; i < n; i++) res = res ^ a[i];                 
        for (int i = 0; i <= n; i++) res = res ^ i;                  
        return res;
}
