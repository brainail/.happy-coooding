/**
 * Given a positive 32-bit integer n, you need to find the smallest 32-bit
 * integer which has exactly the same digits existing in the integer n and is
 * greater in value than n. If no such positive 32-bit integer exists, you need
 * to return -1.
 * 
 * Example 1:
 * 
 * Input: 12 Output: 21
 * 
 * 
 * Example 2:
 * 
 * Input: 21 Output: -1
 */

class Solution {
    public int nextGreaterElement(int n) {
        List<Integer> num = new ArrayList<>();
        while (n > 0) {
            num.add(n % 10);
            n /= 10;
        }
        if (num.isEmpty())
            num.add(0);
        Collections.reverse(num);
        int downIndex = num.size() - 2;
        while (downIndex >= 0 && num.get(downIndex) >= num.get(downIndex + 1))
            --downIndex;
        if (downIndex < 0)
            return -1;
        for (int i = num.size() - 1;; --i)
            if (num.get(i) > num.get(downIndex)) {
                swap(num, i, downIndex);
                break;
            }
        for (int i = downIndex + 1, j = num.size() - 1; i < j; ++i, --j) {
            swap(num, i, j);
        }
        long ret = 0;
        for (Integer x : num)
            ret = ret * 10 + x;
        return ret > Integer.MAX_VALUE ? -1 : (int) ret;
    }

    private void swap(List<Integer> items, int i, int j) {
        Integer buff = items.get(i);
        items.set(i, items.get(j));
        items.set(j, buff);
    }
}
