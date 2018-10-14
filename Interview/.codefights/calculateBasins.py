from collections import Counter as cntr


def calculateBasins(grid):
    n, basins = len(grid), [u for u in range(len(grid)**2)]

    # disjoint-set-union help methods
    def find(u): return u if basins[u] == u else find(basins[u])

    def union(u, v): basins[find(v)] = find(u)

    # union edges using disjoint-set-union
    for i in range(n):
        for j in range(n):
            mini, minj = get_min(grid, i, j, n)
            union(i*n + j, mini*n + minj)

    # count and sort
    return sorted(cntr(find(u) for u in range(n*n)).values(), reverse=True)

# find edge


def get_min(grid, i, j, n):
    mini, minj = i, j
    if i > 0 and grid[i-1][j] < grid[mini][minj]:
        mini, minj = i - 1, j
    if i < n-1 and grid[i+1][j] < grid[mini][minj]:
        mini, minj = i + 1, j
    if j > 0 and grid[i][j-1] < grid[mini][minj]:
        mini, minj = i, j - 1
    if j < n-1 and grid[i][j+1] < grid[mini][minj]:
        mini, minj = i, j + 1
    return mini, minj
