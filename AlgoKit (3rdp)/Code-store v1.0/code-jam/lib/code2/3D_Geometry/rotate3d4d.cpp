/*
 * Rotation in 3D and 4D
 *
 * Adapted by: Richard Krueger <richard@cs.ualberta.ca>
 * References:
 *   http://www.magic-software.com/src/misc/rot3d4d.cpp  (code)
 *   http://www.magic-software.com/src/misc/rotation.pdf (docs, theory)
 *
 * Rotation in 3D about arbitrary vector. Rotation in 4D about space
 * spanned by two arbitrary but linearly independent vectors.
 * Returns the rotation matrix that can be applied against points in
 * the original space to find the new points.
 *
 * Note that the rotation angle is specified in radians, and
 * that direction of rotation is counterclockwise if angle > 0,
 * and clockwise if angle < 0.
 *
 * Obviously you will only need one of these functions.
 *
 * Date: 2 March 2000
 *
 * WARNING: In incoming
 */

#include <stdio.h>
#include <math.h>

void Rotate3D (double line[3], double angle, double rotate[3][3])
{
  int row, col, mid;
  double A[3][3], A2[3][3];
  double sn, omcs;

  /* identity matrix */
  static const double I[3][3] = { { 1,0,0 }, { 0,1,0 }, { 0,0,1 } };

  /* infinitesimal rotation about line */
  A[0][0] = 0;         A[0][1] = +line[2];  A[0][2] = -line[1];
  A[1][0] = -line[2];  A[1][1] = 0;         A[1][2] = +line[0];
  A[2][0] = +line[1];  A[2][1] = -line[0];  A[2][2] = 0;

  /* A2 = A*A */
  for (row = 0; row < 3; row++)
    for (col = 0; col < 3; col++) {
      A2[row][col] = 0;
      for (mid = 0; mid < 3; mid++)
	A2[row][col] += A[row][mid]*A[mid][col];
    }

  sn = sin(angle);
  omcs = 1-cos(angle);

  /* rotation is I + sin(angle)*A + [1-cos(angle)]*A*A */
  for (row = 0; row < 3; row++)
    for (col = 0; col < 3; col++)
      rotate[row][col] = I[row][col] + sn*A[row][col] + omcs*A2[row][col];
}

void Rotate4D (double u[4], double v[4], double angle, double rotate[4][4])
{
  int row, col, mid;
  double I[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  double A[4][4], A2[4][4];
  double length, dot, sn, omcs;

  /* orthonormalize vectors u and v */
  length = sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2] + u[3]*u[3]);
  if ( length > 0 )
    for (row = 0; row < 4; row++)
      u[row] /= length;
  else
    return;

  dot = u[0]*v[0] + u[1]*v[1] + u[2]*v[2] + u[3]*v[3];
  for (row = 0; row < 4; row++)
    v[row] -= dot*u[row];

  length = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
  if ( length > 0 )
    for (row = 0; row < 4; row++)
      v[row] /= length;
  else
    return;

  /* identity matrix is I*/
  /* infinitesimal rotation through uv-plane */
  A[0][0] = 0;
  A[0][1] = u[2]*v[3] - u[3]*v[2];
  A[0][2] = u[3]*v[1] - u[1]*v[3];
  A[0][3] = u[1]*v[2] - u[2]*v[1];
  A[1][0] = -A[0][1];
  A[1][1] = 0;
  A[1][2] = u[0]*v[3] - u[3]*v[0];
  A[1][3] = u[2]*v[0] - u[0]*v[2];
  A[2][0] = -A[0][2];
  A[2][1] = -A[1][2];
  A[2][2] = 0;
  A[2][3] = u[0]*v[1] - u[1]*v[0];
  A[3][0] = -A[0][3];
  A[3][1] = -A[1][3];
  A[3][2] = -A[2][3];
  A[3][3] = 0;

  /* A2 = A*A */
  for (row = 0; row < 4; row++)
    for (col = 0; col < 4; col++) {
      A2[row][col] = 0;
      for (mid = 0; mid < 4; mid++)
	A2[row][col] += A[row][mid]*A[mid][col];
    }

  sn = sin(angle);
  omcs = 1-cos(angle);

  /* rotation is I + sin(angle)*A + [1-cos(angle)]*A*A */
  for (row = 0; row < 4; row++)
    for (col = 0; col < 4; col++)
      rotate[row][col] = I[row][col] + sn*A[row][col] + omcs*A2[row][col];
}

int main (){
  double angle = 0.1;
  double line[3] = {1,0,0};
  double u[4] = {1,0,0,0}, v[4] = {0,1,0,0};
  double rot3D[3][3], rot4D[4][4];
  int row, col;

  printf("Enter 3D vector to rotate about: ");
  scanf("%lf%lf%lf", &line[0], &line[1], &line[2]);
  printf("Enter angle to rotate through (in radians): ");
  scanf("%lf", &angle);

  Rotate3D(line,angle,rot3D);
  printf("Rotation matrix is:\n");
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++)
      printf("% f ", rot3D[row][col]);
    printf("\n");
  }
  printf("\n");

  Rotate4D(u,v,angle,rot4D);
  for (row = 0; row < 4; row++) {
    for (col = 0; col < 4; col++)
      printf("% f ", rot4D[row][col]);
    printf("\n");
  }
  return 0;
}
