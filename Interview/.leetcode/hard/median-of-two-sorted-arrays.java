/**
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * 
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 * 
 * You may assume nums1 and nums2 cannot be both empty.
 * 
 * Example 1:
 * 
 * nums1 = [1, 3] nums2 = [2]
 * 
 * The median is 2.0 Example 2:
 * 
 * nums1 = [1, 2] nums2 = [3, 4]
 * 
 * The median is (2 + 3)/2 = 2.5
 */
class Solution {
    public int findMedian(int k, int[] a, int la, int ra, int[] b, int lb, int rb) {
        if (la > ra)
            return b[lb + k - 1];
        if (lb > rb)
            return a[la + k - 1];

        int ma = (la + ra) / 2;
        int mb = (lb + rb) / 2;
        int pivotK = ma - la + mb - lb + 1;

        if (a[ma] <= b[mb]) {
            return k <= pivotK ? findMedian(k, a, la, ra, b, lb, mb - 1)
                    : findMedian(k - (ma - la + 1), a, ma + 1, ra, b, lb, rb);
        } else {
            return k <= pivotK ? findMedian(k, a, la, ma - 1, b, lb, rb)
                    : findMedian(k - (mb - lb + 1), a, la, ra, b, mb + 1, rb);
        }
    }

    public double findMedianSortedArrays(int[] a, int[] b) {
        int n = a.length;
        int m = b.length;

        double median = (double) findMedian((n + m + 1) / 2, a, 0, n - 1, b, 0, m - 1);
        if ((n + m) % 2 == 0) {
            double median2 = (double) findMedian((n + m + 2) / 2, a, 0, n - 1, b, 0, m - 1);
            median = (median + median2) / 2;
        }

        return median;
    }
}
