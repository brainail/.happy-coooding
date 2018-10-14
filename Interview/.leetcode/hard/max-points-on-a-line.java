/**
 * Given n points on a 2D plane, find the maximum number of points that lie on
 * the same straight line.
 * 
Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
*/
public class Solution {
    public int gcd(int a, int b) {
        return (a < 0) ? gcd(-a, b) : (b < 0 ? gcd(a, -b) : (b > 0 ? gcd(b, a % b) : a));
    }

    public int maxPoints(Point[] points) {
        int result = 0;
        final int n = points.length;
        Map<List<Integer>, Integer> map = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            map.clear();
            int duplicate = 0;
            int localResult = 0;
            for (int t = 0; t < n; ++t) {
                int vX = points[i].x - points[t].x;
                int vY = points[i].y - points[t].y;
                if (0 == vX && 0 == vY) {
                    ++duplicate;
                    continue;
                }

                final int common = gcd(vX, vY);
                vX /= common;
                vY /= common;
                if (vX < 0) {
                    vX *= -1;
                    vY *= -1;
                }

                final List<Integer> line = Arrays.asList(vX, vY);
                final int sameLine = (map.containsKey(line) ? map.get(line) : 0) + 1;
                map.put(line, sameLine);

                localResult = Math.max(localResult, sameLine);
            }
            result = Math.max(result, localResult + duplicate);
        }
        return result;
    }
}
