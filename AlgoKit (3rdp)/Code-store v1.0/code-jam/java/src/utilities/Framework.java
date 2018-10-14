package utilities;

import static java.lang.Math.*;

import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

import utilities.struct.*;

public class Framework
{
    // *************************** ALGORITHMS *********************************
    // ========================= SORTING AND SEARCHING ========================
    // Arrays.asList, binarySearch, equals, fill, sort

    public static void xorSwap(int[] array, int pos1, int pos2)
    {
        // A XOR A = 0
        if (array[pos1] == array[pos2]) return;

        array[pos1] ^= array[pos2];
        array[pos2] ^= array[pos1];
        array[pos1] ^= array[pos2];
    }

    public static void quickSort(int[] array)
    {
        qsort(array, 0, array.length - 1);
    }

    private static void qsort(int[] numbers, int low, int high)
    {
        int i = low, j = high;
        // Get the pivot element from the middle of the list
        int pivot = numbers[low + (high - low) / 2];

        // Divide into two lists
        while (i <= j) {
            // If the current value from the left list is smaller then the pivot
            // element then get the next element from the left list
            while (numbers[i] < pivot) {
                i++;
            }
            // If the current value from the right list is larger then the pivot
            // element then get the next element from the right list
            while (numbers[j] > pivot) {
                j--;
            }

            // If we have found a values in the left list which is larger then
            // the pivot element and if we have found a value in the right list
            // which is smaller then the pivot element then we exchange the
            // values.
            // As we are done we can increase i and j
            if (i <= j) {
                // exchange(i, j);
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;

                i++;
                j--;
            }
        }
        // Recursion
        if (low < j) qsort(numbers, low, j);
        if (i < high) qsort(numbers, i, high);
    }

    public static void mergeSort(int[] values)
    {
        msort(values, 0, values.length - 1);
    }

    /**
     * Helper method for merge sort
     * 
     * @param values
     * @param low
     * @param high
     */
    private static void msort(int[] values, int low, int high)
    {
        // Check if low is smaller then high, if not then the array is sorted
        if (low < high) {
            // Get the index of the element which is in the middle
            int middle = (low + high) / 2;
            // Sort the left side of the array
            msort(values, low, middle);
            // Sort the right side of the array
            msort(values, middle + 1, high);

            // Combine them both => merge
            // Helperarray
            int[] helper = new int[values.length];
            // Copy both parts into the helper array
            for (int i = low; i <= high; i++) {
                helper[i] = values[i];
            }
            int i = low;
            int j = middle + 1;
            int k = low;
            // Copy the smallest values from either the left or the right side
            // back
            // to the original array
            while (i <= middle && j <= high) {
                if (helper[i] <= helper[j]) {
                    values[k] = helper[i];
                    i++;
                } else {
                    values[k] = helper[j];
                    j++;
                }
                k++;
            }
            // Copy the rest of the left side of the array into the target array
            while (i <= middle) {
                values[k] = helper[i];
                k++;
                i++;
            }
            helper = null;
        }
    }

    /**
     * removes all the chars present in 'remove' from 'str' and returns
     * resulting string
     */
    public static String removeChars(String str, String remove)
    {
        boolean[] bitset = new boolean[128]; // ASCII are 7-bit

        // initialize array
        /**
         * Because the size of a character is fixed for a given platform,
         * zeroing the array is constant time - O(1)
         */
        for (int i = 0; i < bitset.length; ++i)
            bitset[i] = false;

        /**
         * building lookup array is O(m)
         */
        for (int i = 0; i < remove.length(); ++i)
            bitset[remove.charAt(i)] = true;

        /**
         * Finally, you do at most one constant time lookup and one constant
         * time copy for each character in str, giving O(n) for this stage.
         */
        int dst = 0;
        char[] s = new char[str.length()];
        for (int i = 0; i < str.length(); ++i) {
            if (!bitset[str.charAt(i)]) {
                s[dst++] = str.charAt(i);
            }
        }

        return new String(s, 0, dst);
    }

