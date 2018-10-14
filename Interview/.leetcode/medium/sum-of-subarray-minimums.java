/**
 * Given an array of integers A, find the sum of min(B), where B ranges over
 * every (contiguous) subarray of A.
 * 
 * Since the answer may be large, return the answer modulo 10^9 + 7.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: [3,1,2,4] Output: 17 Explanation: Subarrays are [3], [1], [2], [4],
 * [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. Minimums are 3, 1, 2, 4, 1,
 * 1, 2, 1, 1, 1. Sum is 17.
 * 
 * 
 * Note:
 * 
 * 1 <= A.length <= 30000 1 <= A[i] <= 30000
 * 
 */
class Solution {
    public int sumSubarrayMins(int[] A) {
        Stack<Integer> stack = new Stack<>();
        int n = A.length, res = 0, mod = (int) 1e9 + 7, j, k;
        for (int i = 0; i <= n; i++) {
            while (!stack.isEmpty() && A[stack.peek()] > (i == n ? 0 : A[i])) {
                j = stack.pop();
                k = stack.isEmpty() ? -1 : stack.peek();
                res = (res + A[j] * (i - j) * (j - k)) % mod;
            }
            stack.push(i);
        }
        return res;
    }
}

/**
 * class Solution {
    int M=(int)1e9+7;
    public int sumSubarrayMins(int[] A) {
        Stack<Integer> stack= new Stack<>();
        stack.add(-1);
        int[][] area= new int[A.length][2];
        for (int i=0; i<A.length; i++){
            while (stack.peek()!=-1 && A[i]<A[stack.peek()]) stack.pop();
            area[i][0]=stack.peek()+1;
            stack.add(i);
        }
        stack.clear();
        stack.add(A.length);
        for (int i=A.length-1; i>-1; i--){
            while (stack.peek()!=A.length && A[i]<=A[stack.peek()]) stack.pop();
            area[i][1]=stack.peek()-1;
            stack.add(i);
        }
        long res=0;
        for (int i=0; i<A.length; i++){
            int lo=area[i][0], hi=area[i][1];
            res=(res+((hi-i+1)*(i-lo+1))*A[i])%M;
        }
        return (int)res%M;
    }
}
 */