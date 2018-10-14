package utilities.combinatorics;

public class KSubsetsBitfieldCounterLexicographic
{
    public static void main(String[] args)
    {
        String[] set = new String[] { "1a", "2b", "3c", "4d" };
        int n = set.length, K = 2;

        for (int B = 0; B < (1 << n); B++) {
            // ignore if permutation is of incorrect bit length
            if (bitcount(B) != K) {
                continue;
            }

            String subset = "";
            for (int i = n - 1; i >= 0; i--) {
                if ((B & (1 << i)) == 0) {
                    subset += set[n - 1 - i].charAt(0);
                }
            }
            System.out.print(subset + " ");
        }
        System.out.println();
    }

    private static int bitcount(int n)
    {
        return (n == 0) ? 0 : (n & 1) + bitcount(n / 2);
    }
}