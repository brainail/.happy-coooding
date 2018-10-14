int maximalSquare(char[][] M) {
    int R = M.length; 
    if (0 == R) return 0;
    
    int C = M[0].length;     
    int S[][] = new int[R][C];     

    int i , j;
    for(i = 0; i < R; i++) S[i][0] = M[i][0] - '0';
    for(j = 0; j < C; j++) S[0][j] = M[0][j] - '0';
           
    for(i = 1; i < R; i++) {
        for(j = 1; j < C; j++) {
            if (M[i][j] == '1') {
                S[i][j] = Math.min(S[i][j-1],Math.min(S[i-1][j], S[i-1][j-1])) + 1;
            } else {
                S[i][j] = 0;
            }
        }    
    } 
    
    int max = 0;
    for(i = 0; i < R; i++) {
        for(j = 0; j < C; j++) {
            max = Math.max(max, S [i][j]);
        }
    }
    
    return max * max;
}
