private static final int ROWS = 4;

interface Sequence {
    void onNext(final int next);
}

void enumBlocks(int cur, int pos, int next, Sequence sequence) {
    if (pos >= ROWS) { // done
        sequence.onNext(next);
    } else if (((cur >> pos) & 1) != 0) { // occupied
        enumBlocks(cur, pos + 1, next, sequence);
    } else { // horizontal, vertical        
        enumBlocks(cur | (1 << pos), pos + 1, next | (1 << pos), sequence);
        if (pos + 1 < ROWS && ((cur >> (pos + 1)) & 1) == 0) {
            final int newCur = cur | (1 << pos) | (1 << (pos + 1));
            enumBlocks(newCur, pos + 2, next, sequence);
        }
    }   
}

int fillingBlocks(int n) {
    final int maskSize = 1 << ROWS;
    final int [][] dp = new int [n + 1][maskSize];
    dp [0][0] = 1;
    
    for (int col = 0; col < n; ++ col) {
        for (int mask = 0; mask < maskSize; ++ mask) {
            final int curCol = col;
            final int curMask = mask;
            enumBlocks(mask, 0, 0, new Sequence() {
                @Override
                public void onNext(final int next) {
                    dp [curCol + 1][next] += dp [curCol][curMask];
                }
            });
        } 
    }
    
    return dp [n][0];
}
