#include <map>
#include <utility>
#include <iostream>
#include <list>
#include <cmath>
#include <cstdio>

using namespace std;

// d es distancia entre los centros de los circulos 

double areaintersectCircles(double r1, double r2, double d)
{
    if(d == 0 || d + r2 < r1 || d + r1 < r2)
        return min(M_PI * r1 * r1, M_PI * r2 * r2);
    double a = pow(r1, 2) * acos((pow(d, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * d * r1));
    double b = pow(r2, 2) * acos((pow(d, 2) + pow(r2, 2) - pow(r1, 2)) / (2 * d * r2));
    double c = (sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2))) / 2;
    double respuesta = a + b - c;
    if(respuesta != respuesta)
        return 0;
    return respuesta;
}

bool circlesIntersect(double r1, double r2, double d)
{
	return r1 + r2 < d; // o <= dependiendo de la definicion
}
