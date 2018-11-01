/**
 * In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: A = [1,0,1,0,1], S = 2 Output: 4 Explanation: The 4 subarrays are
 * bolded below: [1,0,1,0,1] [1,0,1,0,1] [1,0,1,0,1] [1,0,1,0,1]
 * 
 * 
 * Note:
 * 
 * A.length <= 30000 0 <= S <= A.length A[i] is either 0 or 1.
 */

 class Solution {
    public int numSubarraysWithSum(int[] arr, int ta) {
        int n = arr.length, ret = 0;
        for (int le = 0, ri = 0, cta = 0, tz = 0; le < n; ++le, ri = Math.max(ri, le)) {
            while (ri < n && cta + arr[ri] <= ta) {
                cta += arr[ri++];
                if (arr[ri - 1] == 1) tz = 0; else tz += 1;
            }
            if (ri > le) {
                if (cta == ta) ret += tz + Integer.signum(ta);
                cta -= arr[le];
                if (arr[le] == 0 && tz >= ri - le) --tz;
            }
        }
        return ret;
    }
}
