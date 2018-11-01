/**
 * The set [1,2,3,...,n] contains a total of n! unique permutations.
 * 
 * By listing and labeling all of the permutations in order, we get the
 * following sequence for n = 3:
 * 
 * "123" "132" "213" "231" "312" "321" Given n and k, return the kth permutation
 * sequence.
 * 
 * Note:
 * 
 * Given n will be between 1 and 9 inclusive. Given k will be between 1 and n!
 * inclusive. Example 1:
 * 
 * Input: n = 3, k = 3 Output: "213" Example 2:
 * 
 * Input: n = 4, k = 9 Output: "2314"
 */

// #1
class Solution {
    public String getPermutation(int n, int k) {
        List<Integer> nums = new ArrayList<>();
        for (int i = 1; i <= n; i++) nums.add(i);
        int total = 1;
        for (int i = 1; i < n; i++) total *= i;
        StringBuilder sb = new StringBuilder();
        while (n > 1) {
            int idx = (k - 1) / total;
            sb.append(nums.get(idx));
            nums.remove(idx);
            k -= idx * total;
            total /= --n;
        }
        sb.append(nums.get(0));
        return sb.toString();
    }
}

 // #2
class Solution {
    public String getPermutation(int n, int k) {
        int count = 0;
        StringBuilder ret = new StringBuilder(n);
        boolean[] used = new boolean[n + 1];
        int[] f = new int[11];
        f[0] = 1;
        for (int i = 1; i <= 10; ++i)
            f[i] = f[i - 1] * i;
        for (int i = 0; i < n; ++i) {
            int before = 0;
            int candidate = -1;
            int candidateCount = -1;
            for (int j = 1; j <= n; ++j)
                if (!used[j]) {
                    int countIfUse = f[n - i - 1] * before;
                    if (count + countIfUse < k) {
                        candidate = j;
                        candidateCount = countIfUse;
                    }
                    ++before;
                }
            count += candidateCount;
            used[candidate] = true;
            ret.append(candidate);
        }
        return ret.toString();
    }
}
