public class Solution {
    public int gcd(int a, int b) {
        return (a < 0) 
            ? gcd(-a, b) 
            : (b < 0 
                ? gcd(a, -b)
                : (b > 0 
                    ? gcd(b, a % b) 
                    : a));
    }
    
    public int maxPoints(ArrayList<Integer> x, ArrayList<Integer> y) {
        int result = 0;
        final int n = x.size();
        Map<List<Integer>, Integer> map = new HashMap<> ();
        for (int i = 0; i < n; ++ i) {
            map.clear();
            int duplicate = 1;
            int localResult = 0;
            for (int t = i + 1; t < n; ++ t) {
                int vX = x.get(i) - x.get(t);
                int vY = y.get(i) - y.get(t);
                if (0 == vX && 0 == vY) {
                    ++ duplicate;
                    continue;
                }
                
                final int common = gcd(vX, vY);
                vX /= common;
                vY /= common;
                if (vX < 0) {
                    vX *= -1;
                    vY *= -1;
                } else if (0 == vX) {
                    vY = 0;
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
