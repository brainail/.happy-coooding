/**
 * You are given two integer arrays nums1 and nums2 sorted in ascending order
 * and an integer k.
 * 
 * Define a pair (u,v) which consists of one element from the first array and
 * one element from the second array.
 * 
 * Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.
 * 
 * Example 1:
 * 
 * Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3 Output: [[1,2],[1,4],[1,6]]
 * Explanation: The first 3 pairs are returned from the sequence:
 * [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6] Example 2:
 * 
 * Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2 Output: [1,1],[1,1]
 * Explanation: The first 2 pairs are returned from the sequence:
 * [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3] Example 3:
 * 
 * Input: nums1 = [1,2], nums2 = [3], k = 3 Output: [1,3],[2,3] Explanation: All
 * possible pairs are returned from the sequence: [1,3],[2,3]
 */

class Solution {
    public List<int[]> kSmallestPairs(int[] nums1, int[] nums2, int k) { // multiple-merge sort of columns
        PriorityQueue<int[]> q = new PriorityQueue<>((a, b) -> (a[0] + a[1]) - (b[0] + b[1])); // sorted by pair sum
        List<int[]> res = new ArrayList();
        int N1 = nums1.length, N2 = nums2.length;
        if (N1 == 0 || N2 == 0) return res; // early exit, no pairs to form
        for (int i = 0; i < Math.min(N1, k); i++) q.offer(new int[] { nums1[i], nums2[0], 0 }); // {num1, num2, num2idx}
        for (int i = 0; i < Math.min(N1 * N2, k); i++) {
            int[] cur = q.poll(); // best current pair
            res.add(new int[] { cur[0], cur[1] }); // form item result
            if (cur[2] < N2 - 1) q.offer(new int[] { cur[0], nums2[cur[2] + 1], cur[2] + 1 }); // column has next item
        }
        return res;
    }
}
