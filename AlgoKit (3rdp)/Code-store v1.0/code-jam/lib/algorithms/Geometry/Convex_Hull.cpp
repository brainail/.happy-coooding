#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point
{
    double x, y;
};

int n;

double dis(Point p1, Point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

double cross(Point p1, Point p2, Point p3)
{
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}

bool comp(const Point &p1, const Point &p2)
{
    if(p1.y < p2.y) return true;
    if(p1.y > p2.y) return false;
    if(p1.x < p2.x) return true;
}

void getconvexhull(Point p1[], Point p2[], int &top)
{
    sort(p1, p1 + n, comp);
    int i;
    top = 0;
    p2[top++] = p1[0];
    p2[top++] = p1[1];
    for (i = 2; i < n; i++)
    {
        while (top >= 2 && cross(p2[top - 2], p2[top - 1], p1[i]) <= 0)
            --top;
        p2[top++] = p1[i];
    }
    int r = top;
    for (i = n - 2; i >= 0; i--)
    {
        while (top > r && cross(p2[top - 2], p2[top - 1], p1[i]) <= 0)
            --top;
        if (i != 0)
            p2[top++] = p1[i];
    }
}

/*
  Otra forma de verlo:
  vector<point> convex_hull(vector<point> ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  vector<point> ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  ch.resize(k-1);
  return ch;
}
*/

int main()
{
    int m, i;
    while (scanf("%d", &n) != EOF && n) {
        Point p1[105], p2[105];
        for (i = 0; i < n; i++)
            scanf("%lf%lf", &p1[i].x, &p1[i].y);
        if (n == 1) {
            printf("0.00\n");
            continue;
        }
        getconvexhull(p1, p2, m);
        double ans = 0.0;
        for (i = 0; i < m - 1; i++)
            ans += dis(p2[i], p2[i + 1]);
        ans += dis(p2[0], p2[m - 1]);
        printf("%.2lf\n", ans);
    }
    return 0;
}
