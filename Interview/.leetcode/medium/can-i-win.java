/**
 * In the "100 game," two players take turns adding, to a running total, any
 * integer from 1..10. The player who first causes the running total to reach or
 * exceed 100 wins.
 * 
 * What if we change the game so that players cannot re-use integers?
 * 
 * For example, two players might take turns drawing from a common pool of
 * numbers of 1..15 without replacement until they reach a total >= 100.
 * 
 * Given an integer maxChoosableInteger and another integer desiredTotal,
 * determine if the first player to move can force a win, assuming both players
 * play optimally.
 * 
 * You can always assume that maxChoosableInteger will not be larger than 20 and
 * desiredTotal will not be larger than 300.
 */
class Solution {
public:
    bool canIWin(int max, int desired) {
        if (max >= desired) return true;
        if (max * (max + 1) / 2 < desired) return false;
        unordered_map<int, bool> m;
        return canWin(max, desired, 0, m);
    }

    bool canWin(int length, int total, int used, unordered_map<int, bool>& m) {
        if (m.count(used)) return m[used];
        for (int i = 0; i < length; ++i) 
            if (((1 << i) & used) == 0) {
                if (total <= i + 1 || !canWin(length, total - (i + 1), (1 << i) | used, m)) {
                    return (m[used] = true);
                }
            }
        return (m[used] = false);
    }
};


// #region grandy common approach
class Solution {
    int[] stateMemo;

    private int game(int sum, int mask, int max, int desired) {
        if (sum >= desired)
            return 0;
        if (stateMemo[mask] >= 0)
            return stateMemo[mask];
        Set<Integer> states = new HashSet<Integer>();
        for (int i = 1; i <= max; ++i) {
            if (((mask >> (i - 1)) & 1) != 0)
                continue;
            int state = game(sum + i, mask | (1 << (i - 1)), max, desired);
            states.add(state);
        }
        int mex;
        for (mex = 0;; ++mex) {
            if (!states.contains(mex))
                break;
        }
        stateMemo[mask] = mex;
        return mex;
    }

    public boolean canIWin(int max, int desired) {
        if (max >= desired)
            return true;
        if (max * (max + 1) / 2 < desired)
            return false;
        stateMemo = new int[1 << max];
        Arrays.fill(stateMemo, -1);
        int finalState = game(0, 0, max, desired);
        return 0 != finalState;
    }
}
// #endregion
