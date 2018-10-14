package utilities.combinatorics;

public class AllSubsetsLexicographic
{
    private static int n;
    private static String[] set;

    public static void main(String[] args)
    {
        set = new String[] { "1a", "2b", "3c", "4d" };
        n = set.length;
        foo(0, "");
    }

    private static void foo(int i, String subset)
    {
        System.out.println('"' + subset + '"');
        for (; i < n; i++) {
            foo(i + 1, subset + set[i].charAt(0));
        }
    }
}
