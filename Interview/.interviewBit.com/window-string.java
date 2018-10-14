public class Solution {
    public String minWindow(String S, String T) {
        final int nS = S.length();
        final int nT = T.length();

        final HashMap<Integer, Integer> windowCurrent = new HashMap<> (nT);
        final HashMap<Integer, Integer> windowAll = new HashMap<> (nT);
        for (int i = 0; i < nT; ++ i) {
            final int ch = (int) T.charAt(i);
            windowCurrent.put(ch, 0);
            windowAll.put(ch, (windowAll.containsKey(ch) ? windowAll.get(ch) : 0) + 1);
        }

        int need = windowCurrent.keySet().size();
        int right = -1;
        int resultLeft = 0;
        int resultRight = Integer.MAX_VALUE;

        for (int left = 0; left < nS - nT + 1; ++ left) {
            right = Math.max(right, left - 1);
            
            while (right + 1 < nS && need > 0) {
                final int ch = S.charAt(right + 1);
                if (windowCurrent.containsKey(ch)) {
                    if (windowAll.get(ch) == windowCurrent.get(ch) + 1) {
                        -- need;
                    }
                    windowCurrent.put(ch, windowCurrent.get(ch) + 1);
                }
                ++ right;
            }
            
            if (0 == need && right >= left && (right - left) < (resultRight - resultLeft)) {
                resultLeft = left;
                resultRight = right;
            }
            
            final int ch = S.charAt(left);
            if (windowCurrent.containsKey(ch)) {
                windowCurrent.put(ch, windowCurrent.get(ch) - 1);
                if (windowAll.get(ch) == windowCurrent.get(ch) + 1) {
                    ++ need;
                }
            }
        }
        
        if (Integer.MAX_VALUE == resultRight) {
            return "";
        } else {
            return S.substring(resultLeft, resultRight + 1);
        }
    }
}
