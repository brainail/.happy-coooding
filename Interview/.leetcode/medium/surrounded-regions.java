/**
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions 
 * surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example:

X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
Explanation:

Surrounded regions shouldn’t be on the border, which means that any 'O' 
on the border of the board are not flipped to 'X'. Any 'O' that is not on the 
border and it is not connected to an 'O' on the border will be flipped to 'X'.
Two cells are connected if they are adjacent cells connected horizontally or vertically.
 */
class Solution {
    private void fill(int i, int j, char[][] board, int n, int m) {
        if (i < 0 || i >= n)
            return;
        if (j < 0 || j >= m)
            return;
        if (board[i][j] != 'O')
            return;
        board[i][j] = 'B';
        fill(i - 1, j, board, n, m);
        fill(i + 1, j, board, n, m);
        fill(i, j - 1, board, n, m);
        fill(i, j + 1, board, n, m);
    }

    public void solve(char[][] board) {
        int n = board.length;
        if (n == 0)
            return;
        int m = board[0].length;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!(i == 0 || i == n - 1 || j == 0 || j == m - 1))
                    continue;
                fill(i, j, board, n, m);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                if (board[i][j] == 'B')
                    board[i][j] = 'O';
            }
        }
    }
}
