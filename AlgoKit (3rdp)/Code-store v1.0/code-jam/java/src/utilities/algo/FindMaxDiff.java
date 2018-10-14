package utilities.algo;

public class FindMaxDiff
{
    private static int start = 0, end = 0;

    public static void main(String[] args)
    {
        int[] array = { 4, 3, 9, 1, 8, 2, 6, 7, 5 };
        maxDiffLinear(array);
        System.out.println(start + " " + end);
    }

    /**
     * calculate the max difference for the subarray traversed till
     * now and whenever we find a better difference value we can
     * replace it by this value. This is a dynamic approach and
     * complete in O(1) space and O(n) time.
     * 
     * @param xs
     */
    private static void maxDiffLinear(int[] xs)
    {
        int min = 0, maxDiff = 0;
        for (int i = 0; i < xs.length; i++) {
            if (xs[i] < xs[min]) {
                min = i;
            }

            int diff = xs[i] - xs[min];

            if (diff > maxDiff) {
                start = min;
                end = i;
                maxDiff = diff;
            } // end if
        } // end for
    } // end function
}
