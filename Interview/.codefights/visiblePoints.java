double len(double x, double y) {
    return Math.sqrt(x * x + y * y);    
}

double mult(double x0, double y0, double x1, double y1) {
    return x0 * x1 + y0 * y1;    
}

int visiblePoints(int[][] points) {
    int n = points.length;
    double [] angles = new double [2 * n];
    int k = 0;
    int always = 0;
	for (int i = 0; i < n; ++ i) {
        int x = points [i][0];
        int y = points [i][1];
        if (x == 0 && y == 0) {
            always ++;
            continue;
        }
        double co;
        if (x > 0 && y >= 0) {
            co = mult(0,+1,x,y) / (len(0,+1) * len(x,y)); 
            co = Math.toDegrees(Math.acos(co));
        } else if (x >= 0) {
            co = mult(1,0,x,y) / (len(1,0) * len(x,y));  
            co = Math.toDegrees(Math.acos(co));
            co += 90;
        } else if (y <= 0) {
            co = mult(0,-1,x,y) / (len(0,-1) * len(x,y));  
            co = Math.toDegrees(Math.acos(co));
            co += 180;
        } else {
            co = mult(-1,0,x,y) / (len(-1,0) * len(x,y));  
            co = Math.toDegrees(Math.acos(co));
            co += 270;            
        }
		angles [k++] = co;
    }
    Arrays.sort(angles, 0, k);
    for (int i = 0; i < k; ++ i) angles [k + i] = 360 + angles [i];
    k *= 2;
    int i = -1;
    int j = 0;
    int maxVisible = 0;
    while (i + 1 < k) {
        ++ i;
        while (j + 1 < k && angles [j + 1] - angles [i] - 1e-7 <= 45) ++ j;
        maxVisible = Math.max(maxVisible, j - i + 1);
    }
    return maxVisible + always;
}
