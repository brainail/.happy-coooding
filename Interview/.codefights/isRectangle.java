double len(int x, int y) {
    return Math.sqrt(x * x + y * y);    
}

double mult(int x0, int y0, int x1, int y1) {
    return x0 * x1 + y0 * y1;    
}

boolean isRectangle(int[][] points) {
    boolean isRect = true;
    for (int i = 0; i < 4; ++ i) {
        int x0 = points [(i + 1) % 4][0] - points [i][0];
        int y0 = points [(i + 1) % 4][1] - points [i][1];
        int x1 = points [(i + 2) % 4][0] - points [(i + 1) % 4][0];
        int y1 = points [(i + 2) % 4][1] - points [(i + 1) % 4][1];
        double co = mult(x0,y0,x1,y1) / (len(x0,y0) * len(x1,y1));
        isRect &= Math.abs(co) <= 1e-9;
    }
    return isRect;
}
