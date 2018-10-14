public class TaskAboutWords {
    
    String word;
    int n;
    
    TaskAboutWords(String word) {
        this.n = word.length();
        this.word = word;
    }

boolean placement(int pos, int x, int y, char [][] board) {
    if (pos == n - 1) {
        return true;
    }
    
    boolean found = false;
    for (int vx = -1; vx <= +1; ++ vx) {
        for (int vy = -1; vy <= +1; ++ vy) {
            if (0 == vx && 0 == vy) continue;
            int nx = x + vx;
            int ny = y + vy;
            if (nx < 0 || nx >= board.length) continue;
            if (ny < 0 || ny >= board [nx].length) continue;
            if (board [nx][ny] != word.charAt(pos + 1)) continue;
            board [nx][ny] = ' ';
            found = placement(pos + 1, nx, ny, board);
            board [nx][ny] = word.charAt(pos + 1);
            if (found) break;
        }
        if (found) break;
    }
    return found;
}
    
}

String[] wordBoggle(char[][] board, String[] words) {
    List<String> result = new ArrayList<>();
    for (final String word : words) {
        boolean found = false;
        for (int x = 0; x < board.length; ++ x) {
            for (int y = 0; y < board [x].length; ++ y) {
                if (board [x][y] != word.charAt(0)) continue;
                board [x][y] = ' ';
                found = new TaskAboutWords(word).placement(0, x, y, board);
                board [x][y] = word.charAt(0);
                if (found) break;
            }
            if (found) break;
        }
        if (found) {
            result.add(word);
        }
    }
    Collections.sort(result);
    return result.toArray(new String [0]);
}
