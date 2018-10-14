# In a given integer array A, we must move every element of A to either list B or list C. (B and C initially start empty.)
# Return true if and only if after such a move, it is possible that the average value of B is equal to the average value of C, and B and C are both non-empty.

# Example:
# Input:
# [1, 2, 3, 4, 5, 6, 7, 8]
# Output: true
# Explanation: We can split the array into[1, 4, 5, 8] and [2, 3, 6, 7], and both of them have the average of 4.5.
class Solution(object):
    def splitArraySameAverage(self, A):
        from fractions import Fraction
        N, S = len(A), sum(A)
        A = [z - Fraction(S, N) for z in A]
        if N == 1:
            return False

        left = {A[0]}
        for i in xrange(1, N/2):
            left = {z + A[i] for z in left} | left | {A[i]}
        if 0 in left:
            return True

        right = {A[-1]}
        for i in xrange(N/2, N-1):
            right = {z + A[i] for z in right} | right | {A[i]}
        if 0 in right:
            return True

        sleft = sum(A[i] for i in xrange(N/2))
        sright = sum(A[i] for i in xrange(N/2, N))
        return any(-ha in right and (ha, -ha) != (sleft, sright) for ha in left)
