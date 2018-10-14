#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
struct Point {
    double _x, _y;
  Point(double x, double y) : _x(x),_y(y) {}
};
// find centre point given 3 points on circumference of circle
Point* centre(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double s = 0.5 * ((x2 - x3) * (x1 - x3) - (y2 - y3) * (y3 - y1));
    double sUnder = (x1 - x2) * (y3 - y1) - (y2 - y1) * (x1 - x3);
    if(sUnder != 0) {
        s /= sUnder;
        double xc = 0.5 * (x1 + x2) + s * (y2 - y1); // center x coordinate
        double yc = 0.5 * (y1 + y2) + s * (x1 - x2); // center y coordinate
    return new Point(xc, yc);
    }
  return NULL;
}
int main()
{
    double x1 = 0, y1 = 4, x2 = 3, y2 = 5, x3 = 7, y3 = 3;
    Point* p = centre(x1, y1, x2, y2, x3, y3);
    printf("(%lf,%lf)\n", p->_x, p->_y);
    return 0;
}
