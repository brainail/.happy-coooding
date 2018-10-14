Matrix mul(const Matrix &A,const Matrix &B)
{
    Matrix C;
    int i, j, k;
    memset(C.matrix, 0, sizeof(C.matrix));
    for(k = 1; k <= d; k++)
        for(i = 1; i <= d; i++)
            if(A.matrix[i][k]!=0) {
                for(j = 1; j<= d; j++) {
                    if(B.matrix[k][j]!=0) {
                        C.matrix[i][j] = (C.matrix[i][j] + A.matrix[i][k] * B.matrix[k][j]) % MOD;
                    }
                }
            }
    return C;
}

