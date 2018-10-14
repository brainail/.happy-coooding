#include <iostream>
#include <math.h>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI (2.0 * acos(0.0)) // important constant

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { int x, y; }; // preferred mode
struct point_d { double x, y; }; // preferred mode

double dist(point_d p1, point_d p2) { // returns Euclidian distance between two points
  double dx = p1.x - p2.x, dy = p1.y - p2.y;
  return hypot(dx, dy);
}

double perimeter_of_triangle(double ab, double bc, double ca) {
  return ab + bc + ca;
}

double perimeter_of_triangle(point_d a, point_d b, point_d c) {
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  return ab + bc + ca;
}

double Heron(double ab, double bc, double ca) {
  // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
  double s = 0.5 * perimeter_of_triangle(ab, bc, ca);
  return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca);
}

double Heron(point_d a, point_d b, point_d c) {
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  return Heron(ab, bc, ca);
}

double r_inner_circle(double ab, double bc, double ca) {
  return Heron(ab, bc, ca) / (0.5 * perimeter_of_triangle(ab, bc, ca));
}

double r_inner_circle(point_d a, point_d b, point_d c) {
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  return r_inner_circle(ab, bc, ca);
}

double r_outer_circle(double ab, double bc, double ca) {
  return ab * bc * ca / (4.0 * Heron(ab, bc, ca));
}

double r_outer_circle(point_d a, point_d b, point_d c) {
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  return r_outer_circle(ab, bc, ca);
}

int main() {
  double base = 4.0, h = 3.0;
  double A = 0.5 * base * h;
  printf("Area = %.2lf\n", A);

  point_d a = { 0.0, 0.0 }; // a right triangle
  point_d b = { 4.0, 0.0 };
  point_d c = { 4.0, 3.0 };

  double p = perimeter_of_triangle(a, b, c);
  double s = 0.5 * p;
  A = Heron(a, b, c);
  printf("Area = %.2lf\n", A); // must be the same as above

  printf("R1 (radius of inner circle) = %.2lf\n", r_inner_circle(a, b, c));
  printf("R2 (radius of outer circle) = %.2lf\n", r_outer_circle(a, b, c));

  // Law of Cosines
  double ab = dist(a, b);
  double bc = dist(b, c);
  double ca = dist(c, a);
  double alpha = RAD_to_DEG(acos((ca * ca + ab * ab - bc * bc) / (2.0 * ca * ab)));
  printf("alpha = %.2lf\n", alpha);
  double beta  = RAD_to_DEG(acos((ab * ab + bc * bc - ca * ca) / (2.0 * ab * bc)));
  printf("beta  = %.2lf\n", beta);
  double gamma = RAD_to_DEG(acos((bc * bc + ca * ca - ab * ab) / (2.0 * bc * ca)));
  printf("gamma = %.2lf\n", gamma);

  // Law of Sines
  printf("%.2lf == %.2lf == %.2lf\n", bc / sin(DEG_to_RAD(alpha)), ca / sin(DEG_to_RAD(beta)), ab / sin(DEG_to_RAD(gamma)));

  // Phytagorean Theorem
  printf("%.2lf^2 == %.2lf^2 + %.2lf^2\n", ca, ab, bc);

  return 0;
}



// not tested yet
// circumcenter of circle through three points
int circle(point_d p1, point_d p2, point_d p3, point_d *center, long double *r) {
  double a, b, c, d, e, f, g;
  a = p2.x - p1.x;
  b = p2.y - p1.y;
  c = p3.x - p1.x;
  d = p3.y - p1.y;
  e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
  f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
  g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
  if (fabs(g) < EPS)
    return 0;

  center->x = (d*e - b*f) / g;
  center->y = (a*f - c*e) / g;
  *r = sqrt((p1.x-center->x) * (p1.x-center->x) + (p1.y-center->y) * (p1.y-center->y));
  return 1;
}
