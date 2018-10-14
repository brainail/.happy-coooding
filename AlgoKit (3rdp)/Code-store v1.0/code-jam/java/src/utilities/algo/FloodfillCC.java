package utilities.algo;

import java.util.*;

public class FloodfillCC
{
    private static String[] land;
    private static boolean[][] isFilled;
    private static int m, n;
    private static boolean[][] seen;

    public static void main(String[] args)
    {
        // init input data
        land = new String[] { "ACCCCACB", "AAAACACB", "BCAACCCA", "BBBBACAA",
                        "BCCBAACC", "BBBBBAAC" };
        isFilled = new boolean[land.length][land[0].length()];

        System.out.println("map of land");
        for (int i = 0; i < land.length; i++) {
            System.out.println(land[i]);
        }
        System.out.println();

        // part 1 - recursively figure out how many subgroups present in grid
        System.out.println("# connected components: " + numberOfRegions(land)
                        + "\n");

        // populated isFilled array depending on whether grid cell == 'A'
        for (int x = 0; x < land.length; x++) {
            for (int y = 0; y < land[0].length(); y++) {
                isFilled[x][y] = land[x].charAt(y) != 'A';
            }
        }
        System.out.println("isFilled[x][y] == A");
        for (int i = 0; i < isFilled.length; i++) {
            System.out.println(Arrays.toString(isFilled[i]));
        }
        System.out.println();

        // figure out from isFilled size of each connected component 'A'
        List<Integer> result = new ArrayList<Integer>();
        for (int x = 0; x < isFilled.length; x++) {
            for (int y = 0; y < isFilled[0].length; y++) {
                if (!isFilled[x][y]) {
                    result.add(doFill(x, y));
                }
            }
        }
        System.out.println(result);
    }

    public static int numberOfRegions(String[] land)
    {
        m = land.length;
        n = land[0].length();
        seen = new boolean[m][n];

        int answer = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (!seen[i][j]) {
                    ++answer;
                    flood(i, j, land[i].charAt(j));
                }
            }
        }

        return answer;
    }

    public static void flood(int i, int j, char farmer)
    {
        // out-of-bounds check, visited before check, different region color
        if (i < 0 || i >= m || j < 0 || j >= n || seen[i][j]
                        || land[i].charAt(j) != farmer) {
            return;
        }
        seen[i][j] = true;

        // 4 basic directions - NSEW
        flood(i - 1, j, farmer);
        flood(i + 1, j, farmer);
        flood(i, j - 1, farmer);
        flood(i, j + 1, farmer);

        // diagonals
        // flood(i - 1, j - 1, farmer);
        // flood(i - 1, j + 1, farmer);
        // flood(i + 1, j - 1, farmer);
        // flood(i + 1, j + 1, farmer);
    }

    /**
     * returns the size of the connected area, using Floodfill algorithm
     * by implementation of DFS through given setup config
     * 
     * @param x
     * @param y
     * @return
     */
    public static int doFill(int x, int y)
    {
        int result = 0;

        // Declare our stack of nodes, and push our starting node onto the stack
        Stack<Node> s = new Stack<Node>();
        s.push(node(x, y));

        while (!s.empty()) {
            Node top = s.pop();

            // grid out-of-bounds check
            if (top.x < 0 || top.x >= isFilled.length) continue;
            if (top.y < 0 || top.y >= isFilled[0].length) continue;
            // visited before?
            if (isFilled[top.x][top.y]) continue;

            isFilled[top.x][top.y] = true; // mark node visited

            // We have found this node to be empty, and part
            // of this connected area, so add 1 to the result
            result++;

            // Now we know that we have at least one empty square, then we will
            // attempt to visit every node adjacent to this node.

            // 4 basic directions - NSEW
            s.push(node(top.x + 1, top.y));
            s.push(node(top.x - 1, top.y));
            s.push(node(top.x, top.y + 1));
            s.push(node(top.x, top.y - 1));

            // diagonals
            // s.push(node(top.x - 1, top.y - 1));
            // s.push(node(top.x + 1, top.y + 1));
            // s.push(node(top.x - 1, top.y + 1));
            // s.push(node(top.x + 1, top.y - 1));
        }

        return result;
    }

    public static Node node(int x, int y)
    {
        return new Node(x, y);
    }

    private static class Node
    {
        int x, y;

        public Node(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
    }
}
