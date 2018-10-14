void fly(char[][] skyMap, int x, int y) {
    if (x < 0 || x >= skyMap.length) return;
    if (y < 0 || y >= skyMap [x].length) return;
    if ('1' != skyMap [x][y]) return;
    skyMap [x][y] = '0';
    fly(skyMap, x - 1, y);
    fly(skyMap, x + 1, y);
    fly(skyMap, x, y - 1);
    fly(skyMap, x, y + 1);
}

int countClouds(char[][] skyMap) {
    int clouds = 0;
    for (int x = 0; x < skyMap.length; ++ x)
        for (int y = 0; y < skyMap [x].length; ++ y)
            if ('1' == skyMap [x][y]) {
                ++ clouds;
                fly(skyMap, x, y);
            }
    return clouds;
}
