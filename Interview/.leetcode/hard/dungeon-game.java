/**
 * The demons had captured the princess (P) and imprisoned her in the
 * bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid
 * out in a 2D grid. Our valiant knight (K) was initially positioned in the
 * top-left room and must fight his way through the dungeon to rescue the
 * princess.
 * 
 * The knight has an initial health point represented by a positive integer. If
 * at any point his health point drops to 0 or below, he dies immediately.
 * 
 * Some of the rooms are guarded by demons, so the knight loses health (negative
 * integers) upon entering these rooms; other rooms are either empty (0's) or
 * contain magic orbs that increase the knight's health (positive integers).
 * 
 * In order to reach the princess as quickly as possible, the knight decides to
 * move only rightward or downward in each step.
 * 
 * 
 * 
 * Write a function to determine the knight's minimum initial health so that he
 * is able to rescue the princess.
 * 
 * For example, given the dungeon below, the initial health of the knight must
 * be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
 * 
 * -2 (K) -3 3 
 * -5 -10 1 
 * 10 30 -5 (P)
 */
public class Solution {
    public int calculateMinimumHP(int[][] damage) {
		int m = damage.length;
		int n = m == 0 ? 0 : damage[0].length;
		int[][] dp = new int[m + 1][n + 1];

		for (int i = 0; i < m + 1; i++) dp[i][n] = Integer.MAX_VALUE;
		for (int j = 0; j < n + 1; j++) dp[m][j] = Integer.MAX_VALUE;
		dp[m][n - 1] = dp[m - 1][n] = 0;
		
        for (int i = m - 1; i >= 0; i--) {
			for (int j = n - 1; j >= 0; j--) {
				dp[i][j] = Math.max(Math.min(dp[i + 1][j], dp[i][j + 1]) - damage[i][j], 0);
			}
		}

		return dp[0][0] + 1;
    }
}