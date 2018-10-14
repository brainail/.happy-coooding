package utilities.combinatorics;

public class KSubsetsRecursiveLoop
{
    private static int n, K;
    private static String[] set;

    public static void main(String[] args)
    {
        set = new String[] { "1a", "2b", "3c", "4d" };
        n = set.length;
        K = 2;
        buildSubsets(0, 0, "");
    }

    private static void buildSubsets(int i, int j, String subset)
    {
        if (j == K) {
            // subset complete
            System.out.print(subset + " ");
            return;
        }

        // incomplete => #elem < n => continuing building
        for (; i < n; ++i) {
            buildSubsets(i + 1, j + 1, subset + set[i].charAt(0));
        }
    }
}
