package utilities.algo;

import java.util.*;

public class Select
{
    private static Random rnd = new Random();

    public static void swap(int[] array, int i, int j)
    {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static int[] partition(int[] array, int pivot, int left, int right)
    {
        int pivots = 0;
        int end = right;

        for (int i = left; i <= end; i++)
            if (array[i] > pivot) swap(array, i--, end--);

        for (int i = left; i <= end; i++)
            if (array[i] == pivot) {
                swap(array, i--, end--);
                pivots++;
            }

        return new int[] { end + 1, end + pivots };
    }

    public static int randomizedSelect(int[] array, int k)
    {
        return randomizedSelect(array, k, 0, array.length - 1);
    }

    public static int randomizedSelect(int[] array, int k, int left, int right)
    {
        int pivotIndex = left + rnd.nextInt(right - left + 1);
        int[] pos = partition(array, array[pivotIndex], left, right);

        if (k < pos[0])
            return randomizedSelect(array, k, left, pos[0] - 1);
        else if (k > pos[1])
            return randomizedSelect(array, k, pos[1] + 1, right);
        else
            return array[k];
    }
}
