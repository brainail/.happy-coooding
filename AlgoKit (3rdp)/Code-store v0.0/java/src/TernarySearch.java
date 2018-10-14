import java.util.Random;
import java.util.function.*;

public class TernarySearch {

	// finds maximum of strictly increasing and then decreasing function
	public static double ternarySearch(DoubleUnaryOperator f, double lo, double hi) {
		for (int step = 0; step < 1000; step++) {
			double m1 = lo + (hi - lo) / 3;
			double m2 = hi - (hi - lo) / 3;
			if (f.applyAsDouble(m1) < f.applyAsDouble(m2))
				lo = m1;
			else
				hi = m2;
		}
		return (lo + hi) / 2;
	}

	// finds maximum of strictly increasing and then decreasing function
	public static int ternarySearch(IntUnaryOperator f, int fromInclusive, int toInclusive) {
		int lo = fromInclusive - 1;
		int hi = toInclusive;
		while (lo < hi - 1) {
			int mid = (lo + hi) >>> 1;
			if (f.applyAsInt(mid) < f.applyAsInt(mid + 1)) {
				lo = mid;
			} else {
				hi = mid;
			}
		}
		return hi;
	}

	// random tests
	public static void main(String[] args) {
		System.out.println(ternarySearch((DoubleUnaryOperator) x -> -(x - 2) * (x - 2), -10, 10));

		Random rnd = new Random(1);
		for (int step = 0; step < 1000; step++) {
			int n = rnd.nextInt(20) + 1;
			int p = rnd.nextInt(n);
			int[] a = new int[n];
			final int range = 10;
			a[p] = rnd.nextInt(range);
			for (int i = p - 1; i >= 0; i--)
				a[i] = a[i + 1] - rnd.nextInt(range) - 1;
			for (int i = p + 1; i < n; i++)
				a[i] = a[i - 1] - rnd.nextInt(range) - 1;
			int res = ternarySearch((IntUnaryOperator) i -> a[i], 0, a.length - 1);
			if (a[p] != a[res])
				throw new RuntimeException();
		}
	}
}