    /**
     * performs L-to-R corresponding scan comparison of 2 generic arrays, and
     * returns the number of matches found
     */
    public static <T> int numCorrespondingMatches(T[] a, T[] b)
    {
        int result = 0;
        for (int i = 0; i < min(a.length, b.length); i++) {
            if (a[i] != null && b[i] != null && a[i].equals(b[i])) {
                result++;
            }
        }
        return result;
    }

    /**
     * equivalent for int primitive
     */
    public static int numCorrespondingMatches(int[] a, int[] b)
    {
        int result = 0;
        for (int i = 0; i < min(a.length, b.length); i++) {
            if (a[i] == b[i]) {
                result++;
            }
        }
        return result;
    }

    // ============================ COMBINATORICS =============================
    /**
     * This function will count the number of inversions in an array of numbers.
     * (Recall that an inversion is a pair of numbers that appear out of
     * numerical order in the list.
     * 
     * We use a modified version of the MergeSort algorithm to do this, so it's
     * a recursive function. We split the list into two (almost) equal parts,
     * recursively count the number of inversions in each part, and then count
     * inversions caused by one element from each part of the list.
     * 
     * The merging is done is a separate procedure given below, in order to
     * simplify the presentation of the algorithm here.
     * 
     * Note: I am assuming that the integers are distinct, but they need *not*
     * be integers { 1, 2, ..., n} for some n.
     */
    public static int countInversions(int nums[])
    {
        int mid = nums.length / 2, k;
        int countLeft, countRight, countMerge;

        /* If the list is small, there's nothing to do. */
        if (nums.length <= 1) return 0;

        /*
         * Otherwise, we create new arrays and split the list into two (almost)
         * equal parts.
         */
        int left[] = new int[mid];
        int right[] = new int[nums.length - mid];

        for (k = 0; k < mid; k++)
            left[k] = nums[k];
        for (k = 0; k < nums.length - mid; k++)
            right[k] = nums[mid + k];

        /*
         * Recursively count the inversions in each part.
         */
        countLeft = countInversions(left);
        countRight = countInversions(right);

        /*
         * Now merge the two sublists together, and count the inversions caused
         * by pairs of elements, one from each half of the original list.
         */
        int result[] = new int[nums.length];
        countMerge = mergeAndCountInversions(left, right, result);

        /*
         * Finally, put the resulting list back into the original one. This is
         * necessary for the recursive calls to work correctly.
         */
        for (k = 0; k < nums.length; k++)
            nums[k] = result[k];

        /*
         * Return the sum of the values computed to get the total number of
         * inversions for the list.
         */
        return (countLeft + countRight + countMerge);

    } /* end of "countInversions" procedure */

    /**
     * This procedure will merge the two lists, and count the number of
     * inversions caused by the elements in the "right" list that are less than
     * elements in the "left" list.
     */
    public static int mergeAndCountInversions(
        int left[],
        int right[],
        int result[])
    {
        int a = 0, b = 0, count = 0, i, k = 0;

        while ((a < left.length) && (b < right.length)) {
            if (left[a] <= right[b])
                result[k] = left[a++];
            else /* You have found (a number of) inversions here. */
            {
                result[k] = right[b++];
                count += left.length - a;
            }
            k++;
        }

        if (a == left.length)
            for (i = b; i < right.length; i++)
                result[k++] = right[i];
        else
            for (i = a; i < left.length; i++)
                result[k++] = left[i];

        return count;
    }

    /**
     * implementation of "n choose k", ie. nCk
     */
    public static long choose(int n, int k)
    {
        k = min(k, n - k);
        if (k < 0) {
            return 0;
        }
        long result = 1;
        for (int i = 1; i <= k; ++i) {
            result *= (n - i + 1) / i;
        }
        return result;
    }

    /**
     * generates the entire list of binomial coefficients
     * for a given level in Pascal's Triangle
     * 
     * @param n
     * @param k
     * @return "n choose k", ie. nCk
     */
    public static BigInteger chooseAll(int n, int k)
    {
        BigInteger[] b = new BigInteger[n + 1];
        b[0] = BigInteger.ONE;
        for (int i = 1; i <= n; ++i) {
            b[i] = BigInteger.ONE;
            for (int j = i - 1; j > 0; --j) {
                b[j] = b[j].add(b[j - 1]);
            }
        }

        // System.out.println(Arrays.deepToString(b));

        return b[k];
    }

