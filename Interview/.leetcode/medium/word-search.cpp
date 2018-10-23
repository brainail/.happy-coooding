/**
 * Given a 2D board and a word, find if the word exists in the grid.
 * 
 * The word can be constructed from letters of sequentially adjacent cell, where
 * "adjacent" cells are those horizontally or vertically neighboring. The same
 * letter cell may not be used more than once.
 * 
 * Example:
 * 
 * board = [ ['A','B','C','E'], ['S','F','C','S'], ['A','D','E','E'] ]
 * 
 * Given word = "ABCCED", return true. Given word = "SEE", return true. Given
 * word = "ABCB", return false.
 */

 class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); ++i) 
            for (int j = 0; j < board[0].size(); ++j) 
                if (adjacentSearch(board, word, i, j, 0)) return true;
        return false;
    
    }
protected:

    bool adjacentSearch(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        if(index == word.size()) return true; 
        if(i < 0 || j < 0 || i > board.size()-1 || j > board[0].size()-1) return false; 
        if(board[i][j] != word[index]) return false; 
        board[i][j] = '*'; // change the content, to avoid duplicated search
        bool furtherSearch =  adjacentSearch(board, word, i+1, j, index+1) || // up
                              adjacentSearch(board, word, i-1, j, index+1) || // down
                              adjacentSearch(board, word, i, j-1, index+1) || // left
                              adjacentSearch(board, word, i, j+1, index+1);   // right      
        board[i][j] = word[index]; 
        return furtherSearch;
    }
};