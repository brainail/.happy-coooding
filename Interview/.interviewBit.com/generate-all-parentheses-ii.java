public class Solution {
    private void genAll(
        final int pos,
        final int nOpened,
        final int nClosed,
        final int n,
        final StringBuilder buff,
        final ArrayList<String> outResult) {
        
        if (pos == 2 * n) {
            outResult.add(buff.toString());
            return;
        }
        
        // `(`
        if (nOpened + 1 <= n) {
            buff.setCharAt(pos, '(');
            genAll(pos + 1, nOpened + 1, nClosed, n, buff, outResult);
        }

        // `)`
        if (nClosed + 1 <= n && nOpened - nClosed - 1 >= 0) {
            buff.setCharAt(pos, ')');
            genAll(pos + 1, nOpened, nClosed + 1, n, buff, outResult);
        }
    }
    
    public ArrayList<String> generateParenthesis(int n) {
        final ArrayList<String> outResult = new ArrayList<> ();
        final StringBuilder buff = new StringBuilder();
        buff.setLength(2 * n);
        genAll(0, 0, 0, n, buff, outResult);
        return outResult;
    }
}