    /**
     * implementation of "n permute k", ie. nPk
     */
    public static BigInteger permute(int n, int m)
    {
        BigInteger result = chooseAll(n, m);
        result = result.multiply(factorial(m));
        return result;
    }

    /**
     * Helper function to return the factorial of a given number m
     * 
     * @param m
     * @return
     */
    public static BigInteger factorial(int m)
    {
        BigInteger n = BigInteger.ONE;
        for (int i = 1; i <= m; i++) {
            n = n.multiply(BigInteger.valueOf(i));
        }
        return n;
    }

    /**
     * generates the power set of the given originalSet of elements
     * 
     * @param <T>
     * @param originalSet
     * @return
     */
    public static <T> Set<Set<T>> powerSet(Set<T> originalSet)
    {
        Set<Set<T>> sets = new HashSet<Set<T>>();
        if (originalSet.isEmpty()) {
            sets.add(new HashSet<T>());
            return sets;
        }
        List<T> list = new ArrayList<T>(originalSet);
        T head = list.get(0);
        Set<T> rest = new HashSet<T>(list.subList(1, list.size()));
        for (Set<T> set : powerSet(rest)) {
            Set<T> newSet = new HashSet<T>();
            newSet.add(head);
            newSet.addAll(set);
            sets.add(newSet);
            sets.add(set);
        }
        return sets;
    }

    /**
     * prints power set for given array
     * - do processing within function where it says
     * 
     * @param a
     */
    public static void printPowerSet(int[] a)
    {
        int maxCombinations = (int) pow(2, a.length); // 2^(a.length)

        System.out.println("1: {}"); // empty set

        for (int i = 1; i < maxCombinations; i++) {
            // for each set
            int count = i + 1;
            System.out.print(count + " : { "); // begin print

            List<Integer> setI = new ArrayList<Integer>();

            // search for elements present, ie. 'set'
            for (int j = 0; j < a.length; j++) {
                // for each element in set
                if (((i >> j) & 1) == 1) {
                    System.out.print(a[j] + " ");
                    setI.add(a[j]); // add to complete set at each iteration
                }
            }

            System.out.println("}"); // end print

            /* do processing for a single set here! */
            System.out.println("completed set (i+1): " + setI);
        }
    }

    /**
     * generates a list of all the permutations for a given array
     * insert loop processing function wihtin doPermute()
     * 
     * @param array
     */
    public static void permute(int[] array)
    {
        doPermute(array, new LinkedList<Integer>(), new boolean[array.length],
            array.length, 0);
    }

    /**
     * Helper function for {@link Framework#permute(int[])}
     * 
     * @param array
     * @param result
     * @param used
     * @param length
     * @param level
     */
    public static void doPermute(
        int[] array,
        LinkedList<Integer> result,
        boolean[] used,
        int length,
        int level)
    {
        // base case - fully used, ie. completed set permutation generated
        if (level == length) {

            /* do processing for a single set here! */
            System.out.println(result);

            return;
        }

        // recursive case
        for (int i = 0; i < length; ++i) {
            if (used[i]) { // do not add duplicate elements to list
                continue;
            }

            // add new element to set
            result.add(array[i]);
            used[i] = true;

            // recursive step
            doPermute(array, result, used, length, level + 1);
            used[i] = false;

            // the last element is removed from set
            result.removeLast();
        }
    }

    /**
     * counts the total number of possible factorisations for n
     * for integer partitions, replace n/m by n-m
     * 
     * @param n
     * @return
     */
    public static int countNumFactorisations(int n)
    {
        return countFactors(n, 2) - 1;
    }

    private static int countFactors(int n, int m)
    {
        int t = 0;
        while (m * m <= n) { // m <= sqrt(n)
            if (n % m == 0) { // is a factor
                t += countFactors(n / m, m);
            }
            m++;
        }
        return t + 1;
    }
}
