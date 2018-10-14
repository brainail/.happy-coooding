#include<iostream>
#include<math.h>
#include<vector>
using namespace std;

/*  Watch out the coordinates are integers! */
struct Point{
  int x,y; };

/*  Distance between two points */
double Distance(Point p1, Point p2){
  return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

istream &operator>>(istream &is, Point &p){
  is>>p.x>>p.y;
  return is;
}

ostream &operator<<(ostream &os, Point &p){
  os<<"("<<p.x<<","<<p.y<<")";
  return os;
}

void ClosestFarthestPairs(vector<Point *> points)
{
  int max1, max2, min1, min2;
  double maxy=0, miny=0, maxt, mint; 
  for(int i=0; i<points.size(); i++)
    for(int j=i+1; j<points.size(); j++)
    {
      if(maxy < (maxt=Distance(*points[i], *points[j])))
      {
        maxy = maxt;
        max1 = i;
        max2 = j;
      }
    }
  miny = maxy;
  for(int i=0; i<points.size(); i++)
    for(int j=i+1; j<points.size(); j++)
    {
      if(miny > (mint=Distance(*points[i], *points[j])))
      {
        miny = mint;
        min1 = i;
        min2 = j;
      }
    }
  cout<<"Closest pair is: "<<(*points[min1])<<" and "<<(*points[min2])<<endl;
  cout<<"Farthest pair is: "<<(*points[max1])<<" and "<<(*points[max2])<<endl;
}

int main(){
  vector<Point *> points;
  int i,nPoints;
  while(!cin.eof()){
    cin>>nPoints;
    if(!nPoints) break;
    points.clear();
    Point *p;
    for(i=0;i<nPoints;i++){
      p = new Point;
      cin>>*p;
      points.push_back(p);
    }
    ClosestFarthestPairs(points);
  } 
  return 0;
}
