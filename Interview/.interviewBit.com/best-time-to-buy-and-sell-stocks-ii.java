public class Solution {
    public int maxProfit(final List<Integer> stock) {
        final int days = stock.size();
        final int [][] dp = new int [2][days + 1];
        Arrays.fill(dp [0], Integer.MIN_VALUE);
        Arrays.fill(dp [1], Integer.MIN_VALUE);
        dp [0][0] = 0;
        
        for (int day = 0; day < days; ++ day) {
            for (int op = 0; op < 2; ++ op) {
                if (Integer.MIN_VALUE == dp [op][day]) {
                    continue; // early continue;
                }
                
                dp [op][day + 1] = Math.max(dp [op][day + 1], dp [op][day]);
                final int revOp = op ^ 1;
                final int price = stock.get(day) * (0 == revOp ? +1 : -1);
                dp [revOp][day + 1] = Math.max(dp [revOp][day + 1], dp [op][day] + price);
            }
        }
        
        return dp [0][days];
    }
}
