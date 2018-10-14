#include<iostream>
#include<vector>
using namespace std;

/*  Watch out the point are integers! */
struct Point{
  int x,y;
};

int maxi(int x, int y){
  return ((x>y)?x:y);
}

int mini(int x, int y){
  return ((x<y)?x:y);
}

/* Checks if p is inside the fucking bounding box
  of the shitting segment formed by ps1 and ps2 */
bool isInBoundingBox(Point ps1, Point ps2, Point p){
  if((mini(ps1.x,ps2.x)<=p.x && p.x<=maxi(ps1.x,ps2.x)) &&
     (mini(ps1.y,ps2.y)<=p.y && p.y<=maxi(ps1.y,ps2.y)))
    return true;
  return false; }

/*  The cross product: (p1-p) X (p2-p): Zero if parallel */
int CrossProduct(Point p1, Point p2, Point p)
{ return ((p1.x-p.x)*(p2.y-p.y) - (p2.x-p.x)*(p1.y-p.y)); }

/* Watch out that if p touch the borders
is considered that p inside the polygon. */
bool isPointInside(vector<Point *>polygon, Point *p){
  int d=0,prevD;
  for(int i=0;i<polygon.size();i++)
  {
    prevD = CrossProduct((*polygon[i]),
		    (*polygon[((i+1)%polygon.size())]),
		    (*p));
		if(d==0 && prevD!=0) d = prevD;
    if((prevD>0 && d<0) || (prevD<0 && d>0) )
      return false;
    if((prevD==0 && isInBoundingBox((*polygon[i]),
			     (*polygon[((i+1)%polygon.size())]),
			     (*p)))) return true;
  }
  return true;
}

int main(){
  vector<Point *> polygon;
  Point *pointInDiscordia;

  int i,c,nPoints;
  c = 1;
  while(!cin.eof()){
    cin>>nPoints;
    if(!nPoints) break;
    polygon.clear();
    Point *p;
    for(i=0;i<nPoints;i++){
      p = new Point;
      cin>>p->x>>p->y;
      polygon.push_back(p);
    }
    pointInDiscordia = new Point;
    cin>>pointInDiscordia->x>>pointInDiscordia->y;
    cout<<"Case #"<<(c++)<<":"<<endl;
    if(isPointInside(polygon,pointInDiscordia)){
      cout<<"The Discordia Point is INSIDE of ME.";
    } else {
      cout<<"The Discordia Point is OUTSIDE of ME.";
    }
    cout<<endl;
  } 
  return 0;
}
