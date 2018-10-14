MODULO = 1000000000 + 7

def hierarchiesCount(n, respectList):
    if n == 1:
        return 1
    mat = [[0 for x in range(n)] for y in range(n)]
    for v in respectList:
        mat[v[0]][v[1]] = -1
        mat[v[1]][v[0]] = -1
        mat[v[0]][v[0]] += 1
        mat[v[1]][v[1]] += 1
    
    return (n * det(mat, n - 1)) % MODULO


def gcd(a, b):
    if a == 0 or b == 0:
        return a + b
    return gcd(b, a % b)

def modInverse(a, m):
    mo = m
    temp = 0
    q = 0
    x = 0
    y = 1
    while (a > 1):
        temp = m
        q = a // m
        m = a % m
        a = temp
        temp = x
        x = y - q * x
        y = temp
    if y < 0:
        y += mo
    return y;


def det(mat, n):
    left = []
    for i in range(1, n):
        for j in range(i, n):
            if mat[j][i - 1] == 0 or mat[i - 1][i - 1] == 0:
                continue
            g = gcd(mat[i - 1][i - 1], mat[j][i - 1])
            rowMult = (mat[i - 1][i - 1] * modInverse(g, MODULO)) % MODULO
            subMult = (mat[j][i - 1] * modInverse(g, MODULO)) % MODULO
            left.insert(0, rowMult)
            for k in range(i, n):
                mat[j][k] = ((mat[j][k] * rowMult) % MODULO - (mat[i - 1][k] * subMult) % MODULO) % MODULO

    ans = 1
    for i in range(n):
        ans = (ans * mat[i][i]) % MODULO
    for l in left:
        if l == 0:
            continue
        ans = ans * modInverse(l, MODULO)
    ans %= MODULO
    if ans < 0:
        ans += MODULO
    return ans