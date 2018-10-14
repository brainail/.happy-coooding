/**
 * We have a grid of 1s and 0s; the 1s in a cell represent bricks. A brick will
 * not drop if and only if it is directly connected to the top of the grid, or
 * at least one of its (4-way) adjacent bricks will not drop.
 * 
 * We will do some erasures sequentially. Each time we want to do the erasure at
 * the location (i, j), the brick (if it exists) on that location will
 * disappear, and then some other bricks may drop because of that erasure.
 * 
 * Return an array representing the number of bricks that will drop after each
 * erasure in sequence.
 * 
 * Example 1: Input: grid = [[1,0,0,0],[1,1,1,0]] hits = [[1,0]] Output: [2]
 * Explanation: If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2)
 * will drop. So we should return 2. Example 2: Input: grid =
 * [[1,0,0,0],[1,1,0,0]] hits = [[1,1],[1,0]] Output: [0,0] Explanation: When we
 * erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to
 * the last move. So each erasure will cause no bricks dropping. Note that the
 * erased brick (1, 0) will not be counted as a dropped brick.
 * 
 * 
 * Note:
 * 
 * The number of rows and columns in the grid will be in the range [1, 200]. The
 * number of erasures will not exceed the area of the grid. It is guaranteed
 * that each erasure will be different from any other erasure, and located
 * inside the grid. An erasure may refer to a location with no brick - if it
 * does, no bricks drop.
 */
class Solution {
    private static final int[][] dirs = new int[][] { { +1, 0 }, { -1, 0 }, { 0, +1 }, { 0, -1 } };
    int size, n, m;
    int[] compParent;
    int[] compSize;
    boolean[] isAttached;
    int[] dropCount;

    private int findComp(int v) {
        return (v == compParent[v]) ? v : (compParent[v] = findComp(compParent[v]));
    }

    private void unionComps(int compU, int compV) {
        if (compU == compV)
            return;
        if (compSize[compU] < compSize[compV]) {
            int tmp = compU;
            compU = compV;
            compV = tmp;
        }
        compParent[compV] = compU;
        compSize[compU] += compSize[compV];
    }

    private void union(int u, int v) {
        unionComps(findComp(u), findComp(v));
    }

    private int ind(int i, int j) {
        return i * m + j;
    }

    public int[] hitBricks(int[][] grid, int[][] hits) {
        dropCount = new int[hits.length];
        n = grid.length;
        m = grid[0].length;
        size = n * m;
        compParent = new int[size];
        compSize = new int[size];
        isAttached = new boolean[size];
        for (int[] hit : hits) {
            if (grid[hit[0]][hit[1]] == 1) {
                grid[hit[0]][hit[1]] = 0;
            } else {
                grid[hit[0]][hit[1]] = -1;
            }
        }
        for (int i = 0; i < size; ++i) {
            compParent[i] = i;
            compSize[i] = 1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] != 1)
                    continue;
                if (i > 0 && grid[i - 1][j] == 1)
                    union(ind(i, j), ind(i - 1, j));
                if (j > 0 && grid[i][j - 1] == 1)
                    union(ind(i, j), ind(i, j - 1));
            }
        }
        for (int j = 0; j < m; ++j) {
            if (grid[0][j] == 1)
                isAttached[findComp(ind(0, j))] = true;
        }
        for (int i = hits.length - 1; i >= 0; --i) {
            int x = hits[i][0], y = hits[i][1];
            if (grid[x][y] == -1)
                continue;
            Set<Integer> comps = new HashSet<>();
            for (int[] dir : dirs) {
                int nx = x + dir[0], ny = y + dir[1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 1) {
                    comps.add(findComp(ind(nx, ny)));
                }
            }
            boolean attached = false;
            for (Integer comp : comps) {
                if (!isAttached[comp]) {
                    dropCount[i] += compSize[comp];
                } else {
                    attached = true;
                }
            }
            for (Integer comp : comps) {
                unionComps(comp, findComp(ind(x, y)));
            }
            int newComp = findComp(ind(x, y));
            isAttached[newComp] = attached || (x == 0);
            if (!isAttached[newComp])
                dropCount[i] = 0;
            grid[x][y] = 1;
        }
        return dropCount;
    }
}
