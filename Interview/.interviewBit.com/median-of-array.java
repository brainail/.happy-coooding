/*
There are two sorted arrays A and B of size m and n respectively.

Find the median of the two sorted arrays ( The median of the array formed by merging both the arrays ).

The overall run time complexity should be O(log (m+n)).

Sample Input

A : [1 4 5]
B : [2 3]

Sample Output

3
 NOTE: IF the number of elements in the merged array is even, then the median is the average of n / 2 th and n/2 + 1th element. 
For example, if the array is [1 2 3 4], the median is (2 + 3) / 2.0 = 2.5 
*/

public class Solution {
    public static double findMedianSortedArraysInternal(final List<Integer> A, final List<Integer> B) {
        int m = A.size(), n = B.size();
        
        int k = (m + n + 1) / 2;
        double v = (double) FindKth(A, 0, m - 1, B, 0, n - 1, k);

        if ((m + n) % 2 == 0) {
            v = (v + (double) FindKth(A, 0, m - 1, B, 0, n - 1, k + 1)) / 2;
        }

        return v;
    }

    public static int FindKth(
        final List<Integer> A, int aStart, int aEnd, 
        final List<Integer> B, int bStart, int bEnd, int k) {
            
        if (aStart > aEnd) return B.get(bStart + k - 1);
        if (bStart > bEnd) return A.get(aStart + k - 1);

        int aMid = (aStart + aEnd) / 2, bMid = (bStart + bEnd) / 2;

        if (A.get(aMid) <= B.get(bMid)) {
            if (k <= (aMid - aStart) + (bMid - bStart) + 1) {
                return FindKth(A, aStart, aEnd, B, bStart, bMid - 1, k);
            } else {
                return FindKth(A, aMid + 1, aEnd, B, bStart, bEnd, k - (aMid - aStart) - 1);
            }
        } else { 
            if (k <= (aMid - aStart) + (bMid - bStart) + 1) {
                return FindKth(A, aStart, aMid - 1, B, bStart, bEnd, k);
            } else {
                return FindKth(A, aStart, aEnd, B, bMid + 1, bEnd, k - (bMid - bStart) - 1);
            }
        }
    }
    
    // DO NOT MODIFY BOTH THE LISTS
    public double findMedianSortedArrays(final List<Integer> A, final List<Integer> B) {
        return findMedianSortedArraysInternal(A, B);
    }
}
