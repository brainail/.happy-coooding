import java.util.*;

public class InversionCount {
	public static int merge(int[] arr, int[] left, int[] right) {
		int i = 0, j = 0, count = 0;

		while (i < left.length && j < right.length) {
			if (left[i] <= right[j])
				arr[i + j] = left[i++];
			else {
				arr[i + j] = right[j++];
				count += left.length - i;
			}
		}

		while (i < left.length)
			arr[i + j] = left[i++];
		while (j < right.length)
			arr[i + j] = right[j++];

		return count;
	}

	public static int inversionCount(int[] arr) {
		if (arr.length < 2)
			return 0;

		int m = (arr.length + 1) / 2;
		int left[] = Arrays.copyOfRange(arr, 0, m);
		int right[] = Arrays.copyOfRange(arr, m, arr.length);

		return inversionCount(left) + inversionCount(right) + merge(arr, left, right);
	}
}
