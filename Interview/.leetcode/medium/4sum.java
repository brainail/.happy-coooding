/**
 * Given an array nums of n integers and an integer target, are there elements
 * a, b, c, and d in nums such that a + b + c + d = target? Find all unique
 * quadruplets in the array which gives the sum of target.
 */
public class Solution {
    public List<List<Integer>> fourSum(int[] a, int target) {
        final LinkedHashSet<List<Integer>> uniqueItems = new LinkedHashSet<>();
        Arrays.sort(a);
        final int n = a.length;

        for (int i = 0; i < n - 3; ++i) {
            for (int t = i + 1; t < n - 2; ++t) {
                int f = t + 1, l = n - 1;
                while (f < l) {
                    final int currentSum = a[i] + a[t] + a[f] + a[l];
                    if (target == currentSum) {
                        uniqueItems.add(Arrays.asList(a[i], a[t], a[f], a[l]));
                        ++f;
                    } else if (currentSum > target) {
                        --l;
                    } else {
                        ++f;
                    }
                }
            }
        }

        return new ArrayList<List<Integer>>(uniqueItems);
    }
}
