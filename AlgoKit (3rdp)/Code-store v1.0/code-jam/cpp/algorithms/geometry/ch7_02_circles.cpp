#include <iostream>
#include <math.h>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI (2.0 * acos(0.0)) // important constant

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { int x, y; }; // preferred mode
struct point_d { double x, y; };

int in_circle(point p, point c, int r) {
  int dx = p.x - c.x, dy = p.y - c.y, Euc = dx * dx + dy * dy, rSq = r * r; // all integer
       if (Euc  < rSq) return 0; // inside
  else if (Euc == rSq) return 1; // at border
  else                 return 2; // outside
}

int in_circle2(point p, point q, point r, point s) {
  return 0; // not yet implemented
}

// Igor Naverniouk's library
bool circle_2_points_radius(point_d p1, point_d p2, double r, point_d *ctr) {
  double d2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  double det = r * r / d2 - 0.25;
  if (det < 0.0) return false;
  double h = sqrt(det);
  ctr->x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  ctr->y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
  return true;
}

int main() {
  // circle equation, inside, border, outside
  point ctr = { 2, 2 };
  int r = 7;
  point inside = { 8, 2 };
  printf("%d\n", in_circle(inside, ctr, r)); // 0-inside
  point border = { 9, 2 };
  printf("%d\n", in_circle(border, ctr, r)); // 1-at border
  point outside = { 10, 2};
  printf("%d\n", in_circle(outside, ctr, r)); // 2-outside

  double d = 2 * r;
  printf("Diameter = %.2lf\n", d);
  double c = PI * d;
  printf("Perimeter = %.2lf\n", c);
  printf("Length of arc (30 degrees) = %.2lf\n", 30.0 / 360.0 * c);
  printf("Length of chord (30 degrees) = %.2lf\n", sqrt((2 * r * r) * (1 - cos(DEG_to_RAD(30.0)))));
  double A = PI * r * r;
  printf("Area of circle = %.2lf\n", A);
  printf("Area of sector (30 degrees) = %.2lf\n", 30.0 / 360.0 * A);
  // printf("Area of segment (30 degrees) = %.2lf\n", 0.0); // subtract the area of the corresponding sector with the area of an Isosceles Triangle with sides: r, r, and Chord-length

  point_d p1 = { 0.0,  1.0 };
  point_d p2 = { 0.0, -1.0 };
  point_d ans;
  circle_2_points_radius(p1, p2, 2.0, &ans);
  printf("One of the center is (%.2lf, %.2lf)\n", ans.x, ans.y);
  circle_2_points_radius(p2, p1, 2.0, &ans);
  printf("The other center  is (%.2lf, %.2lf)\n", ans.x, ans.y);

  return 0;
}
