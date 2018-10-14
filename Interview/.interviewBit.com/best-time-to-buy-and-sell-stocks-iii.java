public class Solution {
    public int maxProfit(final List<Integer> stock) {
        final int days = stock.size();
        final int [][][] dp = new int [2][3][days + 1];
        for (int i = 0; i < 2; ++ i) {
            for (int j = 0; j < 3; ++ j) {
                Arrays.fill(dp [i][j], Integer.MIN_VALUE);
            }
        }
        dp [0][0][0] = 0;
        
        for (int day = 0; day < days; ++ day) {
            for (int tr = 0; tr < 3; ++ tr) {
                for (int op = 0; op < 2; ++ op) {
                    if (Integer.MIN_VALUE == dp [op][tr][day]) {
                        continue; // early continue;
                    }
                
                    dp [op][tr][day + 1] = Math.max(dp [op][tr][day + 1], dp [op][tr][day]);
                    final int revOp = op ^ 1;
                    final int price = stock.get(day) * (0 == revOp ? +1 : -1);
                    final int isTr = op;
                    
                    if (tr + isTr < 3) {
                        dp [revOp][tr + isTr][day + 1] 
                            = Math.max(dp [revOp][tr + isTr][day + 1] , dp [op][tr][day] + price);
                    }
                }
            }
        }
        
        return Math.max(0, Math.max(dp [0][2][days], dp [0][1][days]));
    }
}
