/**
 * Given a non-empty array of unique positive integers A, consider the following graph:

There are A.length nodes, labelled A[0] to A[A.length - 1];
There is an edge between A[i] and A[j] if and only if A[i] and A[j] share a common factor greater than 1.
Return the size of the largest connected component in the graph.

Example 1:

Input: [4,6,15,35]
Output: 4

Example 2:

Input: [20,50,9,63]
Output: 2

Example 3:

Input: [2,3,6,7,4,12,21,39]
Output: 8

Note:

1 <= A.length <= 20000
1 <= A[i] <= 100000
 */
class Solution {
    int parent[121000], size[121000];

public:
    int largestComponentSize(vector<int>& A) {
        for (int i = 0; i < 121000; i++) parent[i] = i;
        memset(size, 0, sizeof(size));

        for (int i = 0; i < A.size(); i++) {
            size[100001 + i] = 1;
            for (int p = 2; p*p <= A[i]; p++) {
                if (A[i] % p == 0) {
                    merge(p, 100001+i);
                    merge(A[i]/p, 100001+i);
                }
            }
            merge(A[i], 100001+i);
        }

        int max_cc = 1;
        for (int i = 0; i < A.size(); i++)
            max_cc = max(max_cc, size[find(100001+i)]);
        return max_cc;
    }

    int find(int i) {
        if (parent[i] != i) parent[i] = find(parent[i]);
        return parent[i];
    }

    void merge(int i, int j) {
        i = find(i);
        j = find(j);
        if (i == j) return;
        size[i] += size[j];
        parent[j] = i;
    }
};