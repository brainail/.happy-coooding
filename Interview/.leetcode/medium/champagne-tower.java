/**
 * We stack glasses in a pyramid, where the first row has 1 glass, the second
 * row has 2 glasses, and so on until the 100th row. Each glass holds one cup
 * (250ml) of champagne.
 * 
 * Then, some champagne is poured in the first glass at the top. When the top
 * most glass is full, any excess liquid poured will fall equally to the glass
 * immediately to the left and right of it. When those glasses become full, any
 * excess champagne will fall equally to the left and right of those glasses,
 * and so on. (A glass at the bottom row has it's excess champagne fall on the
 * floor.)
 * 
 * For example, after one cup of champagne is poured, the top most glass is
 * full. After two cups of champagne are poured, the two glasses on the second
 * row are half full. After three cups of champagne are poured, those two cups
 * become full - there are 3 full glasses total now. After four cups of
 * champagne are poured, the third row has the middle glass half full, and the
 * two outside glasses are a quarter full, as pictured below.
 * 
 * 
 * 
 * Now after pouring some non-negative integer cups of champagne, return how
 * full the j-th glass in the i-th row is (both i and j are 0 indexed.)
 */

class Solution {
    public double champagneTower(int cha, int row, int col) {
        double[] glasses = new double[100 + 10];
        double[] glassesBuff = new double[100 + 10];
        glasses[0] = cha;
        for (int step = 0; step < row; ++step) {
            Arrays.fill(glassesBuff, 0.0);
            for (int i = 0; i <= step; ++i)
                if (glasses[i] > 1) {
                    double t = (glasses[i] - 1) / 2.0;
                    glassesBuff[i] += t;
                    glassesBuff[i + 1] += t;
                }
            System.arraycopy(glassesBuff, 0, glasses, 0, glasses.length);
        }
        for (int i = 0; i <= row; ++i)
            glasses[i] = Math.min(glasses[i], 1);
        return glasses[col];
    }
}
